#include "../../includes/cub3d.h"

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
