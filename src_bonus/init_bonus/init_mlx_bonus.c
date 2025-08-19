#include "../../includes/cub3d_bonus.h"

int init_mlx(t_mlx *mlx_)
{
    mlx_->mlx_ptr = mlx_init();
    if (!mlx_->mlx_ptr)
        return (print_err("mlx error: Failed to connect to mlx server\n"));
    // Creer une nouvelle fenetre mlx
    mlx_->win_ptr = mlx_new_window(mlx_->mlx_ptr, WIDTH, HEIGHT, "cub3D");
    if (!mlx_->win_ptr)
        return (print_err("mlx error: Failed to create a new window\n"));
    return (0);
}
