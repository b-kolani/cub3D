/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:41:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 13:43:24 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys.w = 1;
	if (keycode == 0)
		game->keys.a = 1;
	else if (keycode == 1)
		game->keys.s = 1;
	else if (keycode == 2)
		game->keys.d = 1;
	else if (keycode == 123)
		game->keys.left = 1;
	else if (keycode == 124)
		game->keys.right = 1;
	else if (keycode == 53)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 13)
		game->keys.w = 0;
	else if (keycode == 0)
		game->keys.a = 0;
	else if (keycode == 1)
		game->keys.s = 0;
	else if (keycode == 2)
		game->keys.d = 0;
	else if (keycode == 123)
		game->keys.left = 0;
	else if (keycode == 124)
		game->keys.right = 0;
	return (0);
}
