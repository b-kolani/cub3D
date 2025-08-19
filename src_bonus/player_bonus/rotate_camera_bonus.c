#include "../../includes/cub3d_bonus.h"

// TOURNER LA CAMERA VERS LA GAUCHE
void    rotate_left(t_game *game)
{
    double  old_dir_x;
    double  old_plane_x;

    // printf("Coord de Pos: %d %d\n", (int)game->config.player.pos.x, (int)game->config.player.pos.y);
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

// TOURNER LA CAMERA VERS L ADROITE
void    rotate_right(t_game *game)
{
    double  old_dir_x;
    double  old_plane_x;

    // printf("Coord de Pos: %d %d\n", (int)game->config.player.pos.x, (int)game->config.player.pos.y);
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

// void    mouse_rotate_left(t_game *game, int rot_speed)
// {
//     double  old_dir_x;
//     double  old_plane_x;

//     // printf("Coord de Pos: %d %d\n", (int)game->config.player.pos.x, (int)game->config.player.pos.y);
//     old_dir_x = game->config.player.dir.x;
//     old_plane_x = game->config.player.plane.x;
//     game->config.player.dir.x = old_dir_x * cos(-rot_speed) 
//         - game->config.player.dir.y * sin(-rot_speed);
//     game->config.player.dir.y = old_dir_x * sin(-rot_speed) 
//         + game->config.player.dir.y * cos(-rot_speed);
//     game->config.player.plane.x = old_plane_x * cos(-rot_speed) 
//         - game->config.player.plane.y * sin(-rot_speed);
//     game->config.player.plane.y = old_plane_x * sin(-rot_speed) 
//         + game->config.player.plane.y * cos(-rot_speed);
// }

// TOURNER LA CAMERA VERS L ADROITE
// void    mouse_rotate_right(t_game *game, int rot_speed)
// {
//     double  old_dir_x;
//     double  old_plane_x;

//     // printf("Coord de Pos: %d %d\n", (int)game->config.player.pos.x, (int)game->config.player.pos.y);
//     old_dir_x = game->config.player.dir.x;
//     old_plane_x = game->config.player.plane.x;
//     game->config.player.dir.x = old_dir_x * cos(rot_speed)
//         - game->config.player.dir.y * sin(rot_speed);
//     game->config.player.dir.y = old_dir_x * sin(rot_speed)
//         + game->config.player.dir.y * cos(rot_speed);
//     game->config.player.plane.x = old_plane_x * cos(rot_speed)
//         - game->config.player.plane.y * sin(rot_speed);
//     game->config.player.plane.y = old_plane_x * sin(rot_speed)
//         + game->config.player.plane.y * cos(rot_speed);
// }
// TOURNER LA CAMERA VERS L AGAUCHE
// void    rotate(t_game *game, int rot)
// {
//     printf("%d %d\n", game->keys.left, rot);
// }

