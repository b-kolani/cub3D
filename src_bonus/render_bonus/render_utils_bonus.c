#include "../../includes/cub3d_bonus.h"

int    put_pixel(t_img *img, int x, int y, int color)
{
    char    *dst; // addresse du pixel a dessiner

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return (print_err("mlx error: Failed to put pixel\n"));
    // Recuperer cette adresse
    // img->img_data_addr -> debut de l'image tampon
    // y * img->line_length -> decalage vertical jusqu'a la ligne y
    // x * (img->bits_per_pixel / 8) -> decalage horizontal jusqu'a la colonne x
    // *(unsigned int *)dst -> ON ecrrit un int 4 octets (32 bits)
    // color -> La couleur a ecire;
    dst = img->img_data_addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
    return (0);
}

// Cette fonction est utilisée pour récupérer
// les pixels des textures
int get_texture_pixels(t_img* tex, int x, int y)
{
    char    *pixel_addr;
    int     color;

    pixel_addr = tex->img_data_addr + (y * tex->line_length + x 
    *(tex->bits_per_pixel / 8));
    color = *(unsigned int *)pixel_addr;
    return (color);
}

// draw_background() est essentielle dans le rendu de base d’un moteur comme Cub3D.
// Elle sert à remplir tout l’écran avec :
// Une couleur pour le plafond dans la moitié supérieure,
// Une couleur pour le sol dans la moitié inférieure.
// Dans un moteur 3D comme Cub3D (type Wolfenstein 3D) :
// Tu dessines d’abord un fond : ciel (haut) et sol (bas),
// Puis tu dessines les murs par-dessus avec le raycasting.
// Sans cette fonction, le fond de ton image serait noir ou 
// plein de pixels précédents (non nettoyés), ce qui donne un rendu sale ou incohérent.
// Pour chaque pixel (x, y) :
// Si y est dans la moitié supérieure → plafond
// Sinon → sol
// L'appeler avant de placer les murs avec le raycasting
/**
 * La rencontre entre le plafond et le sol, 
 * c’est-à-dire la séparation visuelle entre les deux, 
 * crée un fond de base pour ta scène 3D.
 * 🎯 Ce fond joue deux rôles :
 * Donner un effet de perspective 
 * même sans mur (sol en bas, ciel en haut).
 * Préparer l’image proprement avant de dessiner 
 * les murs (et plus tard les sprites, textures, etc.).
 * Même sans aucun mur, ton œil perçoit une profondeur, 
 * une ligne d’horizon, donc une illusion de 3D !
 * L’effet de perspective, c’est ce qui donne l’illusion de profondeur dans une image 2D.
 * 🎯 C’est ce qui te fait percevoir qu’un objet est loin ou près, 
 * alors que tout est dessiné sur un écran plat.
 */
int draw_background(t_game *game)
{
    int x;
    int y;

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            if (y < (HEIGHT / 2))
            {
                if (put_pixel(&game->mlx.screen, x, y, game->config.ceil_color))
                    return (-1);
            }
            else
            {
                if (put_pixel(&game->mlx.screen, x, y, game->config.floor_color))
                    return (-1);
            }
        }
    }
    return (0);
}

int is_item_active(t_config *config, int x, int y)
{
    int i;

    i = -1;
    while (++i < config->sprites_count)
    {
        if ((int)config->sprites[i].x == x && (int)config->sprites[i].y == y)
        {
            if (config->sprites[i].active)
                return (1);
            else
                return (0);
        } 
    }
    return (0);
}

t_sprite *find_item(t_config *config, int map_x, int map_y)
{
    int i;

    i = -1;
    while (++i < config->sprites_count)
    {
        if ((int)config->sprites[i].x == map_x
            && (int)config->sprites[i].y == map_y)
            return (&config->sprites[i]);
    }
    return (NULL);
}

