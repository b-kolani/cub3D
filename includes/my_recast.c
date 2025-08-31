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

// ray_one.c
// Build (Linux): cc -Wall -Wextra -Werror ray_one.c -lmlx -lXext -lX11 -lm
// Build (macOS): cc -Wall -Wextra -Werror ray_one.c -lmlx -framework OpenGL -framework AppKit -lm

#include <mlx.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define WIN_W 800
#define WIN_H 600
#define MAP_H 5
#define MAP_W 6

typedef struct s_data {
    void    *mlx;
    void    *win;
    int     grid[MAP_H][MAP_W];   // 1 = wall, 0 = empty
    double  px;                    // player x in MAP units (not pixels)
    double  py;                    // player y in MAP units
    double  angle_deg;             // player angle in degrees (0 = +X, CCW)
    int     cell;                  // pixels per map cell
    int     ox, oy;                // top-left screen origin of the map (in pixels)
} t_data;

/* ---------- Pixel & simple drawing ---------- */

static void put_px(t_data *d, int x, int y, int color) {
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H) return;
    mlx_pixel_put(d->mlx, d->win, x, y, color);
}

static void fill_rect(t_data *d, int x, int y, int size, int color) {
    int yy = y;
    while (yy < y + size) {
        int xx = x;
        while (xx < x + size) {
            put_px(d, xx, yy, color);
            xx++;
        }
        yy++;
    }
}

static void draw_cell_map(t_data *d) {
    int gy = 0;
    while (gy < MAP_H) {
        int gx = 0;
        while (gx < MAP_W) {
            int sx = d->ox + gx * d->cell;
            int sy = d->oy + gy * d->cell;
            int color = (d->grid[gy][gx] == 1) ? 0xff0090 : 0x1e1e1e;
            fill_rect(d, sx, sy, d->cell, color);
            gx++;
        }
        gy++;
    }
}

static void draw_player(t_data *d) {
    int sx = d->ox + (int)(d->px * d->cell);
    int sy = d->oy + (int)(d->py * d->cell);
    fill_rect(d, sx - 3, sy - 3, 6, 0xffff00);
}

/* ---------- The ray: step until we hit a wall ---------- */
/*
 * Cast exactly ONE ray from (px,py) with angle angle_deg.
 * We step in SMALL increments in MAP units (world space), and stop at the
 * first cell that contains a wall (grid[y][x] == 1) or when we leave the map.
 * For visualization, we plot a pixel at each step (green), and a red pixel at the hit.
 */
static void cast_single_ray(t_data *d, double angle_deg) {
    double rad = angle_deg * M_PI / 180.0;
    double dirx = cos(rad);
    double diry = sin(rad);

    // Small step in MAP units (independent of pixel size)
    const double step = 0.01;
    // Safety cap to avoid infinite loops if something goes wrong
    const int max_steps = 200000000;

    double rx = d->px;
    double ry = d->py;

    int steps = 0;
    while (steps++ < max_steps) {
        rx += dirx * step;
        ry += diry * step;

        // Stop if we move outside the map
        int mx = (int)floor(rx);
        int my = (int)floor(ry);
        if (mx < 0 || mx >= MAP_W || my < 0 || my >= MAP_H)
            break;

        // Draw the ray path point (convert world -> screen)
        int sx = d->ox + (int)(rx * d->cell);
        int sy = d->oy + (int)(ry * d->cell);
        put_px(d, sx, sy, 0x00ff00); // green line

        // Check collision with a wall
        if (d->grid[my][mx] == 1) {
            // Draw the hit point in red and stop
            put_px(d, sx, sy, 0x0000ff);
            break;
        }
    }
}

int main(void) {
    t_data d;
    memset(&d, 0, sizeof(d));

    d.mlx = mlx_init();
    d.win = mlx_new_window(d.mlx, WIN_W, WIN_H, "One Ray");

    // Map (5 x 6)
    int map[MAP_H][MAP_W] = {
        {1,1,1,1,1,1},
        {1,0,0,1,0,1},
        {1,0,1,0,0,1},
        {1,1,0,0,0,1},
        {1,1,1,1,1,1}
    };
    for (int y = 0; y < MAP_H; y++)
        for (int x = 0; x < MAP_W; x++)
            d.grid[y][x] = map[y][x];

    // Player in world/MAP units (not pixels)
    d.px = 1.5;
    d.py = 1.25;
    d.angle_deg = 360.0; // 0=to the right, 90=down (screen Y grows downward)

    d.cell = 90;

    // Center the map on screen
    d.ox = (WIN_W - d.cell * MAP_W) / 2;
    d.oy = (WIN_H - d.cell * MAP_H) / 2;

    // Draw scene
    draw_cell_map(&d);
    draw_player(&d);
    cast_single_ray(&d, d.angle_deg);

    mlx_loop(d.mlx);
    return 0;
}
