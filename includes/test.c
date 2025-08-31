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

#define WIN_W 800
#define WIN_H 600
#define MAP_H 5
#define MAP_W 6


typedef struct s_data
{
    void *mlx;
    void *mlx_window;   
    int grid[5][6];
    double  px;
    double  py;
    double angle;
    int cell;
    double ox;
    double oy;

}t_data;
void    fill_rect(t_data *data, int x, int y, int size, int color);

static void put_px(t_data *data, int x, int y, int color) {
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H) return;
    mlx_pixel_put(data->mlx, data->mlx_window, x, y, color);
}
void    draw_player(t_data *data)
{
    int sx = data->ox + (int)(data->px * data->cell);
    int sy = data->oy + (int)(data->py * data->cell);
    fill_rect(data, sx , sy , 10, 0xffff00);
}
void    fill_rect(t_data *data, int x, int y, int size, int color)
{
    int yy = y;
    while(yy < y + size)
    {
        int xx = x;
        while(xx < x + size)
        {
            put_px(data, xx, yy, color);
            xx++;
        }
        yy++;
    }
}
void    draw_cell_map(t_data *data)
{
    int gy = 0;
    while(gy <  MAP_H)
    {
        int gx = 0;
        while(gx < MAP_W)
        {
            int sx = data->ox + gx * data->cell;
            int sy = data->oy + gy * data->cell;
            int color = (data->grid[gy][gx] == 1) ? 0xff0090 : 0x1e1e1e;
                fill_rect(data, sx, sy, data->cell, color);
                gx++;
        }
        gy++;
    }
}
void    cast_single_ray(t_data *data, double angle_deg)
{
        double red = angle_deg * M_PI / 180.0;
        double dirx = cos(angle_deg);
        double diry = sin(angle_deg);

        double step = 0.01;
        int mx_steps = 20000;

        double rx = data->px;
        double ry = data->py;
        int steps = 0;
        while(steps++ < mx_steps )
        {
            rx += dirx * step;
            ry += diry * step;
            
            int mx = (int) 
        }


}
int main()
{
    t_data data;
    memset(&data, 0, sizeof(data));
    data.mlx = mlx_init();
    data.mlx_window = mlx_new_window(data.mlx, 800, 600, "my_first");

    int map[5][6]= {
        {1,1,1,1,1,1},
        {1,0,0,1,0,1},
        {1,0,1,0,0,1},
        {1,1,0,0,0,1},
        {1,1,1,1,1,1}
    };
    // read the map;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j< 6; j++)
        {
            data.grid[i][j] = map[i][j];
        }
    }
    //player
    data.px = 1.5;
    data.py = 1.5;
    data.angle = 90.99;
    data.cell = 90;

    data.ox = (800 - data.cell * 6) /2;  // center horizontally
    data.oy = ( 600 - data.cell * 5)/2; 
    draw_cell_map(&data);
    draw_player(&data);
    cast_single_ray(&data, data.angle);
    mlx_loop(data.mlx);
}