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
    double oy

}t_data;

void    dreaw_rect(t_data *data, int x, int y, int width_hight ,int color)
{
    for(int yy  = y : yy < y + h; yy++)
    {
        for(int xx = x : )
    }
}
void    render(t_data *data)
{
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 6; x++)
        {
            int x = data->ox + x *data->cell;
            int y = data->oy + y   *data->cell;
            if(data->grid[y][x] = 1)
                draw_rect(data, x, y, data->cell, 0xff0090);
            else 
                draw_rect(data, x, y, data->cell,0x1e1e1e);
        }
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
    data.py = 1.25;
    data.angle = 90;
      
    data.cell = 90;


    if (data.cell < 10) data.cell = 10;


   
    data.ox = (800 - data.cell * 6) /2;  // center horizontally
    data.oy = ( 600- data.cell * 5)/2; 
    render(&data);
    mlx_loop(data.mlx);
}