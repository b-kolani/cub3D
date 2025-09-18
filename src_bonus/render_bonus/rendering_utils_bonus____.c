/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils_bonus____.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:21:37 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 15:21:39 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	render_all_sprites(t_game *game)
{
	t_sprite	*sprites;
	int			sprites_count;
	int			i;

	i = -1;
	sprites = game->config.sprites;
	sprites_count = game->config.sprites_count;
	while (++i < sprites_count)
	{
		if (sprites[i].active && sprites[i].type == ITEM_TYPE)
			project_and_render_sprite(game, &sprites[i]);
	}
}

void	calculate_dist_camera_to_sprite(t_config *config)
{
	int		i;
	double	dx;
	double	dy;

	i = -1;
	while (++i < config->sprites_count)
	{
		dx = config->sprites[i].x - config->player.pos.x;
		dy = config->sprites[i].y - config->player.pos.y;
		config->sprites[i].distance = dx * dx + dy * dy;
	}
}

void	update_sprites_animation(t_game *game)
{
	double		anim_speed;
	t_sprite	*sprites;
	int			count;
	int			i;

	anim_speed = 0.1;
	sprites = game->config.sprites;
	count = game->config.sprites_count;
	i = -1;
	while (++i < count)
	{
		if (sprites[i].type == ITEM_TYPE
			&& sprites[i].active)
		{
			sprites[i].anim_timer += game->config.delta_time;
			if (sprites[i].anim_timer > anim_speed)
			{
				sprites[i].anim_timer = 0;
				sprites[i].anim_index++;
				if (sprites[i].anim_index
					>= game->sprites_frames_count[sprites[i].type])
					sprites[i].anim_index = 0;
			}
		}
	}
}

void	update_door_anim(t_door *door, double delta_time)
{
	double	speed;

	speed = 1.0;
	if (door->is_open && door->door_offset < 1.0)
		door->door_offset += delta_time * speed;
	else if (!door->is_open && door->door_offset > 0.0)
		door->door_offset -= delta_time * speed;
	if (door->door_offset < 0.0)
		door->door_offset = 0.0;
	else if (door->door_offset > 1.0)
		door->door_offset = 1.0;
}

void	update_all_doors(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->doors_count)
		update_door_anim(&config->doors[i], config->delta_time);
}
