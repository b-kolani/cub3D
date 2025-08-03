#include "../../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_config *config, int x)
{
    double  cameraX;

    cameraX = 2 * x / (double)WIDTH - 1;
    // ray.delta_dist.x = sqrt(1 + (ray.ray_dir.y * ray.ray_dir.y)) / (ray.ray_dir.x * ray.ray_dir.x);
    // ray.delta_dist.y = sqrt(1 + (ray.ray_dir.x * ray.ray_dir.x)) / (ray.ray_dir.y * ray.ray_dir.y);

    ray->ray_dir.x = config->player.dir.x + config->player.plane.x * cameraX; // Interpolation lineaire pour x
    ray->ray_dir.y = config->player.dir.y + config->player.plane.y * cameraX; // interpolation lineaire pour y
    // Eviter la division par 0. INFINITY est la bonne valeur car 
    // quand ray dir x est égale à zéro ou très proche de 0 cela veut dire
    // dir que le ray est || à y donc il ne progressera jamais en x. Donc ray 
    // delta_dist x doit être considéré comme infini ainsi dans DDA ray dist x < 
    // ray dist y.
    // Il en va de même lorsque ray dir y est null.
    if (fabs(ray->ray_dir.x) < 1e-6) 
        ray->delta_dist.x = INFINITY; 
    else
        ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
    if (fabs(ray->ray_dir.y) < 1e-6)
        ray->delta_dist.y = INFINITY;
    else
        ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
    // ray->delta_dist.x = sqrt(1 + (ray->ray_dir.y * ray->ray_dir.y)) / (ray->ray_dir.x * ray->ray_dir.x);
    // ray->delta_dist.y = sqrt(1 + (ray->ray_dir.x * ray->ray_dir.x)) / (ray->ray_dir.y * ray->ray_dir.y);
    // ray->delta_dist.x = sqrt(1 + (ray->ray_dir.y * ray->ray_dir.y) / (ray->ray_dir.x * ray->ray_dir.x));
    // ray->delta_dist.y = sqrt(1 + (ray->ray_dir.x * ray->ray_dir.x) / (ray->ray_dir.y * ray->ray_dir.y));
}


void	init_dda(t_ray *ray, t_config *config)
{
    if (ray->ray_dir.x < 0)
    {
        ray->step_x = -1;
        ray->side_dist.x = (config->player.pos.x - ray->map_x) * ray->delta_dist.x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist.x = ((ray->map_x + 1) - config->player.pos.x) * ray->delta_dist.x;
    }
    if (ray->ray_dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist.y = (config->player.pos.y - ray->map_y) * ray->delta_dist.y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist.y = ((ray->map_y + 1) - config->player.pos.y) * ray->delta_dist.y;
    }
};

void	compute_projection(t_ray *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
    else
        ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
    // Ce garde fou ou protection est tres importante pour eviter 
    // la disparition d'un mur lorsqu'on est tout proche 
    // si perp_wall_dist est trop petit alors la division tendra vers l'infini
    // une grande valeur donc draw start et draw end peuvent dépassés
    // On sort complètement de l'écran donc elle empêche un mur enorme/null/invisible
    if (ray->perp_wall_dist < 0.0001)
        ray->perp_wall_dist = 0.0001;
    ray->column.line_height = (int)(HEIGHT / ray->perp_wall_dist);
    ray->column.draw_start = (-(ray->column.line_height) / 2) + (HEIGHT / 2);
    ray->column.draw_end = (ray->column.line_height / 2) + (HEIGHT / 2);
}

// Cette fonction fait le lance ou trace des rayons
// Un rayon c'est une ligne virtuelle lancee 
// depuis la position du joueur pour detecter un
// mur. Une fois le mur atteint on le represente
// sous forme d'une ligne verticale. Les rayons sont
// lances colonne par colonne
int raycasting(t_game *game)
{
    t_ray   ray;
    int     x;

    // Tu parcours chaque colonne de l’écran (de gauche à droite).
    // Chaque x représente une "ligne verticale" à dessiner, 
    // en lançant un rayon dans le monde.
    x = -1;
    while (++x < WIDTH)
    {
        ray.map_x = (int)game->config.player.pos.x;
        ray.map_y = (int)game->config.player.pos.y;
        // ray.delta_dist.x = sqrt(1 + (ray.ray_dir.y * ray.ray_dir.y)) / (ray.ray_dir.x * ray.ray_dir.x);
        // ray.delta_dist.y = sqrt(1 + (ray.ray_dir.x * ray.ray_dir.x)) / (ray.ray_dir.y * ray.ray_dir.y);
        init_ray(&ray, &game->config, x);
        init_dda(&ray, &game->config);
        perform_dda(&ray, &game->config);
        compute_projection(&ray);
        if (draw_column(&ray, game, x))
            return (-1);
    }
    return (0);
}

// int render_frame(t_game *game)
// {
//     if (draw_background(game))
//         return (-1);
//     if (raycasting(game))
//         return (-1);
//     return (0);
// }
