#include "../../includes/cub3d.h"

void	move_forward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		+ game->config.player.dir.x * game->move_speed;
	next_y = game->config.player.pos.y
		+ game->config.player.dir.y * game->move_speed;
	if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x]
		!= '1')
		game->config.player.pos.x = next_x;
	if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x]
		!= '1')
		game->config.player.pos.y = next_y;
}

void	move_backward(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		- game->config.player.dir.x * game->move_speed;
	next_y = game->config.player.pos.y
		- game->config.player.dir.y * game->move_speed;
	if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x]
		!= '1')
		game->config.player.pos.x = next_x;
	if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x]
		!= '1')
		game->config.player.pos.y = next_y;
}

void	strafe_left(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		- game->config.player.plane.x * game->move_speed;
	next_y = game->config.player.pos.y
		- game->config.player.plane.y * game->move_speed;
	if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x]
		!= '1')
		game->config.player.pos.x = next_x;
	if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x]
		!= '1')
		game->config.player.pos.y = next_y;
}

void	strafe_right(t_game *game)
{
	double	next_x;
	double	next_y;

	next_x = game->config.player.pos.x
		+ game->config.player.plane.x * game->move_speed;
	next_y = game->config.player.pos.y
		+ game->config.player.plane.y * game->move_speed;
	if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x]
		!= '1')
		game->config.player.pos.x = next_x;
	if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x]
		!= '1')
		game->config.player.pos.y = next_y;
}
