#include "../../includes/cub3d_bonus.h"

void	perform_dda(t_ray *ray, t_config *config)
{
	ray->hit = 0;
	ray->side = 0;
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (config->map.grid[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
			ray->text_type = WALL_TYPE;
		}
		if (!dda_hit_door(config, ray))
			continue ;
	}
}

t_img	*get_dir_texture(t_ray *ray, t_img *textures)
{
	int	dir_tex;

	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			dir_tex = EAST;
		else
			dir_tex = WEST;
	}
	else
	{
		if (ray->ray_dir.y < 0)
			dir_tex = NORTH;
		else
			dir_tex = SOUTH;
	}
	return (&textures[dir_tex]);
}

t_img	*get_door_dir_text(t_ray *ray, t_door *door, t_img *textures)
{
	int	dir_tex;

	if (ray->side == 0)
		get_x_side_door_dir_text(ray, door, &dir_tex);
	else
		get_y_side_door_dir_text(ray, door, &dir_tex);
	return (&textures[dir_tex]);
}

int	initialize_texture(t_ray *ray, t_img *texture, t_config *config)
{
	double	wall_x;

	wall_x = 0.0;
	if (!ray || !texture)
		return (print_err("Raycasting error: "
				"texture initialization failed\n"));
	init_text_helper(config, ray, &wall_x);
	wall_x -= floor(wall_x);
	texture->tex_x = (int)(wall_x * texture->width);
	if ((ray->side == 0 && ray->ray_dir.x > 0)
		|| (ray->side == 1 && ray->ray_dir.y < 0))
		texture->tex_x = texture->width - texture->tex_x - 1;
	texture->step = 1.0 * texture->height / ray->column.line_height;
	texture->tex_pos = (ray->column.draw_start - HEIGHT / 2
			+ ray->column.line_height / 2) * texture->step;
	return (0);
}

int	draw_column(t_ray *ray, t_game *game, int x)
{
	t_img	*texture;
	t_door	*door;

	texture = NULL;
	door = find_door(&game->config, ray->door_x, ray->door_y);
	if (ray->text_type == WALL_TYPE)
		texture = get_dir_texture(ray, game->textures);
	else if (ray->text_type == DOOR_TYPE)
		texture = get_door_dir_text(ray, door,
				game->door_textures);
	if (ray->column.draw_start < 0)
		ray->column.draw_start = 0;
	if (ray->column.draw_end >= HEIGHT)
		ray->column.draw_end = HEIGHT - 1;
	if (initialize_texture(ray, texture, &game->config))
		return (-1);
	if (draw_col_helper(game, ray, texture, x))
		return (-1);
	return (0);
}
