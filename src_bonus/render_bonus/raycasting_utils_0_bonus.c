/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_0_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:33 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 15:20:35 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	dda_hit_door(t_config *config, t_ray *ray)
{
	t_door	*door;

	door = NULL;
	if (config->map.grid[ray->map_y][ray->map_x] == '4')
	{
		ray->hit = 1;
		door = find_door(config, ray->map_x, ray->map_y);
		if (ray->side == 0)
			door->side_hit = 0;
		else
			door->side_hit = 1;
		if (door && door->door_offset >= 1.0)
		{
			ray->hit = 0;
			return (0);
		}
		ray->text_type = DOOR_TYPE;
		ray->door_x = ray->map_x;
		ray->door_y = ray->map_y;
		ray->door_hit = door;
	}
	return (1);
}

void	get_x_side_door_dir_text(t_ray *ray, t_door *door, int *dir_tex)
{
	if (ray->ray_dir.x > 0)
	{
		if (!door->is_open)
			*dir_tex = 0;
		else
			*dir_tex = 1;
	}
	else
	{
		if (!door->is_open)
			*dir_tex = 0;
		else
			*dir_tex = 1;
	}
}

void	get_y_side_door_dir_text(t_ray *ray, t_door *door, int *dir_tex)
{
	if (ray->ray_dir.y < 0)
	{
		if (!door->is_open)
			*dir_tex = 0;
		else
			*dir_tex = 1;
	}
	else
	{
		if (!door->is_open)
			*dir_tex = 0;
		else
			*dir_tex = 1;
	}
}

void	init_text_helper(t_config *config, t_ray *ray, double *wall_x)
{
	if (ray->text_type == WALL_TYPE)
	{
		if (ray->side == 0)
			*wall_x = config->player.pos.y
				+ ray->perp_wall_dist * ray->ray_dir.y;
		else
			*wall_x = config->player.pos.x
				+ ray->perp_wall_dist * ray->ray_dir.x;
	}
	if (ray->text_type == DOOR_TYPE)
	{
		if (ray->side == 0)
			*wall_x = (config->player.pos.y
					+ ray->perp_wall_dist * ray->ray_dir.y)
				- ray->door_hit->door_offset;
		else
			*wall_x = (config->player.pos.x
					+ ray->perp_wall_dist * ray->ray_dir.x)
				- ray->door_hit->door_offset;
	}
}

int	draw_col_helper(t_game *game, t_ray *ray, t_img *texture, int x)
{
	int	y;

	y = ray->column.draw_start;
	while (y <= ray->column.draw_end)
	{
		texture->tex_y = (int)texture->tex_pos;
		if (texture->tex_y < 0)
			texture->tex_y = 0;
		if (texture->tex_y >= texture->height)
			texture->tex_y = texture->height - 1;
		texture->tex_pos += texture->step;
		ray->column.color = get_texture_pixels(texture,
				texture->tex_x, texture->tex_y);
		ray->column.color = apply_shadow(ray->column.color,
				ray->perp_wall_dist, ray->side);
		if (put_pixel(&game->mlx.screen, x, y, ray->column.color))
			return (print_err("Ray casting error\n"));
		y++;
	}
	return (0);
}
