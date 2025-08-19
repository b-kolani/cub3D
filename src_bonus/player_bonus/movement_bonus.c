#include "../../includes/cub3d_bonus.h"

int update_player(t_game *game)
{

	// double	move_speed = 0.1;
	// double	rot_speed = 0.05;
    game->move_speed = 0.1;
    game->rot_speed = 0.05;
    // printf("Current tile: %c\n", game->config.map.grid[(int)game->config.player.pos.y][(int)game->config.player.pos.x]);
    // printf("Player direction: %f %f\n", game->config.player.pos.x, game->config.player.pos.y);
	// Avancer (W)
    // printf("Position initiale: %c\n", 
    // game->config.map.grid[(int)game->config.player.pos.y][(int)game->config.player.pos.x]);
	if (game->keys.w)
        move_forward(game);
        // move_player(game, game->config.player.dir);
	// {
	// 	double next_x = game->config.player.pos.x + game->config.player.dir.x * game->move_speed;
	// 	double next_y = game->config.player.pos.y + game->config.player.dir.y * game->move_speed;
	// 	// if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
	// 	// 	game->config.player.pos.y = next_y;
	// 	// if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
	// 	// 	game->config.player.pos.x = next_x;
    //     if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
    //     {
    //         game->config.player.pos.x = next_x;
    //         game->config.player.pos.y = next_y;
    //     }
	// }

	// Reculer (S)
	if (game->keys.s)
        move_backward(game);
        // move_player(game, game->config.player.dir);
	// {
	// 	double next_x = game->config.player.pos.x - game->config.player.dir.x * game->move_speed;
	// 	double next_y = game->config.player.pos.y - game->config.player.dir.y * game->move_speed;
    //     if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
    //     {
    //         game->config.player.pos.y = next_y;
    //         game->config.player.pos.x = next_x;
    //     }
	// 	// if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
	// 	// 	game->config.player.pos.y = next_y;
	// 	// if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
	// 	// 	game->config.player.pos.x = next_x;
	// }

    // Strafe à gauche (A)
    if (game->keys.a)
        strafe_left(game);
        // move_player(game, game->config.player.dir);
    // {
	//     double next_x = game->config.player.pos.x - game->config.player.plane.x * game->move_speed;
	//     double next_y = game->config.player.pos.y - game->config.player.plane.y * game->move_speed;
	//     if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
	// 	    game->config.player.pos.y = next_y;
	//     if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
	// 	    game->config.player.pos.x = next_x;
    // }

    // Strafe à droite (D)
    if (game->keys.d)
        strafe_right(game);
        // move_player(game, game->config.player.dir);
    // {
	//     double next_x = game->config.player.pos.x + game->config.player.plane.x * game->move_speed;
	//     double next_y = game->config.player.pos.y + game->config.player.plane.y * game->move_speed;
	//     if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
	// 	    game->config.player.pos.y = next_y;
	//     if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
	// 	    game->config.player.pos.x = next_x;
    // }

	// Tourner à gauche (←)
    if (game->keys.left)
        rotate_left(game);
        // rotate(game, -1);
    // {
	//     double old_dir_x = game->config.player.dir.x;
	//     game->config.player.dir.x = game->config.player.dir.x * cos(-game->rot_speed) - game->config.player.dir.y * sin(-game->rot_speed);
	//     game->config.player.dir.y = old_dir_x * sin(-game->rot_speed) + game->config.player.dir.y * cos(-game->rot_speed);

	//     double old_plane_x = game->config.player.plane.x;
	//     game->config.player.plane.x = game->config.player.plane.x * cos(-game->rot_speed) - game->config.player.plane.y * sin(-game->rot_speed);
	//     game->config.player.plane.y = old_plane_x * sin(-game->rot_speed) + game->config.player.plane.y * cos(-game->rot_speed);
    // }

    // Tourner à droite (→)
    if (game->keys.right)
        rotate_right(game);
        // rotate(game, 1);
    // {
	//     double old_dir_x = game->config.player.dir.x;
	//     game->config.player.dir.x = game->config.player.dir.x * cos(game->rot_speed) - game->config.player.dir.y * sin(game->rot_speed);
	//     game->config.player.dir.y = old_dir_x * sin(game->rot_speed) + game->config.player.dir.y * cos(game->rot_speed);

	//     double old_plane_x = game->config.player.plane.x;
	//     game->config.player.plane.x = game->config.player.plane.x * cos(game->rot_speed) - game->config.player.plane.y * sin(game->rot_speed);
	//     game->config.player.plane.y = old_plane_x * sin(game->rot_speed) + game->config.player.plane.y * cos(game->rot_speed);
    // }

    // Pour chaque touche pressee appelee la
    // la fonction correspondante
    // if (game->keys.w)
    //     printf("KEY W: %d\n", game->keys.w);
    // else
    //     printf("W KEY RELEASED\n");
    // if (game->keys.s)
    //     printf("KEY S: %d\n", game->keys.s);
    // else if (game->keys.a)
    //     printf("KEY A: %d\n", game->keys.a);
    // else if (game->keys.d)
    //     printf("KEY D: %d\n", game->keys.d);
    // else if (game->keys.left)
    //     printf("LEFT ARROW KEY: %d\n", game->keys.left);
    // else if (game->keys.right)
    //     printf("RIGHT ARROW KEY: %d\n", game->keys.right);
    return (0);
}

void    update_enemy_position(t_game *game, t_sprite *enemy)
{
    double  dx;
    double  dy;
    double dist;
    double move_x;
    double move_y;
    int    next_x;
    int    next_y;

    dx = enemy->x - game->config.player.pos.x;
    dy = enemy->y - game->config.player.pos.y;
    dist = sqrt(dx * dx + dy * dy);
    move_x = (dx / dist) * 0.1;
    move_y = (dy / dist) * 0.1;
    next_x = (int)(enemy->x + move_x);
    next_y = (int)(enemy->y + move_y);
    if (dist > 0.5)
    {
        if (game->config.map.grid[next_y][next_x] != '1')
        {
            enemy->x += move_x;
            enemy->y += move_y;
        }
        // else 
        // {
        //     enemy->x -= (dx / dist) * 0.1;
        //     enemy->y -= (dy / dist) * 0.1;
        // }
    }
}

// void    move_enemies(t_game *game)
// {
//     int      i;
//     t_sprite *sprites;

//     i = -1;
//     sprites = game->config.sprites;
//     while (++i < game->config.sprites_count)
//     {
//         if (sprites[i].type == ENEMY_TYPE && sprites[i].active) 
//         {
 
//             update_enemy_position(game, &sprites[i]);

//         }
//     }
// }
