#include "../../includes/cub3d_bonus.h"

int	draw_opened_door(t_game *game, t_door *door, int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = door->x * CELL_SIZE;
	pixel_y = door->y * CELL_SIZE;
	if (door->side_hit == 1)
	{
		if (draw_opened_door_side_y(game,
				color, pixel_x, pixel_y))
			return (-1);
	}
	else if (door->side_hit == 0)
	{
		if (draw_opened_door_side_x(game,
				color, pixel_x, pixel_y))
			return (-1);
	}
	return (0);
}

int	draw_closed_door(t_game *game, t_door *door, int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = door->x * CELL_SIZE;
	pixel_y = door->y * CELL_SIZE;
	if (door->side_hit == 1)
	{
		if (draw_closed_door_side_y(game, color,
				pixel_x, pixel_y))
			return (-1);
	}
	else if (door->side_hit == 0)
	{
		if (draw_closed_door_side_x(game, color,
				pixel_x, pixel_y))
			return (-1);
	}
	return (0);
}

int	draw_map_door_cell(t_game *game, int map_x, int map_y, int color)
{
	t_door	*door;

	door = find_door(&game->config, map_x, map_y);
	if (!door->is_open)
	{
		if (draw_closed_door(game, door, color))
			return (-1);
	}
	else
	{
		if (draw_opened_door(game, door, color))
			return (-1);
	}
	return (0);
}

int	draw_player_on_the_map(t_game *game, int color)
{
	int	px;
	int	py;
	int	y;
	int	x;

	px = game->config.player.pos.x * CELL_SIZE;
	py = game->config.player.pos.y * CELL_SIZE;
	y = -PLAYER_CELL_SIZE / 2;
	while (y < PLAYER_CELL_SIZE / 2)
	{
		x = -PLAYER_CELL_SIZE / 2;
		while (x < PLAYER_CELL_SIZE / 2)
		{
			if (put_pixel(&game->mlx.screen, START_PIXEL_X + px + x,
					START_PIXEL_Y + py + y, color))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

void	init_fov(t_game *game, t_fov **fov)
{
	*fov = &game->mini_map_fov;
	(*fov)->range = 50.0;
	(*fov)->px = game->config.player.pos.x * CELL_SIZE;
	(*fov)->py = game->config.player.pos.y * CELL_SIZE;
	(*fov)->player_angle = atan2(game->config.player.dir.y,
			game->config.player.dir.x);
	(*fov)->start_angle = (*fov)->player_angle - (FOV / 2.0);
	(*fov)->end_angle = (*fov)->player_angle + (FOV / 2.0);
	(*fov)->step = 0.01;
}
