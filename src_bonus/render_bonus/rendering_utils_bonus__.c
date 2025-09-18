/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils_bonus__.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:21:51 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/08 12:49:41 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	draw_square(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	size = 9;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (put_pixel(img, x + j, y + i, color))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

// Filled circle
int	draw_filled_circle(t_img *img, int cx, int cy, int r)
{
	int	y;
	int	x;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
			{
				if (put_pixel(img, cx + x, cy + y, 0x528697))
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

// Bresenham line
// C’est le cœur de Bresenham :
// On double l’erreur (e2).
// Si e2 >= dy, alors on avance en x.
// Si e2 <= dx, alors on avance en y.
// L’erreur est mise à jour à chaque fois,
// pour "savoir" si on doit monter ou descendre au prochain pixel.
// C’est ce qui fait que la ligne est continue, bien droite et
// sans trous, peu importe son inclinaison.
int	draw_line_loop(t_img *img, t_line *ln)
{
	int	e2;

	while (1)
	{
		if (put_pixel(img, ln->x0 + 4, ln->y0 + 4, ln->color))
			return (-1);
		if (ln->x0 == ln->x1 && ln->y0 == ln->y1)
			break ;
		e2 = 2 * ln->err;
		if (e2 >= ln->dy)
		{
			ln->err += ln->dy;
			ln->x0 += ln->sx;
		}
		if (e2 <= ln->dx)
		{
			ln->err += ln->dx;
			ln->y0 += ln->sy;
		}
	}
	return (0);
}

int	draw_line(t_img *img, t_line *ln)
{
	ln->dx = abs(ln->x1 - ln->x0);
	ln->dy = -abs(ln->y1 - ln->y0);
	ln->err = ln->dx + ln->dy;
	if (ln->x0 < ln->x1)
		ln->sx = 1;
	else
		ln->sx = -1;
	if (ln->y0 < ln->y1)
		ln->sy = 1;
	else
		ln->sy = -1;
	if (draw_line_loop(img, ln))
		return (-1);
	return (0);
}

int	draw_line_(t_game *game, int center_x, int center_y)
{
	int		dir_x;
	int		dir_y;
	t_line	line_to_draw;

	dir_x = (int)(game->config.player.dir.x * 15);
	dir_y = (int)(game->config.player.dir.y * 15);
	line_to_draw.x0 = center_x;
	line_to_draw.y0 = center_y;
	line_to_draw.x1 = center_x + dir_x;
	line_to_draw.y1 = center_y + dir_y;
	line_to_draw.color = 0xFF0000;
	if (draw_line(&game->mlx.screen, &line_to_draw))
		return (-1);
	return (0);
}
