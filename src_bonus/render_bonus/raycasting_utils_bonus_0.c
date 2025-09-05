#include "../../includes/cub3d_bonus.h"

int	apply_shadow(int color, double distance, int side)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	factor = 1.0 / (1.0 + distance * 0.1);
	if (factor < 0.2)
		factor = 0.2;
	if (side == 1)
		factor *= 0.7;
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

int	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (print_err("mlx error: Failed to put pixel\n"));
	dst = img->img_data_addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

int	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < (HEIGHT / 2))
			{
				if (put_pixel(&game->mlx.screen,
						x, y, game->config.ceil_color))
					return (-1);
			}
			else
			{
				if (put_pixel(&game->mlx.screen,
						x, y, game->config.floor_color))
					return (-1);
			}
		}
	}
	return (0);
}

int	get_texture_pixels(t_img *tex, int x, int y)
{
	char	*pixel_addr;
	int		color;

	pixel_addr = tex->img_data_addr + (y * tex->line_length + x
			* (tex->bits_per_pixel / 8));
	color = *(unsigned int *)pixel_addr;
	return (color);
}

int	is_item_active(t_config *config, int x, int y)
{
	int	i;

	i = -1;
	while (++i < config->sprites_count)
	{
		if ((int)config->sprites[i].x
			== x && (int)config->sprites[i].y == y)
		{
			if (config->sprites[i].active)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}
