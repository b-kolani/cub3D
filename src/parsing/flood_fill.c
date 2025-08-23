#include "../../includes/cub3d.h"

// Flood_fill valider les acces du joueur depuis sa position
// aux positions ajaccentes pour detecter des fuites(comme carte non fermee)
// ou detection des vides a cote des caracteres '0' ou 'N' ou 'E' ou 'W' ou 'S'
int flood_fill(t_config *config, char **tmp_map, int x, int y)
{
    int width;
    int height;

    width = config->map.width;
    height = config->map.height;
    if (x < 0 || y < 0 || x >= width || y >= height || tmp_map[y][x] == ' ')
        return (0);
    if (tmp_map[y][x] == '1' || tmp_map[y][x] == 'F')
        return (1);
    tmp_map[y][x] = 'F'; 
    return (flood_fill(config, tmp_map, x - 1, y) && 
            flood_fill(config, tmp_map, x, y + 1) &&
            flood_fill(config, tmp_map, x + 1, y) &&
            flood_fill(config, tmp_map, x, y - 1));
}

int flood_fill_space(t_config *config, char **tmp_map, int x, int y)
{
    int width;
    int height;

    width = config->map.width;
    height = config->map.height;
    if (x < 0 || y < 0 || x >= width || y >= height)
        return (1); // On sort de la map pas une fuite
    if (tmp_map[y][x] == '1' || tmp_map[y][x] == 'F' 
        || tmp_map[y][x] == 'F')
        return (1);
    if (tmp_map[y][x] == '0' || tmp_map[y][x] == 'N'
        || tmp_map[y][x] == 'S' || tmp_map[y][x] == 'E'
        || tmp_map[y][x] == 'W')
        return (0); // Fuite detectee un espace est connecte a un '0' ou position du joueur
    tmp_map[y][x] = 'F';
    return (flood_fill_space(config, tmp_map, x + 1, y) &&
            flood_fill_space(config, tmp_map, x, y + 1) &&
            flood_fill_space(config, tmp_map, x - 1, y) &&
            flood_fill_space(config, tmp_map, x, y - 1));
}