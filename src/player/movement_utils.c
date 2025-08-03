#include "../../includes/cub3d.h"

// ON peut creer une fonction generique 
// donc unique qui sera utilisee pour chaque
// touche avec le bon vecteur pour W et S le vecteur dir;
// et Pour A et D le vecteur plan
// en utilisant le principe de deplacement par vecteur
// // POUR AVANCER

void    move_forward(t_game *game)
{
    double  next_x;
    double  next_y;

    // printf("Coord de Pos: %d %d\n", (int)game->config.player.pos.x, (int)game->config.player.pos.y);
    next_x = game->config.player.pos.x + game->config.player.dir.x * game->move_speed;
    next_y = game->config.player.pos.y + game->config.player.dir.y * game->move_speed;
    // char tile_x = game->config.map.grid[(int)game->config.player.pos.y][(int)next_x];
    // char tile_y = game->config.map.grid[(int)next_y][(int)game->config.player.pos.x];

    // printf("➡️ Collision X: tile = '%c' (ascii %d)\n", tile_x, tile_x);
    // printf("➡️ Collision Y: tile = '%c' (ascii %d)\n", tile_y, tile_y);

    // printf("%c\n", game->config.map.grid[(int)next_y][(int)game->config.player.pos.y]);
    if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
        game->config.player.pos.x = next_x;
    if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
        game->config.player.pos.y = next_y;
    // printf("Previous position: %c\n", game->config.map.grid[(int)game->config.player.pos.y][(int)game->config.player.pos.x]); printf("Next position: %c\n", game->config.map.grid[(int)next_y][(int)next_x]);
    // if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
    // {
    //     game->config.player.pos.x = next_x;
    //     game->config.player.pos.y = next_y;
    // }
}
// 
// // POUR RECULER
void    move_backward(t_game *game)
{
    double next_x;
    double next_y;

    // printf("Coord de Pos: %d %d\n", (int)game->config.player.pos.x, (int)game->config.player.pos.y);
    next_x = game->config.player.pos.x - game->config.player.dir.x * game->move_speed;
    next_y = game->config.player.pos.y - game->config.player.dir.y * game->move_speed;
    if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
        game->config.player.pos.x = next_x;
    if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
        game->config.player.pos.y = next_y;
    // if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
    // {
    //     game->config.player.pos.x = next_x;
    //     game->config.player.pos.y = next_y;
    // }
}

// Strafe ou mitraillage en francais designe le mouvement lateral
// d'un personnage, sans modifier sa direction de deplacement.
// (avancer ou reculer). C'est une technique utilisee dans les 
// jeux de tir a la premiere personne (FPS) et peut etre utilise
// pour esquiver les tirs des ennemis, faciliter le deplacement, 
// et dans certains cas augmenter la vitesse du joueur.
// // POUR ALLER A GAUCHE (DEPLACEMENT LATERAL VERS LA GAUCHE <-)
void    strafe_left(t_game *game)
{
    double next_x;
    double next_y;

    next_x = game->config.player.pos.x - game->config.player.plane.x * game->move_speed;
    next_y = game->config.player.pos.y - game->config.player.plane.y * game->move_speed;
    if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
        game->config.player.pos.x = next_x;
    if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
        game->config.player.pos.y = next_y;
    // if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
    // {
    //     game->config.player.pos.x = next_x;
    //     game->config.player.pos.y = next_y;
    // }
}

// // POUR ALLER A DROITE (DEPLACEMENT LATERAL VERS LA DROITE ->)
void    strafe_right(t_game *game)
{
    double  next_x;
    double  next_y;

    next_x = game->config.player.pos.x + game->config.player.plane.x * game->move_speed;
    next_y = game->config.player.pos.y + game->config.player.plane.y * game->move_speed;
    if (game->config.map.grid[(int)game->config.player.pos.y][(int)next_x] != '1')
        game->config.player.pos.x = next_x;
    if (game->config.map.grid[(int)next_y][(int)game->config.player.pos.x] != '1')
        game->config.player.pos.y = next_y;
    // if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
    // {
    //     game->config.player.pos.x = next_x;
    //     game->config.player.pos.y = next_y;
    // }
}

// Cette fonction sera appele pour tous les mouvement de 
// maniere generique juste passer le bon vecteur de mouvent
// elle utilise le principe de deplacement par vectuer
// void    move_player(t_game *game, t_vector mov_vec, int mov_dir)
// {
//     double  next_x;
//     double  next_y;

//     next_x = game->config.player.pos.x + mov_vec.x * game->move_speed;
//     next_y = game->config.player.pos.y + mov_vec.y * game->move_speed;

//     // Eviter de glisser sur les cotes si un cote est vide
//     // bloquer le glissement
//     if (game->config.map.grid[(int)next_y][(int)next_x] != '1')
//     {
//         game->config.player.pos.x = next_x;
//         game->config.player.pos.y = next_y;
//     }
// }
