/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils_bonus_.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:21:58 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/08 12:49:56 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

t_sprite	*find_item(t_config *config, int map_x, int map_y)
{
	int	i;

	i = -1;
	while (++i < config->sprites_count)
	{
		if ((int)config->sprites[i].x == map_x
			&& (int)config->sprites[i].y == map_y)
			return (&config->sprites[i]);
	}
	return (NULL);
}

t_door	*find_door(t_config *config, int map_x, int map_y)
{
	int	i;

	i = -1;
	while (++i < config->doors_count)
	{
		if ((int)config->doors[i].x == map_x
			&& (int)config->doors[i].y == map_y)
			return (&config->doors[i]);
	}
	return (NULL);
}

t_sprite	*detect_item_(t_config *config, int x, int y)
{
	int	i;

	i = -1;
	while (++i < config->sprites_count)
	{
		if ((int)config->sprites[i].x
			== x && (int)config->sprites[i].y == y)
			return (&config->sprites[i]);
	}
	return (NULL);
}

int	draw_item_cell(t_game *game, t_mini_map *m_map, int x, int y)
{
	m_map->item = detect_item_(&game->config, x, y);
	if (m_map->item->active)
	{
		if (draw_square(&game->mlx.screen, m_map->screen_x,
				m_map->screen_y, 0xFFFF00))
			return (-1);
	}
	return (0);
}

int	draw_door_cell(t_game *game, t_mini_map *m_map, int x, int y)
{
	m_map->door = find_door(&game->config, x, y);
	if (!m_map->door->is_open)
	{
		if (draw_square(&game->mlx.screen, m_map->screen_x,
				m_map->screen_y, 0xAAAAAA))
			return (-1);
	}
	return (0);
}

// int	draw_map_wall_cell(t_img *screen, int map_x, int map_y, int color)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	while (++y < CELL_SIZE)
// 	{
// 		x = -1;
// 		while (++x < CELL_SIZE)
// 		{
// 			if (put_pixel(screen, START_PIXEL_X + map_x * CELL_SIZE + x,
// 					START_PIXEL_Y + map_y * CELL_SIZE + y, color))
// 				return (-1);
// 		}
// 	}
// 	return (0);
// }

// int	draw_map_cell_loop(t_game *game, int color, int pixel_x, int pixel_y)
// {
// 	int	x;
// 	int	y;

// 	y = -ITEM_CELL_SIZE / 2;
// 	while (y < ITEM_CELL_SIZE / 2)
// 	{
// 		x = -ITEM_CELL_SIZE / 2;
// 		while (x < ITEM_CELL_SIZE / 2)
// 		{
// 			if (put_pixel(&game->mlx.screen,
// 					START_PIXEL_X + pixel_x + x,
// 					START_PIXEL_Y + pixel_y + y, color))
// 				return (-1);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (0);
// }

// int	draw_map_item_cell(t_game *game, int map_x, int map_y, int color)
// {
// 	t_sprite	*sprite;
// 	int			pixel_x;
// 	int			pixel_y;

// 	sprite = find_item(&game->config, map_x, map_y);
// 	if (sprite == NULL)
// 		return (-1);
// 	pixel_x = sprite->x * CELL_SIZE;
// 	pixel_y = sprite->y * CELL_SIZE;
// 	if (draw_map_cell_loop(game, color,
// 			pixel_x, pixel_y))
// 		return (-1);
// 	return (0);
// }
