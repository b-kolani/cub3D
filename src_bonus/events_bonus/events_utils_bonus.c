/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:18:24 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 15:18:30 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

t_door	*get_door_help_(t_config *config, int idx,
	t_door *doors, t_vector *player_pos)
{
	if (((int)player_pos->y + 1 <= config->map.height - 1)
		&& config->map.grid[(int)player_pos->y + 1][(int)player_pos->x] == '4'
		&& (int)player_pos->x == (int)doors[idx].x
		&& (int)(player_pos->y + 1) == (int)doors[idx].y)
		return (&doors[idx]);
	else if (((int)player_pos->y - 1 >= 0)
		&& config->map.grid[(int)player_pos->y - 1][(int)player_pos->x] == '4'
		&& (int)player_pos->x == (int)doors[idx].x
		&& (int)(player_pos->y - 1) == (int)doors[idx].y)
		return (&doors[idx]);
	else if (((int)player_pos->x + 1 <= config->map.width - 1)
		&& config->map.grid[(int)player_pos->y][(int)player_pos->x + 1] == '4'
		&& (int)(player_pos->x + 1) == (int)doors[idx].x
		&& (int)player_pos->y == (int)doors[idx].y)
		return (&doors[idx]);
	else if (((int)player_pos->x - 1 >= 0)
		&& config->map.grid[(int)player_pos->y][(int)player_pos->x - 1] == '4'
		&& (int)(player_pos->x - 1) == (int)doors[idx].x
		&& (int)player_pos->y == (int)doors[idx].y)
		return (&doors[idx]);
	return (NULL);
}

t_door	*get_door_in_front_helper(t_config *config, int idx)
{
	t_door		*doors;
	t_vector	*player_pos;
	t_door		*door;

	doors = config->doors;
	player_pos = &config->player.pos;
	door = get_door_help_(config, idx, doors, player_pos);
	if (!door)
		return (NULL);
	return (door);
}

void	open_door(t_game *game)
{
	t_door	*door;

	door = get_door_in_front_of_player(&game->config);
	if (door)
	{
		if (!door->is_open && door->door_offset == 0.0)
			door->is_open = true;
		else if (door->is_open && door->door_offset == 1.0)
			door->is_open = false;
	}
}