t_door *find_door(t_config *config, int map_x, int map_y)
{
    int i;

    i = -1;
    while (++i < config->doors_count)
    {
        if ((int)config->doors[i].x == map_x 
            && (int)config->doors[i].y == map_y)
            return (&config->doors[i]);
    }
    return (NULL);
}
// Fonction pour déssiner une cellule ou case ou tile 
// de la carte 
int draw_map_wall_cell(t_img *screen , int map_x, int map_y, int color)
{
    int x;
    int y;

    y = -1;
    while (++y < CELL_SIZE)
    {
        x = -1;
        while (++x < CELL_SIZE)
        {
            if (put_pixel(screen, START_PIXEL_X + map_x * CELL_SIZE + x, 
                START_PIXEL_Y + map_y * CELL_SIZE + y, color))
                return (-1);
        }
    }
    return (0);
}

int draw_map_item_cell(t_game *game, int map_x, int map_y, int color)
{
    t_sprite *sprite;
    int pixel_x;
    int pixel_y;
    int x;
    int y;

    sprite = find_item(&game->config, map_x, map_y);
    if (sprite == NULL)
        return (-1);
    pixel_x = sprite->x * CELL_SIZE;
    pixel_y = sprite->y * CELL_SIZE;
    y = -ITEM_CELL_SIZE / 2;
    while (y < ITEM_CELL_SIZE / 2)
    {
        x = -ITEM_CELL_SIZE / 2;
        while (x < ITEM_CELL_SIZE / 2)
        {
            if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
                START_PIXEL_Y + pixel_y + y, color))
                return (-1);
            x++;
        }
        y++;
    }
    return (0);
}

// int door_pos_on_mini_map(t_door *door, t_map *map)
// {
//     // Porte vertiacle si un mur est à sa gauche ou à sa doite
//     if ()
//         return (0);
//     // 0 si la porte doit être dessiné horizontalement 
//     // sur la mini map
//     return (1);
// }

int draw_opened_door(t_game *game, t_door *door, int color)
{
    int x;
    int y;
    int     pixel_x;
    int     pixel_y;

    pixel_x = door->x * CELL_SIZE;
    pixel_y = door->y * CELL_SIZE;
    if (door->side_hit == 1)
    {
        y = -1;
        while (y < DOOR_CELL_SIZE / 2)
        {
            x = -DOOR_CELL_SIZE;
            while (x < DOOR_CELL_SIZE)
            {
                if (x < -(DOOR_CELL_SIZE / 2) || x >= (DOOR_CELL_SIZE / 2))
                {
                    if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
                        START_PIXEL_Y + pixel_y + y, color))
                        return (-1);
                }
                x++;
            }
            y++;
        }
    }
    else if (door->side_hit == 0)
    {
        y = -DOOR_CELL_SIZE;
        while (y < DOOR_CELL_SIZE)
        {
            if (y >= -2 && y <= 1) {
                y++;
                continue ;
            }
            x = -1;
            while (x < DOOR_CELL_SIZE)
            {
                if (x < -(DOOR_CELL_SIZE / 2) || x >= (DOOR_CELL_SIZE / 2))
                {
                    if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
                        START_PIXEL_Y + pixel_y + y, color))
                        return (-1);
                }
                x++;
            }
            y++;
        }
    }
    return (0);
}

// int dot_product(t_vector v_1, t_vector v_2)
// {
//     int scalar_product;

//     scalar_product = (v_1.x * v_2.x) + (v_1.y * v_2.y);
//     return (scalar_product);
// }

int draw_closed_door(t_game *game, t_door *door, int color)
{
    int x;
    int y;
    int     pixel_x;
    int     pixel_y;

    pixel_x = door->x * CELL_SIZE;
    pixel_y = door->y * CELL_SIZE;
    // printf("Door dir: x:%d, y:%d\n", (int)door->dir.x, (int)door->dir.y);
    // Pour un mur horizontal
    if (door->side_hit == 1)
    {
        y = -1;
        while (y < DOOR_CELL_SIZE / 2)
        {
            x = -DOOR_CELL_SIZE;
            while (x < DOOR_CELL_SIZE)
            {
                if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
                    START_PIXEL_Y + pixel_y + y, color))
                    return (-1);
                x++;
            }
            y++;
        }
    }
    // Pour un mur vertical
    else if (door->side_hit == 0)
    {
        // printf("Ici\n");
        y = -DOOR_CELL_SIZE;
        while (y < DOOR_CELL_SIZE)
        {
            x = -1;
            while (x < DOOR_CELL_SIZE / 2)
            {
                if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
                    START_PIXEL_Y + pixel_y + y, color))
                    return (-1);
                x++;
            }
            y++;
        }
    }
    return (0);
}

