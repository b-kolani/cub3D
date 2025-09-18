/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_images_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:14:55 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/14 11:14:57 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	destroy_walls_img(t_game *game)
{
	int	z;

	z = -1;
	while (++z < 4)
	{
		if (game->textures[z].img_ptr)
		{
			mlx_destroy_image(game->mlx.mlx_ptr,
				game->textures[z].img_ptr);
			game->textures[z].img_ptr = NULL;
		}
	}
}

void	destroy_doors_img(t_game *game)
{
	int	k;

	k = -1;
	while (++k < 2)
	{
		if (game->door_textures[k].img_ptr)
		{
			mlx_destroy_image(game->mlx.mlx_ptr,
				game->door_textures[k].img_ptr);
			game->door_textures[k].img_ptr = NULL;
		}
	}
}

void	destroy_items_img(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (i++ < SPRITE_TYPE_COUNT)
	{
		j = -1;
		while (++j < game->sprites_frames_count[i])
		{
			if (game->sprite_textures[i][j].img_ptr)
			{
				mlx_destroy_image(game->mlx.mlx_ptr,
					game->sprite_textures[i][j].img_ptr);
				game->sprite_textures[i][j].img_ptr = NULL;
			}
		}
	}
}

void	destroy_all_images(t_game *game)
{
	destroy_walls_img(game);
	destroy_doors_img(game);
	destroy_items_img(game);
	if (game->mlx.screen.img_ptr)
	{
		mlx_destroy_image(game->mlx.mlx_ptr,
			game->mlx.screen.img_ptr);
		game->mlx.screen.img_ptr = NULL;
	}
}

void	clean_exit_and_exit(t_game *game, int status)
{
	if (game)
	{
		destroy_all_images(game);
		if (game->mlx.win_ptr)
		{
			mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
			game->mlx.win_ptr = NULL;
		}
		if (game->gc)
			gc_free_all(game->gc);
	}
	exit(status);
}
