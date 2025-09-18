/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:19:11 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 15:19:13 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	update_player(t_game *game)
{
	game->move_speed = 0.1;
	game->rot_speed = 0.05;
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		strafe_left(game);
	if (game->keys.d)
		strafe_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	return (0);
}

void	handle_x_movement(t_game *game, double next_x)
{
	t_door	*door;

	door = NULL;
	if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x]
		!= '1')
	{
		if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x]
			== '4')
		{
			door = find_door(&game->config,
					(int)next_x, (int)game->config.player.pos.y);
			if (door && door->is_open)
				game->config.player.pos.x = next_x;
		}
		else
		{
			if (game->config.map.grid[(int)game->config.player.pos.y]
				[(int)next_x] == '3')
				detect_item(&game->config, next_x, game->config.player.pos.y);
			game->config.player.pos.x = next_x;
		}
	}
}

void	handle_y_movement(t_game *game, double next_y)
{
	t_door	*door;

	door = NULL;
	if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x]
		!= '1')
	{
		if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x]
			== '4')
		{
			door = find_door(&game->config,
					(int)game->config.player.pos.x, (int)next_y);
			if (door && door->is_open)
				game->config.player.pos.y = next_y;
		}
		else
		{
			if (game->config.map.grid[(int)next_y]
				[(int)game->config.player.pos.x] == '3')
				detect_item(&game->config,
					(int)game->config.player.pos.x, (int)next_y);
			game->config.player.pos.y = next_y;
		}
	}
}
