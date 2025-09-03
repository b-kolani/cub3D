/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:48:40 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/02 21:48:56 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Ajouter 0.5 a x pour placer le joueur au milieu de la colonne
// ou case cela est important pour son champ de vision 
// de pouvoir regarder a gauche; au centre et a droite 
// donc oscillation de la camera
// Pareil pour y; car c'est x et y qui determinent la position 
// exacte du joueur sur la carte
/**
 * Dans Cub3D :
 * La carte (map) est une grille de cases (comme un tableau).
 * Chaque case (mur ou sol) a une taille de 1.0 unité (en coordonnées monde).
 * Si le joueur est à (2, 2), il est au coin supérieur gauche de la cellule [2][2].
 * Or, pour que le joueur voit bien dans toutes les directions et 
 * qu’il soit "dans la case", on veut le mettre au centre de la case.
 * Il sera au coin haut-gauche de la case [2][2], 
 * ce qui peut causer des bugs (collisions, rayons mal orientés, murs pas touchés, etc.).
 * Il sera au milieu de la case avec [2.5][2.5], ce qui permet :
 * De lancer des rayons dans toutes les directions sans "être dans un mur"
 * D’avoir un rendu plus propre et naturel.
 */
void    set_player_x_pos(t_config *config, char *pos_line)
{
    int j;

    j = -1;
    while (pos_line[++j])
    {
        if (pos_line[j] == 'N' || pos_line[j] == 'S'
            || pos_line[j] == 'E' || pos_line[j] == 'W')
        {
            config->player.pos.x = j + 0.5;
            break ;
        }
    }
}

// Detecter la direction du regard du joueur
/**
 * Le vecteur plane est perpendiculaire au vecteur direction dir du joueur.
 * Il représente les bords gauche et droit de la "caméra" virtuelle.
 * Le FOV classique utilisé dans Cub3D est d’environ 66°, ce 
 * qui correspond à un plane de longueur 0.66.
 */
// Creer un vecteur de direction de coordonnees (x, y)
// Car en 2D, une direction est un vecteur qui a deux 
// composantes : une pour l’axe x (horizontal), 
// une pour l’axe y (vertical).
// Un vecteur direction représente donc un sens.
// Donc (dir_x, dir_y) exprime où tu vas "en ligne droite" si tu avances.
static void set_plane(t_player *player, double x, double y)
{
    player->plane.x = x;
    player->plane.y = y;
}

/**
 * Le vecteur plane doit être perpendiculaire au vecteur dir, 
 * dans le sens anti-horaire (convention d’orientation du plan 
 * de caméra dans les moteurs 3D simples).
 * 🔁 Rappel :
 * Si tu as un vecteur dir = (dx, dy), alors les vecteurs :
 * ( -dy, dx )
 * ( dy, -dx )
 * sont perpendiculaires à dir.
 * C’est une propriété géométrique en 2D :
 * Tourner un vecteur de 90° donne un vecteur perpendiculaire.
 */
static void set_direction(t_player *player, char dir)
{
    if (dir == 'N')
    {
        player->dir.x = 0;
        player->dir.y = -1;
        set_plane(player, 0.66, 0);
    }
    if (dir == 'S')
    {
        player->dir.x = 0;
        player->dir.y = 1;
        set_plane(player, -0.66, 0);
    }
    if (dir == 'E')
    {
        player->dir.x = 1;
        player->dir.y = 0;
        set_plane(player, 0, 0.66);
    }
    if (dir == 'W')
    {
        player->dir.x = -1;
        player->dir.y = 0;
        set_plane(player, 0, -0.66);
    }
}

void    set_player_orientation(t_player *player, char *pos_line)
{
    char    dir;
    int     i;

    i = -1;
    while (pos_line[++i])
    {
        if (pos_line[i] == 'N' || pos_line[i] == 'S'
        || pos_line[i] == 'E' || pos_line[i] == 'W')
            dir = pos_line[i];
    }
    set_direction(player, dir);
    // printf("x pos: %f\n", player->pos.x);
    // printf("y pos: %f\n", player->pos.y);
}

// Valider les elements
int my_access(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (-1);
    close(fd);
    return (0);
}

int validate_config(t_config *config, t_gc *gc)
{
    if (!config->no || !config->so || !config->ea || !config->we)
        return (print_err("Map error: element path missing\n"));
    if (my_access(ft_substr(config->no, 0, ft_strlen(config->no), gc)) || my_access(ft_substr(config->so, 0, ft_strlen(config->so), gc))
        || my_access(ft_substr(config->ea, 0, ft_strlen(config->ea), gc))
        || my_access(ft_substr(config->we, 0, ft_strlen(config->we), gc)))
        return (print_err("Map error: Invalid path; file not found!\n"));
    return (0);
}
