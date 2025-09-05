#include "../../includes/cub3d_bonus.h"

t_door	*get_door_in_front_of_player(t_config *config)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < config->doors_count)
	{
		door = get_door_in_front_helper(config, i);
		if (door)
			return (door);
	}
	return (NULL);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 13)
		game->keys.w = 1;
	else if (keycode == 97 || keycode == 0)
		game->keys.a = 1;
	else if (keycode == 115 || keycode == 1)
		game->keys.s = 1;
	else if (keycode == 100 || keycode == 2)
		game->keys.d = 1;
	else if (keycode == 65361 || keycode == 123)
		game->keys.left = 1;
	else if (keycode == 65363 || keycode == 124)
		game->keys.right = 1;
	else if (keycode == 76)
		open_door(game);
	else if (keycode == 65307 || keycode == 53)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 13)
		game->keys.w = 0;
	else if (keycode == 97 || keycode == 0)
		game->keys.a = 0;
	else if (keycode == 115 || keycode == 1)
		game->keys.s = 0;
	else if (keycode == 100 || keycode == 2)
		game->keys.d = 0;
	else if (keycode == 65361 || keycode == 123)
		game->keys.left = 0;
	else if (keycode == 65363 || keycode == 124)
		game->keys.right = 0;
	else if (keycode == 76)
		game->keys.right = 0;
	return (0);
}

int	mouse_move_handler(int x, int y, t_game *game)
{
	int	center_x;
	int	delta_x;

	(void)y;
	if (game->g_mouse_lock == 0)
		return (0);
	center_x = WIDTH / 2;
	if (x == center_x)
		return (0);
	delta_x = x - center_x;
	if (delta_x > 0)
		rotate_right(game);
	else
		rotate_left(game);
	mlx_mouse_move(game->mlx.win_ptr, center_x, HEIGHT / 2);
	return (0);
}

int	mouse_click_handler(int button, int x, int y, t_game *game)
{
	(void)x;
	if (button == 1)
	{
		if (y >= 2)
			game->g_mouse_lock = !game->g_mouse_lock;
	}
	if (game->g_mouse_lock)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
	return (0);
}
