#include "../../includes/cub3d.h"

int	update_player(t_game *game)
{
	game->move_speed = 0.1;
	game->rot_speed = 0.05;
	if (game->keys.w)
		move_forward(game);
	if (game->keys.s)
		move_backward(game);
	if (game->keys.a)
		strafe_left(game);
	if (game->keys.d)
		strafe_right(game);
	if (game->keys.left)
		rotate_left(game);
	if (game->keys.right)
		rotate_right(game);
	return (0);
}
