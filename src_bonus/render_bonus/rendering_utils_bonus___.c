#include "../../includes/cub3d_bonus.h"

void	init_params(t_game *game, int *type, int *frame, t_sprite*sprite)
{
	t_player	player;
	double		inv_det;

	*type = sprite->type;
	*frame = sprite->anim_index;
	player = game->config.player;
	sprite->dx = sprite->x - player.pos.x;
	sprite->dy = sprite->y - player.pos.y;
	inv_det = 1.0 / (player.plane.x * player.dir.y
			- player.dir.x * player.plane.y);
	sprite->transform_x = inv_det
		* (player.dir.y * sprite->dx - player.dir.x * sprite->dy);
	sprite->transform_y = inv_det
		* (-player.plane.y * sprite->dx + player.plane.x * sprite->dy);
	sprite->sprite_screen_x = (int)((WIDTH / 2)
			* (1 + sprite->transform_x / sprite->transform_y));
}

void	check_params(t_sprite *sprite)
{
	if (sprite->type == 2)
		sprite->sprite_height = fabs(HEIGHT / sprite->transform_y / 4);
	else
		sprite->sprite_height = fabs(HEIGHT / sprite->transform_y);
	sprite->draw_start_y = fmax(0,
			-(sprite->sprite_height / 2) + (HEIGHT / 2));
	sprite->draw_end_y = fmin(HEIGHT - 1,
			(sprite->sprite_height / 2) + (HEIGHT / 2));
	if (sprite->type == 2)
		sprite->sprite_width = fabs(HEIGHT / sprite->transform_y / 4);
	else
		sprite->sprite_width = fabs(HEIGHT / sprite->transform_y);
}

void	proj_loop(t_game *game, t_img *texture, t_sprite *sprite, int stripe)
{
	int	y;
	int	d;
	int	color;

	texture->tex_x = (int)((stripe
				- (-sprite->sprite_width / 2 + sprite->sprite_screen_x))
			* texture->width / sprite->sprite_width);
	if (texture->tex_x < 0)
		texture->tex_x = 0;
	else if (texture->tex_x >= texture->width)
		texture->tex_x = texture->width - 1;
	y = sprite->draw_start_y;
	while (y < sprite->draw_end_y)
	{
		d = (y - sprite->draw_start_y);
		texture->tex_y = (d * texture->height) / sprite->sprite_height;
		if (texture->tex_y < 0)
			texture->tex_y = 0;
		else if (texture->tex_y >= texture->height)
			texture->tex_y = texture->height - 1;
		color = get_texture_pixels(texture, texture->tex_x, texture->tex_y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(&game->mlx.screen, stripe, y, color);
		y++;
	}
}

int	project_and_render_sprite(t_game *game, t_sprite *sprite)
{
	int		type;
	int		frame;
	t_img	*texture;
	int		stripe;

	init_params(game, &type, &frame, sprite);
	check_params(sprite);
	sprite->draw_start_x = fmax(0, -sprite->sprite_width
			/ 2 + sprite->sprite_screen_x);
	sprite->draw_end_x = fmin(WIDTH - 1, sprite->sprite_width
			/ 2 + sprite->sprite_screen_x);
	texture = &game->sprite_textures[type][frame];
	stripe = sprite->draw_start_x;
	while (stripe < sprite->draw_end_x)
	{
		if (sprite->transform_y > 0 && stripe >= 0 && stripe < WIDTH
			&& sprite->transform_y < game->config.z_buffer[stripe])
		{
			proj_loop(game, texture, sprite, stripe);
		}
		stripe++;
	}
	return (0);
}

void	sort_sprites_by_distance(t_sprite *sprites, int count)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = -1;
	while (++i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (sprites[i].distance < sprites[j].distance)
			{
				tmp = sprites[i];
				sprites[i] = sprites[j];
				sprites[j] = tmp;
			}
			j++;
		}
	}
}
