#include "unistd.h"
#include "stdio.h"
#include "../../minilibx_opengl_20191021/mlx.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"
#include "math.h"
#include "sys/time.h"

#define WIDTH 800
#define HEIGHT 600

#define MAP_W 6
#define MAP_H 5

// Keys (macOS MLX)
#define KEY_ESC   53
#define KEY_LEFT  123
#define KEY_RIGHT 124

// Events
#define ON_KEYDOWN 2
#define ON_DESTROY 17

typedef struct s_data {
    void *mlx;
    void *win;

    int map[MAP_H][MAP_W];  // [y][x]

    double px, py; // player position (in map units, e.g., 1.5)
    double angle;  // player angle (radians)

    // Drawing helpers for minimap
    int cell;   // pixel size per map cell
    int ox, oy; // origin (top-left) where map is drawn
} t_data;

typedef struct s_rayhit {
    int hit;         // 1 if hit a wall, 0 if went out of bounds
    int mapX, mapY;  // cell coordinates of impact
    int side;        // 0 if an x-side was hit (vertical wall), 1 if y-side (horizontal)
    double dist;     // perpendicular distance from player to impact along the ray
    double hitX;     // world-space hit point x
    double hitY;     // world-space hit point y
} t_rayhit;

static void put_px(t_data *d, int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    mlx_pixel_put(d->mlx, d->win, x, y, color);
}

static void draw_rect(t_data *d, int x, int y, int w, int h, int color) {
    for (int yy = y; yy < y + h; yy++) {
        for (int xx = x; xx < x + w; xx++) {
            put_px(d, xx, yy, color);
        }
    }
}

static void draw_rect_outline(t_data *d, int x, int y, int w, int h, int color) {
    for (int xx = x; xx < x + w; xx++) {
        put_px(d, xx, y, color);
        put_px(d, xx, y + h - 1, color);
    }
    for (int yy = y; yy < y + h; yy++) {
        put_px(d, x, yy, color);
        put_px(d, x + w - 1, yy, color);
    }
}

static void world_to_screen(t_data *d, double wx, double wy, int *sx, int *sy) {
    // World (map) units to pixels in the minimap
    *sx = d->ox + (int)(wx * d->cell);
    *sy = d->oy + (int)(wy * d->cell);
}

static void draw_map(t_data *d) {
    // Clear background
    //draw_rect(d, 0, 0, WIDTH, HEIGHT, 0x101010);

    // Draw cells
    for (int my = 0; my < MAP_H; my++) {
        for (int mx = 0; mx < MAP_W; mx++) {
            int x = d->ox + mx * d->cell;
            int y = d->oy + my * d->cell;
            if (d->map[my][mx] == 1) {
                draw_rect(d, x, y, d->cell, d->cell, 0xff0090); // wall cell
            } else {
                draw_rect(d, x, y, d->cell, d->cell, 0x1e1e1e); // empty
            }
             draw_rect_outline(d, x, y, d->cell, d->cell, 0x0000ff); // grid line
        }
    }
}

static t_rayhit shoot_ray(t_data *d, double angle) {
    // 1) Ray direction from angle
    double rayDirX = cos(angle);
    double rayDirY = sin(angle);

    // 2) Starting cell (integer coords)
    int mapX = (int)d->px;
    int mapY = (int)d->py;

    // 3) Distances between next vertical/horizontal grid lines
    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

    // 4) Step direction and initial side distances
    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (d->px - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - d->px) * deltaDistX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (d->py - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - d->py) * deltaDistY;
    }

    // 5) DDA: step cell-by-cell until we hit a wall or go OOB
    int side = 0; // 0 if we crossed a vertical grid line last, 1 if horizontal
    int hit = 0;
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // Bounds check
        if (mapX < 0 || mapX >= MAP_W || mapY < 0 || mapY >= MAP_H) {
            // Out of map -> treat as no hit
            t_rayhit out = {0, mapX, mapY, side, 1e9, d->px, d->py};
            return out;
        }
        // Hit check (1 = wall)
        if (d->map[mapY][mapX] == 1) {
            hit = 1;
        }
    }

    // 6) Perpendicular distance to the wall (removes fish-eye)
    double dist;
    if (side == 0) {
        // We just crossed a vertical line
        dist = (mapX - d->px + (1 - stepX) / 2.0) / (rayDirX == 0 ? 1e-9 : rayDirX);
    } else {
        // We just crossed a horizontal line
        dist = (mapY - d->py + (1 - stepY) / 2.0) / (rayDirY == 0 ? 1e-9 : rayDirY);
    }
    if (dist < 0) dist = 0;

    // 7) Exact hit point in world coordinates
    double hitX = d->px + dist * rayDirX;
    double hitY = d->py + dist * rayDirY;

    t_rayhit res = {1, mapX, mapY, side, dist, hitX, hitY};
    return res;
}