// int draw_vertical_wall()
// {}

// int draw_horizontal_wall(t_img *screen, int fov->px, int py, int color)
// {
//     int x;
//     int y;

//     y = -1;
//     while (y < DOOR_CELL_SIZE / 2)
//     {
//         x = -DOOR_CELL_SIZE;
//         while (x < DOOR_CELL_SIZE)
//         {
//             if (put_pixel(screen, START_PIXEL_X + px + x,
//                 START_PIXEL_Y + py + y, color))
//                 return (-1);
//             x++;
//         }
//         y++;
//     }
// }

int draw_map_door_cell(t_game *game, int map_x, int map_y, int color)
{
    t_door  *door;
    // int     pixel_x;
    // int     pixel_y;
    // int     x;
    // int     y;

    door = find_door(&game->config, map_x, map_y);
    // pixel_x = door->x * CELL_SIZE;
    // pixel_y = door->y * CELL_SIZE;
    if (!door->is_open)
    {
        if (draw_closed_door(game, door, color))
            return (-1);
        // y = -1;
        // while (y < DOOR_CELL_SIZE / 2) ,
        // {
        //     x = -DOOR_CELL_SIZE;
        //     while (x < DOOR_CELL_SIZE)
        //     {
        //         if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
        //             START_PIXEL_Y + pixel_y + y, color))
        //             return (-1);
        //         x++;
        //     }
        //     y++;
        // }
    }
    else
    {
        if (draw_opened_door(game, door, color))
            return (-1);
        // y = -1;
        // while (y < DOOR_CELL_SIZE / 2)
        // {
        //     x = -DOOR_CELL_SIZE;
        //     while (x < DOOR_CELL_SIZE)
        //     {
        //         if (x < -(DOOR_CELL_SIZE / 2) || x >= (DOOR_CELL_SIZE / 2))
        //         {
        //             if (put_pixel(&game->mlx.screen, START_PIXEL_X + pixel_x + x,
        //             START_PIXEL_Y + pixel_y + y, color))
        //                 return (-1);
        //         }
        //         x++;
        //     }
        //     y++;
        // }
    }
    return (0);
}

// Fonction pour déssiner le player sur la mini-map
int draw_player_on_the_map(t_game *game, int color)
{
    int px;
    int py;
    int y;
    int x;

    px = game->config.player.pos.x * CELL_SIZE;
    py = game->config.player.pos.y * CELL_SIZE;
    y = -PLAYER_CELL_SIZE / 2;
    while (y < PLAYER_CELL_SIZE / 2)
    {
        x = -PLAYER_CELL_SIZE / 2;
        while (x < PLAYER_CELL_SIZE / 2)
        {
            if (put_pixel(&game->mlx.screen, START_PIXEL_X + px + x, 
                START_PIXEL_Y + py + y, color))
                return (-1);
            x++;
        }
        y++;
    }
    return (0);
}

