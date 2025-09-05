#include "../../includes/cub3d_bonus.h"

void	detect_item(t_config *config, int x, int y)
{
	int	i;

	i = -1;
	while (++i < config->sprites_count)
	{
		if ((int)config->sprites[i].x == x && (int)config->sprites[i].y == y)
			config->sprites[i].active = false;
	}
}

void	move_forward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		+ game->config.player.dir.x * game->move_speed;
	next_y = game->config.player.pos.y
		+ game->config.player.dir.y * game->move_speed;
	handle_x_movement(game, next_x);
	handle_y_movement(game, next_y);
}

void	move_backward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		- game->config.player.dir.x * game->move_speed;
	next_y = game->config.player.pos.y
		- game->config.player.dir.y * game->move_speed;
	handle_x_movement(game, next_x);
	handle_y_movement(game, next_y);
}

void	strafe_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		- game->config.player.plane.x * game->move_speed;
	next_y = game->config.player.pos.y
		- game->config.player.plane.y * game->move_speed;
	handle_x_movement(game, next_x);
	handle_y_movement(game, next_y);
}

void	strafe_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		+ game->config.player.plane.x * game->move_speed;
	next_y = game->config.player.pos.y
		+ game->config.player.plane.y * game->move_speed;
	handle_x_movement(game, next_x);
	handle_y_movement(game, next_y);
}
