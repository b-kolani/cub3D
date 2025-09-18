/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:21:18 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/08 18:15:28 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_mini_map_params(t_game *game,
	t_mini_map *mini_map, int x, int y)
{
	mini_map->dx = (x + 0.5 - game->config.player.pos.x)
		* MINIMAP_SCALE;
	mini_map->dy = (y + 0.5 - game->config.player.pos.y)
		* MINIMAP_SCALE;
	mini_map->screen_x = mini_map->center_x
		+ (int)mini_map->dx;
	mini_map->screen_y = mini_map->center_y
		+ (int)mini_map->dy;
}

int	loop_checker(t_game *game, t_mini_map *m_map, int x, int y)
{
	if (m_map->dx * m_map->dx + m_map->dy * m_map->dy
		<= MINIMAP_RADIUS * MINIMAP_RADIUS)
	{
		if (game->config.map.grid[y][x] == '1')
		{
			if (draw_square(&game->mlx.screen, m_map->screen_x,
					m_map->screen_y, 0x000000))
				return (-1);
		}
		else if (game->config.map.grid[y][x] == '3')
		{
			if (draw_item_cell(game, m_map, x, y))
				return (-1);
		}
		else if (game->config.map.grid[y][x] == '4')
		{
			if (draw_door_cell(game, m_map, x, y))
				return (-1);
		}
	}
	return (0);
}

int	init_m_map(t_mini_map *m_map, t_img screen)
{
	m_map->center_x = MINIMAP_RADIUS + 20;
	m_map->center_y = HEIGHT - MINIMAP_RADIUS - 20;
	if (draw_filled_circle(&screen, m_map->center_x,
			m_map->center_y, MINIMAP_RADIUS + 10))
		return (-1);
	return (0);
}

int	draw_mini_map(t_game *game, t_img screen)
{
	t_mini_map	mini_map;
	int			x;
	int			y;

	if (init_m_map(&mini_map, screen))
		return (-1);
	y = 0;
	while (y < game->config.map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->config.map.grid[y]))
		{
			init_mini_map_params(game, &mini_map, x, y);
			if (loop_checker(game, &mini_map, x, y))
				return (-1);
			x++;
		}
		y++;
	}
	if (draw_square(&screen, mini_map.center_x,
			mini_map.center_y, 0x0000FF))
		return (-1);
	if (draw_line_(game, mini_map.center_x, mini_map.center_y))
		return (-1);
	return (0);
}