int draw_mini_map_fov(t_game *game)
{
    // double range;
    t_fov *fov;
    // int x;
    // int y;
    // double dx;
    // double dy;
    // int     px;
    // int     py;
    // double  player_angle;
    double  r;
    // double  start_angle;
    // double  end_angle;
    double  angle;
    // double step;
    t_door  *door;
    // int     map_x;
    // int     intersection;
    // int     map_y;

    fov = &game->mini_map_fov;
    fov->range = 50.0; // Le cône s'étend de 50 pixels depuis la position du joueur
    fov->px = game->config.player.pos.x * CELL_SIZE;
    fov->py = game->config.player.pos.y * CELL_SIZE;
    // atan2 donne l'angle en radians que forme un vecteur avec l'axe des abssices (en 2D)
    // Si par exemple l'angle est 0; alors la dir du joueur est vers la droite (x positif)
    // Si angle est pi / 2; vecteur vers le bas (y positif)
    // Si angle est égal à pi; vecteur vers la gauche (x négatif)
    // Si angle est égal à -pi / 2; vecteur vers le haut (y négatif)
    fov->player_angle = atan2(game->config.player.dir.y, game->config.player.dir.x);
    // start_angle désigne le début du cône ou de l'éventail
    // représentant le fov sur le mini map
    fov->start_angle = fov->player_angle - (FOV / 2.0); // Divise le FOV / 2 car la direction du joueur
    // divise le plane en deux;
    // end_angle la fin du cône
    fov->end_angle = fov->player_angle + (FOV / 2.0);
    r = 0;
    angle = fov->start_angle;
    // step = 0.01;
    fov->step = 0.01; // step nous permet d'avancer
    // de start_angle à end_angle; plus c'est petit plusc'est lisse par exemple 0.01
    while (angle <= fov->end_angle)
    {
        r = 0;
        while (r <= fov->range)
        {
            fov->intersection = 0;
            // dx et dy direction du rayon
            fov->dx = cos(angle); // dx c'est de combien on avance horizonatlement pour un pas
            fov->dy = sin(angle); // dy c'est de combien on avance verticalement pour un pas
            fov->x = (int)(fov->px + fov->dx * r);
            fov->y = (int)(fov->py + fov->dy * r);
            fov->map_x = fov->x / CELL_SIZE;
            fov->map_y = fov->y / CELL_SIZE;
            if (fov->map_x < 0 || fov->map_x > game->config.map.width - 1 
                || fov->map_y < 0 || fov->map_y > game->config.map.height - 1)
                break ;
            if (!ft_strchr("0134", game->config.map.grid[fov->map_y][fov->map_x]) || (
                game->config.map.grid[fov->map_y][fov->map_x] == '0' && game->config.map.grid[fov->map_y][fov->map_x + 1] == '1'
                && game->config.map.grid[fov->map_y][fov->map_x - 1] == '1' && game->config.map.grid[fov->map_y - 1][fov->map_x] == '1'
                && game->config.map.grid[fov->map_y + 1][fov->map_x] == '1'
            ))
                fov->intersection = 1;
            if (game->config.map.grid[fov->map_y][fov->map_x] == '1' || fov->intersection)
                break ;
            if (game->config.map.grid[fov->map_y][fov->map_x] == '4')
            {
                door = find_door(&game->config, fov->map_x, fov->map_y);
                if (door && !door->is_open)
                    break;
            }
            if (put_pixel(&game->mlx.screen, fov->x, fov->y, 0xf5b342))
                return (-1);
            r += 1.0;
        }
        angle += fov->step;
    }
    return (0);
}

int draw_mini_map(t_game *game)
{
    int map_x;
    int map_y;

    map_y = -1;
    // printf("Height: %d, Width: %d\n", game->config.map.height, game->config.map.width);
    // int i = -1;
    // while (++i < game->config.map.height)
    //     printf("%s%%\n", game->config.map.grid[i]);
    // printf("\n");
    if (game->config.map.height > 72 || game->config.map.width > 128)
        return (print_err("Failed to draw mini map; out of window sizes bounds\n"));
    while (++map_y < game->config.map.height)
    {
        map_x = -1;
        while (++map_x < (int)ft_strlen(game->config.map.grid[map_y]))
        {
            if (game->config.map.grid[map_y][map_x] == '1')
            {
                if (draw_map_wall_cell(&game->mlx.screen, map_x, map_y, 0xFF9000))
                    return (-1);
            }
            else if (game->config.map.grid[map_y][map_x] == '3')
            {
                if (is_item_active(&game->config, map_x, map_y))
                {
                    if (draw_map_item_cell(game, map_x, map_y, 0x00FF00))
                        return (-1);
                }
            }
            else if (game->config.map.grid[map_y][map_x] == '4')
            {
                if (draw_map_door_cell(game, map_x, map_y, 0XFF0000))
                    return (-1);
            }
        }
    }
    if (draw_player_on_the_map(game, 0x0000FF))
        return (-1);
    if (draw_mini_map_fov(game))
        return (-1);
    return (0);
}
