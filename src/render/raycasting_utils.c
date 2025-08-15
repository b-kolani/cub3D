#include "../../includes/cub3d.h"

// Appliquer l'effet d'ombre sur les mûrs
int apply_shadow(int color, double distance, int side)
{
    double  factor;
    int     r;
    int     g;
    int     b;

    // Plus la distance est garnde, plus c'est sombre (min: 0.2, max: 1.0)
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
            ray->hit = 1;
    }
}

t_img *get_dir_texture(t_ray *ray, t_img *textures)
{
    int tex_dir;

    // tex_pos : position de départ dans la texture (dépend de draw_start).
    // Cela permet de mapper proportionnellement la texture à la hauteur du mur à l’écran.
    // 1. Choisir la texture
    if (ray->side == 0)
    {
        if (ray->ray_dir.x > 0)
            tex_dir = EAST;
        else
            tex_dir = WEST;

    } else {
        if (ray->ray_dir.y < 0)
            tex_dir = NORTH;
        else
            tex_dir = SOUTH;
    }
    return (&textures[tex_dir]);
}

int initialize_texture(t_ray *ray, t_img *texture, t_config *config)
{
    double wall_x;

    if (!ray || !texture)
        return (print_err("Raycasting error: "
        "texture initialization failed\n"));
    //  Calcul de wall_x et tex_x
    if (ray->side == 0)
        wall_x = config->player.pos.y + ray->perp_wall_dist * ray->ray_dir.y;
        // wall_x = ray->map_y + ray->perp_wall_dist * ray->ray_dir.y;
    else
        wall_x = config->player.pos.x + ray->perp_wall_dist * ray->ray_dir.x;
        // wall_x = ray->map_x + ray->perp_wall_dist * ray->ray_dir.x;
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

    texture = get_dir_texture(ray, game->textures);
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
