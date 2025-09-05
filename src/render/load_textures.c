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
