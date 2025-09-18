/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:12:34 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 17:44:38 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	draw_col_checker(t_game *game, t_img *texture, t_ray *ray)
{
	if (ray->column.draw_start < 0)
		ray->column.draw_start = 0;
	if (ray->column.draw_end >= HEIGHT)
		ray->column.draw_end = HEIGHT - 1;
	if (initialize_texture(ray, texture, &game->config))
		return (-1);
	return (0);
}
