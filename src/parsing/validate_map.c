#include "../../includes/cub3d.h"

static int detect_map_leaks(t_gc *gc ,t_config *config, char **tmp)
{
    int x ;
    int y ;

    y = -1;
    while (++y < config->map.height)
    {
        x = -1;
        while (++x < config->map.width)
        {
            if (tmp[y][x] == ' ')
            {
                // if (!flood_fill_space(config, tmp, x, y))
                    if(!flood_fill_space_bfs(gc ,config, tmp,  x,  y))
                    return (-1);
            }
        }
    }
    return (0);
}

// Verifier si la carte est entouree de murs
static int check_walls(t_map map)
{
    int i;
    int j;

    i = -1;
    while (++i < map.height)
    {
        if (i == 0 || i == map.height - 1)
        {
            j = -1;
            while (map.grid[i][++j])
            {  
                if (map.grid[i][j] != '1' && !ft_isspace(map.grid[i][j]))
                    return (print_err("Map error: The map must be surrounded by walls!\n"));
            }
        }
        else if ((map.grid[i][0] != '1' && !ft_isspace(map.grid[i][0])) 
            || (map.grid[i][ft_strlen(map.grid[i]) - 1] != '1' 
            && !ft_isspace(map.grid[i][ft_strlen(map.grid[i]) - 1])))
            return (print_err("Map error: Invalid line between first and last lines!\n"));
    }
    return (0);
}

int find_player_position(t_config *config, char **tmp_map)
{
    int     i;
    int     player;
    char    *player_pos_line;

    i = -1;
    //int j = -1;
    player = 0;
    player_pos_line = NULL;
    while (tmp_map[++i])
    {

        if (ft_strchr(tmp_map[i], 'N') || ft_strchr(tmp_map[i], 'S')
        || ft_strchr(tmp_map[i], 'E') || ft_strchr(tmp_map[i], 'W'))
        {
            if (player == 1)
                return (print_err("Map error: need only one player on the map!\n"));
            player++;
            config->player.pos.y = i + 0.5;
        }
    }
    player_pos_line = tmp_map[(int)config->player.pos.y]; 
    set_player_x_pos(config, player_pos_line);
    set_player_orientation(&config->player, player_pos_line);
    return (0);
}

// Normailser les lignes c-a-d ajouter des espaces pour 
// qu etoutes les lignes aient la meme taille
// Cela evite des erreurs de raycasting; des segfaults
// les bugs de rendu
// les comportements imprévus du joueur (traversé des murs)
static int  normalized(char **config_map, char **tmp, t_gc *gc, size_t max_len)
{
    int i;
    int j;

    i = -1;
    while (config_map[++i])
    {
        tmp[i] = gc_malloc(gc, max_len + 1);
        j = -1;
        while (config_map[i][++j])
            tmp[i][j] = config_map[i][j];
        while ((size_t)j < max_len)
            tmp[i][j++] = ' ';
        tmp[i][j] = '\0';
    }
    tmp[i] = NULL;
   return (0);
}


// Valider la carte
// check if the map surounded by walls 
int validate_map(t_config *config, t_gc *gc, size_t map_len)
{
    int i;
    size_t  max_len;
    char    **tmp;

    max_len = 0;
    i = -1;
    if (check_walls(config->map))
        return (-1);
    while (config->map.grid[++i])
    {
        if (ft_strlen(config->map.grid[i]) > max_len)
            max_len = ft_strlen(config->map.grid[i]);
    }
    config->map.width = max_len;
    tmp = gc_malloc(gc, sizeof(char *) * (map_len + 1));
    if (normalized(config->map.grid, tmp, gc, max_len))
        return (-1);
    if (find_player_position(config, tmp))
        return (-1);
        
    if (detect_map_leaks(gc ,config, tmp))
        return (print_err("Map error: leak detected on the map!\n"));
    return (0);
}
