/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:53:06 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 13:53:27 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_img	load_texture(t_game *game, char *file)
{
	t_img	tex;

	tex.img_ptr = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			file, &tex.width, &tex.height);
	if (!tex.img_ptr)
	{
		gc_free(game);
		exit(-1);
	}
	tex.img_data_addr = mlx_get_data_addr(tex.img_ptr, &tex.bits_per_pixel,
			&tex.line_length, &tex.endian);
	if (!tex.img_data_addr)
	{
		gc_free(game);
		exit(-1);
	}
	return (tex);
}
