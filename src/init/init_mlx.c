#include "../../includes/cub3d_bonus.h"

int ft_init_mlx(t_mlx *mlx)
{
    mlx->mlx_ptr = mlx_init();
    if (!mlx->mlx_ptr)
        return (print_err("mlx error: Failed to connect to mlx server\n"));
    // Creer une nouvelle fenetre mlx
    mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "cub3D");
    if (!mlx->win_ptr)
        return (print_err("mlx error: Failed to create a new window\n"));
    return (0);
}