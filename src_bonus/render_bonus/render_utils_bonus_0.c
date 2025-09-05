#include "../../includes/cub3d_bonus.h"

int	loop_check(int *y)
{
	if (*y >= -2 && *y <= 1)
	{
		(*y)++;
		return (-1);
	}
	return (0);
}

int	draw_opened_door_side_x(t_game *game, int color, int pixel_x, int pixel_y)
{
	int	x;
	int	y;

	y = -DOOR_CELL_SIZE;
	while (y < DOOR_CELL_SIZE)
	{
		if (loop_check(&y))
			continue ;
		x = -1;
		while (x < DOOR_CELL_SIZE)
		{
			if (x < -(DOOR_CELL_SIZE / 2) || x >= (DOOR_CELL_SIZE / 2))
			{
				if (put_pixel(&game->mlx.screen,
						START_PIXEL_X + pixel_x + x,
						START_PIXEL_Y + pixel_y + y, color))
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_opened_door_side_y(t_game *game, int color, int pixel_x, int pixel_y)
{
	int	x;
	int	y;

	y = -1;
	while (y < DOOR_CELL_SIZE / 2)
	{
		x = -DOOR_CELL_SIZE;
		while (x < DOOR_CELL_SIZE)
		{
			if (x < -(DOOR_CELL_SIZE / 2)
				|| x >= (DOOR_CELL_SIZE / 2))
			{
				if (put_pixel(&game->mlx.screen,
						START_PIXEL_X + pixel_x + x,
						START_PIXEL_Y + pixel_y + y, color))
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_closed_door_side_x(t_game *game, int color, int pixel_x, int pixel_y)
{
	int	x;
	int	y;

	y = -DOOR_CELL_SIZE;
	while (y < DOOR_CELL_SIZE)
	{
		x = -1;
		while (x < DOOR_CELL_SIZE / 2)
		{
			if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
					START_PIXEL_Y + pixel_y + y, color))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_closed_door_side_y(t_game *game, int color, int pixel_x, int pixel_y)
{
	int	x;
	int	y;

	y = -1;
	while (y < DOOR_CELL_SIZE / 2)
	{
		x = -DOOR_CELL_SIZE;
		while (x < DOOR_CELL_SIZE)
		{
			if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
					START_PIXEL_Y + pixel_y + y, color))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
