#include "../../includes/cub3d_bonus.h"

void	init_fov_in_loop(t_fov *fov, double angle, double r)
{
	fov->intersection = 0;
	fov->dx = cos(angle);
	fov->dy = sin(angle);
	fov->x = (int)(fov->px + fov->dx * r);
	fov->y = (int)(fov->py + fov->dy * r);
	fov->map_x = fov->x / CELL_SIZE;
	fov->map_y = fov->y / CELL_SIZE;
}

int	check_fov_params(t_game *game, t_fov *fov)
{
	t_door	*door;

	if (fov->map_x < 0 || fov->map_x > game->config.map.width - 1
		|| fov->map_y < 0 || fov->map_y > game->config.map.height - 1)
		return (-1);
	if (!ft_strchr("0134", game->config.map.grid[fov->map_y][fov->map_x])
		|| (game->config.map.grid[fov->map_y][fov->map_x] == '0'
		&& game->config.map.grid[fov->map_y][fov->map_x + 1] == '1'
		&& game->config.map.grid[fov->map_y][fov->map_x - 1] == '1'
		&& game->config.map.grid[fov->map_y - 1][fov->map_x] == '1'
		&& game->config.map.grid[fov->map_y + 1][fov->map_x] == '1'
		))
		fov->intersection = 1;
	if (game->config.map.grid[fov->map_y][fov->map_x] == '1'
		|| fov->intersection)
		return (-1);
	if (game->config.map.grid[fov->map_y][fov->map_x] == '4')
	{
		door = find_door(&game->config, fov->map_x, fov->map_y);
		if (door && !door->is_open)
			return (-1);
	}
	return (0);
}

int	draw_mini_map_fov(t_game *game)
{
	t_fov	*fov;
	double	r;
	double	angle;

	fov = NULL;
	init_fov(game, &fov);
	r = 0;
	angle = fov->start_angle;
	while (angle <= fov->end_angle)
	{
		r = 0;
		while (r <= fov->range)
		{
			init_fov_in_loop(fov, angle, r);
			if (check_fov_params(game, fov))
				break ;
			if (put_pixel(&game->mlx.screen, fov->x, fov->y, 0xf5b342))
				return (-1);
			r += 1.0;
		}
		angle += fov->step;
	}
	return (0);
}

int	draw_mini_map_check(t_game *game, int map_x, int map_y)
{
	if (game->config.map.grid[map_y][map_x] == '1')
	{
		if (draw_map_wall_cell(&game->mlx.screen,
				map_x, map_y, 0xFF9000))
			return (-1);
	}
	else if (game->config.map.grid[map_y][map_x] == '3')
	{
		if (is_item_active(&game->config, map_x, map_y))
		{
			if (draw_map_item_cell(game, map_x, map_y, 0x00FF00))
				return (-1);
		}
	}
	else if (game->config.map.grid[map_y][map_x] == '4')
	{
		if (draw_map_door_cell(game, map_x, map_y, 0XFF0000))
			return (-1);
	}
	return (0);
}

int	draw_mini_map(t_game *game)
{
	int	map_x;
	int	map_y;

	map_y = -1;
	if (game->config.map.height > HEIGHT / 10
		|| game->config.map.width > WIDTH / 10)
		return (print_err("Failed to draw mini "
				"map; out of window sizes bounds\n"));
	while (++map_y < game->config.map.height)
	{
		map_x = -1;
		while (++map_x < (int)ft_strlen(game->config.map.grid[map_y]))
		{
			if (draw_mini_map_check(game, map_x, map_y))
				return (-1);
		}
	}
	if (draw_player_on_the_map(game, 0x0000FF))
		return (-1);
	if (draw_mini_map_fov(game))
		return (-1);
	return (0);
}