static void draw_player(t_data *d) {
    int sx, sy;
    world_to_screen(d, d->px, d->py, &sx, &sy);
    // small square for player
    int r = d->cell / 8;
    if (r < 2) r = 2;
    draw_rect(d, sx - r, sy - r, r * 2 + 1, r * 2 + 1, 0xFF5555);
}

static void draw_ray(t_data *d, double angle, t_rayhit hit) {
    // Draw the ray as a line from player to hit point
    double rayDirX = cos(angle);
    double rayDirY = sin(angle);

    // step along the ray in small increments and plot pixels
    double maxT = hit.hit ? hit.dist : 10.0; // cap if no hit
    double step = 0.0025; // in world units

    for (double t = 0; t <= maxT; t += step) {
        double wx = d->px + rayDirX * t;
        double wy = d->py + rayDirY * t;
        int sx, sy;
        world_to_screen(d, wx, wy, &sx, &sy);
        put_px(d, sx, sy, 0xFFEB3B); // yellow
    }

    // Mark the hit cell and exact point if we hit
    if (hit.hit) {
        int hx, hy;
        world_to_screen(d, hit.hitX, hit.hitY, &hx, &hy);
        // Hit marker
        int r = 3;
        draw_rect(d, hx - r, hy - r, r * 2 + 1, r * 2 + 1, 0x00FF88);

        // Outline the cell we hit
        int cellX = d->ox + hit.mapX * d->cell;
        int cellY = d->oy + hit.mapY * d->cell;
        draw_rect_outline(d, cellX, cellY, d->cell, d->cell, 0x00FF88);
    }
}

static void render(t_data *d) {
    draw_map(d);
    draw_player(d);

    t_rayhit res = shoot_ray(d, d->angle);
    draw_ray(d, d->angle, res);

    // Show angle text (optional)
    char buf[128];
    snprintf(buf, sizeof(buf), "angle: %.2f rad", d->angle);
    mlx_string_put(d->mlx, d->win, 10, HEIGHT - 20, 0xFFFFFF, buf);
}

static int key_down(int key, t_data *d) {
    if (key == KEY_ESC) {
        mlx_destroy_window(d->mlx, d->win);
        exit(0);
    }
    if (key == KEY_LEFT) {
        d->angle -= 0.1;
        if (d->angle < -M_PI) d->angle += 2.0 * M_PI;
        render(d);
    }
    if (key == KEY_RIGHT) {
        d->angle += 0.1;
        if (d->angle > M_PI) d->angle -= 2.0 * M_PI;
        render(d);
    }
    return 0;
}

static int close_win(t_data *d) {
    (void)d;
    exit(0);
    return 0;
}

int main(void)
{
    t_data d;
    memset(&d, 0, sizeof(d));

    // Init MLX
    d.mlx = mlx_init();
    if (!d.mlx) return 1;
    d.win = mlx_new_window(d.mlx, WIDTH, HEIGHT, "Single Ray DDA (Top-Down)");
    if (!d.win) return 1;

    // Map (1 = wall, 0 = empty)
    int map[MAP_H][MAP_W] = {
        {1,1,1,1,1,1},
        {1,0,0,1,0,1},
        {1,0,1,0,0,1},
        {1,1,0,0,0,1},
        {1,1,1,1,1,1}
    };
    for (int y = 0; y < MAP_H; y++)
        for (int x = 0; x < MAP_W; x++)
            d.map[y][x] = map[y][x];

    // Player
    d.px = 1.5;
    d.py = 1.5;
    d.angle = 0.0; // facing east

    // Minimap layout
    // d.cell = (int)fmin((WIDTH - 60) / MAP_W, (HEIGHT - 80) / MAP_H);
    d.cell = 90;
    if (d.cell < 10) d.cell = 10;


   
    d.ox = (800 - d.cell * MAP_W) /2;  // center horizontally
    d.oy = ( 600- d.cell * MAP_H)/2; // center vertically

    // Hooks
    mlx_hook(d.win, ON_KEYDOWN, 0, key_down, &d);
    mlx_hook(d.win, ON_DESTROY, 0, close_win, &d);

    render(&d);
    mlx_loop(d.mlx);
    return 0;
}