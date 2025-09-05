#include "../../includes/cub3d_bonus.h"

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->config.player.dir.x;
	old_plane_x = game->config.player.plane.x;
	game->config.player.dir.x = old_dir_x * cos(-game->rot_speed)
		- game->config.player.dir.y * sin(-game->rot_speed);
	game->config.player.dir.y = old_dir_x * sin(-game->rot_speed)
		+ game->config.player.dir.y * cos(-game->rot_speed);
	game->config.player.plane.x = old_plane_x * cos(-game->rot_speed)
		- game->config.player.plane.y * sin(-game->rot_speed);
	game->config.player.plane.y = old_plane_x * sin(-game->rot_speed)
		+ game->config.player.plane.y * cos(-game->rot_speed);
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->config.player.dir.x;
	old_plane_x = game->config.player.plane.x;
	game->config.player.dir.x = old_dir_x * cos(game->rot_speed)
		- game->config.player.dir.y * sin(game->rot_speed);
	game->config.player.dir.y = old_dir_x * sin(game->rot_speed)
		+ game->config.player.dir.y * cos(game->rot_speed);
	game->config.player.plane.x = old_plane_x * cos(game->rot_speed)
		- game->config.player.plane.y * sin(game->rot_speed);
	game->config.player.plane.y = old_plane_x * sin(game->rot_speed)
		+ game->config.player.plane.y * cos(game->rot_speed);
}
