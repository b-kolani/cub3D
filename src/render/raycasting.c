/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:53:59 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/10 18:12:53 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_config *config, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir.x = config->player.dir.x + config->player.plane.x
		* camera_x;
	ray->ray_dir.y = config->player.dir.y + config->player.plane.y
		* camera_x;
	if (fabs(ray->ray_dir.x) < 1e-6)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (fabs(ray->ray_dir.y) < 1e-6)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
}

void	init_dda(t_ray *ray, t_config *config)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (config->player.pos.x - ray->map_x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = ((ray->map_x + 1) - config->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (config->player.pos.y - ray->map_y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = ((ray->map_y + 1) - config->player.pos.y)
			* ray->delta_dist.y;
	}
}

void	compute_projection(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	ray->column.line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->column.draw_start = (-(ray->column.line_height) / 2) + (HEIGHT / 2);
	ray->column.draw_end = (ray->column.line_height / 2) + (HEIGHT / 2);
}

int	raycasting(t_game *game)
{
	t_ray	ray;
	int		x;

	x = -1;
	while (++x < WIDTH)
	{
		ray.map_x = (int)game->config.player.pos.x;
		ray.map_y = (int)game->config.player.pos.y;
		init_ray(&ray, &game->config, x);
		init_dda(&ray, &game->config);
		perform_dda(&ray, &game->config);
		compute_projection(&ray);
		if (draw_column(&ray, game, x))
			return (-1);
	}
	return (0);
}

int	close_window(t_game *game)
{
	printf("Window closed: exiting...\n");
	if (game->mlx.screen.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.screen.img_ptr);
	if (game->mlx.mlx_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
	gc_free(game);
	exit(0);
}
