#include "../../includes/cub3d_bonus.h"

// Appliquer l'effet d'ombre sur les mûrs
int apply_shadow(int color, double distance, int side)
{
    double  factor;
    int     r;
    int     g;
    int     b;

    // Plus la distance est grande, plus c'est sombre (min: 0.2, max: 1.0)
    factor = 1.0 / (1.0 + distance * 0.1);
    if (factor < 0.2)
        factor = 0.2;
    if (side == 1)
        factor *= 0.7;
    r = ((color >> 16) & 0xFF) * factor;
    g = ((color >> 8) & 0xFF) * factor;
    b = (color & 0xFF) * factor;
    return ((r << 16) | (g << 8) | b);
}

// DDA Functions
void	perform_dda(t_ray *ray, t_config *config)
{
    t_door  *door;

    ray->hit = 0;
    ray->side = 0;
    // DDA LOOP
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
        if (config->map.grid[ray->map_y][ray->map_x] == '4')
        {
            ray->hit = 1;
            door = find_door(config, ray->map_x, ray->map_y);
            if (ray->side == 0)
                door->side_hit = 0;
            else
                door->side_hit = 1;
            if (door && door->door_offset >= 1.0)
            {
                ray->hit = 0;
                continue ;
            }
            ray->text_type = DOOR_TYPE;
            ray->door_x = ray->map_x;
            ray->door_y = ray->map_y;
            ray->door_hit = door;
        }
    }
}

t_img *get_dir_texture(t_ray *ray, t_img *textures)
{
    int dir_tex;

    // tex_pos : position de départ dans la texture (dépend de draw_start).
    // Cela permet de mapper proportionnellement la texture à la hauteur du mur à l’écran.
    // 1. Choisir la texture
    if (ray->side == 0)
    {
        if (ray->ray_dir.x > 0)
            dir_tex = EAST;
        else
            dir_tex = WEST;

    } else {
        if (ray->ray_dir.y < 0)
            dir_tex = NORTH;
        else
            dir_tex = SOUTH;
    }
    return (&textures[dir_tex]);
}


t_img *get_door_dir_text(t_ray *ray, t_door *door, t_img *textures)
{
    int dir_tex;

    if (ray->side == 0)
    {
        if (ray->ray_dir.x > 0)
        {
            if (!door->is_open)
                dir_tex = 0;
            else
                dir_tex = 1;
        }
        else
        {
            if (!door->is_open)
                dir_tex = 0;
            else
                dir_tex = 1;
        }
    }
    else
    {
        if (ray->ray_dir.y < 0)
        {
            if (!door->is_open)
                dir_tex = 0;
            else
                dir_tex = 1;
        }
        else
        {
            if (!door->is_open)
                dir_tex = 0;
            else
                dir_tex = 1;
        }
    }
    return (&textures[dir_tex]);
}

int initialize_texture(t_ray *ray, t_img *texture, t_config *config)
{
    double wall_x;

    wall_x = 0.0;
    if (!ray || !texture)
        return (print_err("Raycasting error: "
        "texture initialization failed\n"));
    //  Calcul de wall_x et tex_x
    // wall-X ou hit_x représente la fraction du mur touché
    // donc le point d'impact du ray
    // Ici side = 0; le ray a frappé un mur vertical(vers la gauche ou la droite); la coordonnée importante ici est y
    // Et si side = 1; le ray a frappé un mur horizontal (vers le haut ou bas); la coordonnée ici c'est x 
    if (ray->text_type == WALL_TYPE)
    {
        if (ray->side == 0)
            // wall_x = ray->map_y + ray->perp_wall_dist * ray->ray_dir.y;
            wall_x = config->player.pos.y + ray->perp_wall_dist * ray->ray_dir.y;
        else
            wall_x = config->player.pos.x + ray->perp_wall_dist * ray->ray_dir.x;
            // wall_x = ray->map_x + ray->perp_wall_dist * ray->ray_dir.x;
    } 
    if (ray->text_type == DOOR_TYPE)
    {
        // if (ray->door_hit->is_open)
        //     return (0);
        if (ray->side == 0)
            wall_x = (config->player.pos.y + ray->perp_wall_dist * ray->ray_dir.y) - ray->door_hit->door_offset;
            // wall_x = (ray->map_y + ray->perp_wall_dist * ray->ray_dir.y) - ray->door_hit->door_offset;
        else
            wall_x = (config->player.pos.x + ray->perp_wall_dist * ray->ray_dir.x) - ray->door_hit->door_offset;
            // wall_x = (ray->map_x + ray->perp_wall_dist * ray->ray_dir.x) - ray->door_hit->door_offset;
        // wall_x = wall_x - ray->door_hit->door_offset / (1.0 - ray->door_hit->door_offset);
        // if (wall_x < 0.0)
        //     wall_x = 0.0;
        // else if (wall_x > 1.0)
        //     wall_x = 1.0;
    }
    wall_x -= floor(wall_x); // On ne garde que la partie décimale
    texture->tex_x = (int)(wall_x * texture->width);
    if ((ray->side == 0 && ray->ray_dir.x > 0)
        || (ray->side == 1 && ray->ray_dir.y < 0))
        texture->tex_x = texture->width - texture->tex_x - 1;
    // Calcul du step et de la position initiale
    texture->step = 1.0 * texture->height / ray->column.line_height;
    texture->tex_pos = (ray->column.draw_start - HEIGHT / 2
        + ray->column.line_height / 2) * texture->step;
    return (0);
}

int draw_column(t_ray *ray, t_game *game, int x)
{
    int y;
    // int color;
    t_img *texture;
    t_door *door;

    texture = NULL;
    door = find_door(&game->config, ray->door_x, ray->door_y);
    if (ray->text_type == WALL_TYPE)
        texture = get_dir_texture(ray, game->textures);
    else if (ray->text_type == DOOR_TYPE)
        texture = get_door_dir_text(ray, door, game->door_textures);
    // 3. Sécuriser draw_start / draw_end
    if (ray->column.draw_start < 0)
        ray->column.draw_start = 0;
    if (ray->column.draw_end >= HEIGHT)
        ray->column.draw_end = HEIGHT - 1;
    if (initialize_texture(ray, texture, &game->config))
        return (-1);
    // 5. Boucle de dessin
    y = ray->column.draw_start;
    while (y <= ray->column.draw_end)
    {
        /**
         * À chaque y, on :
         * Cherche le pixel correspondant dans l’image (via tex_x, tex_y),
         * Affiche ce pixel à l’écran.
        */
        texture->tex_y = (int)texture->tex_pos;
        if (texture->tex_y < 0)
            texture->tex_y = 0;
        if (texture->tex_y >= texture->height)
            texture->tex_y = texture->height - 1; // & pour rester dans l’image (si height est puissance de 2)
        texture->tex_pos += texture->step;
        ray->column.color = get_texture_pixels(texture, texture->tex_x, texture->tex_y); // lecture couleur
        ray->column.color = apply_shadow(ray->column.color, ray->perp_wall_dist, ray->side);
        if (put_pixel(&game->mlx.screen, x, y, ray->column.color))
            return (print_err("Ray casting error\n"));
        y++;
    }
    return (0);
}
