#include "../../includes/cub3d.h"

int	game_loop(t_game *game)
{
	if (update_player(game))
		return (-1);
	if (draw_background(game))
		return (-1);
	if (raycasting(game))
		return (-1);
	mlx_put_image_to_window(game->mlx.mlx_ptr,
		game->mlx.win_ptr, game->mlx.screen.img_ptr,
		0, 0);
	return (0);
}

int	close_window(t_game *game)
{
	printf("Window closed: exiting...\n");
	if (game->mlx.screen.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.screen.img_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	gc_free(game);
	exit(0);
}

int	rendering(t_game *game)
{
	if (ft_init_mlx(&game->mlx))
		return (-1);
	game->mlx.screen.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!game->mlx.screen.img_ptr)
		return (print_err("mlx error: Failed to create mlx image\n"));
	game->mlx.screen.img_data_addr = mlx_get_data_addr(game->mlx.screen.img_ptr,
			&game->mlx.screen.bits_per_pixel,
			&game->mlx.screen.line_length, &game->mlx.screen.endian);
	if (!game->mlx.screen.img_data_addr)
		return (print_err("mlx error: Failed to get image address\n"));
	game->textures[NORTH] = load_texture(game, game->config.no);
	game->textures[SOUTH] = load_texture(game, game->config.so);
	game->textures[EAST] = load_texture(game, game->config.ea);
	game->textures[WEST] = load_texture(game, game->config.we);
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win_ptr, 17, 0L, close_window, game);
	mlx_loop_hook(game->mlx.mlx_ptr, game_loop, game);
	mlx_loop(game->mlx.mlx_ptr);
	return (0);
}
