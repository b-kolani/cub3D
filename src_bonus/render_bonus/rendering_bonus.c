#include "../../includes/cub3d_bonus.h"

void	timer(t_game *game)
{
	struct timeval	curr_time;
	double			seconds;
	double			micros;

	gettimeofday(&curr_time, NULL);
	seconds = (curr_time.tv_sec - game->config.prev_time.tv_sec);
	micros = (curr_time.tv_usec - game->config.prev_time.tv_usec) / 1e6;
	game->config.delta_time = seconds + micros;
	game->config.prev_time = curr_time;
}

int	game_loop(t_game *game)
{
	timer(game);
	if (update_player(game))
		return (-1);
	if (draw_background(game))
		return (-1);
	if (raycasting(game))
		return (-1);
	calculate_dist_camera_to_sprite(&game->config);
	sort_sprites_by_distance(game->config.sprites,
		game->config.sprites_count);
	update_sprites_animation(game);
	update_all_doors(&game->config);
	render_all_sprites(game);
	if (draw_mini_map(game))
	{
		gc_free(game);
		exit(-1);
	}
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

void	events_handler(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, mouse_move_handler, game);
	mlx_mouse_hook(game->mlx.win_ptr, mouse_click_handler, game);
	mlx_hook(game->mlx.win_ptr, 17, 0L, close_window, game);
	mlx_loop_hook(game->mlx.mlx_ptr, game_loop, game);
	mlx_loop(game->mlx.mlx_ptr);
}

int	rendering(t_game *game)
{
	if (init_mlx(&game->mlx))
		return (-1);
	game->mlx.screen.img_ptr = mlx_new_image(game->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!game->mlx.screen.img_ptr)
		return (print_err("mlx error: Failed to create mlx image\n"));
	game->mlx.screen.img_data_addr = mlx_get_data_addr(
			game->mlx.screen.img_ptr,
			&game->mlx.screen.bits_per_pixel,
			&game->mlx.screen.line_length,
			&game->mlx.screen.endian);
	if (!game->mlx.screen.img_data_addr)
		return (print_err("mlx error: Failed to get image address\n"));
	game->config.z_buffer = gc_malloc(game->gc, sizeof(double) * WIDTH);
	if (!game->config.z_buffer)
		return (print_err("z_buffer allocation failed\n"));
	load_wall_all_tex(game);
	load_door_all_text(game);
	load_all_sprites_tex(game);
	if (gettimeofday(&game->config.prev_time, NULL))
		return (print_err("Time error\n"));
	game->g_mouse_lock = 0;
	events_handler(game);
	return (0);
}
