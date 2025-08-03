#include "../../includes/cub3d.h"

static int set_config(t_config *config, t_gc *gc, size_t map_len)
{
    config->map.grid = gc_malloc(gc, sizeof(char *) * (map_len + 1));
    config->map.height = map_len;
    if (!config->map.grid)
        return (print_err("gc_malloc error: grid allocation failed!\n"));
    return (0);
}

// Get and set textures paths
static int get_element_path(const char *line, t_config *config, t_gc *gc)
{
    if (!ft_strncmp(line, "NO ", 3) && config->no == NULL)
        config->no = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
        // config->no = ft_strdup(line + 3, gc); Avec ça on
        // a le new line à la fin et cela rend le path invalid
    else if (!ft_strncmp(line, "SO ", 3) && config->so == NULL)
        config->so = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
    else if (!ft_strncmp(line, "EA ", 3) && config->ea == NULL)
        config->ea = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
    else if (!ft_strncmp(line, "WE ", 3) && config->we == NULL)
        config->we = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
    else
        return (print_err("Map error: Element configuration line duplicated!\n"));
    return (0);
}

// Parse and set color for floor and ceil
static int parse_color(const char *line, t_config *config, char conf_type, t_gc *gc)
{
    char    **rgb;
    int     rgb_int[3];
    size_t  len;
    int     i;

    rgb = ft_split(line, ',');
    i = -1;
    len = 0;
    while (rgb[++i])
        len++;
    if (parse_color_helper(rgb, rgb_int, gc, len))
        return (-1);
    if (!(rgb_int[0] >= 0 && rgb_int[0] <= 255) 
        || !(rgb_int[1] >= 0 && rgb_int[1] <= 255)
        || !(rgb_int[2] >= 0 && rgb_int[2] <= 255))
        return (print_err("Map error: Each color need to be between 0 and 255\n"));
    // Construire chaque couleur donc pour le floor et le ceil 
    // Etant donne qu'une couleur prend juste 24 bits sur 32
    // On utilise le shift operator pour placer la premiere couleur le rouge 
    // dans le troisieme octet des 32 bits ensuite; green dans le deuxieme octet 
    // et enfin blue dans le dernier octet; le 4e et dernier octet le plus significatif
    // n'est donc pas utiliser dans certains cas utilise pour la transaprence
    // alpha. Une couleur est codee en general sur 24 bits.
    if (conf_type == 'F')
        config->floor_color = (rgb_int[0] << 16) | (rgb_int[1] << 8) | rgb_int[2];
    else
        config->ceil_color = (rgb_int[0] << 16) | (rgb_int[1] << 8) | rgb_int[2];
    free_split_alloc(rgb);
    return (0);
}

// Handle config line if found one
static int handle_config_line(t_config *config, t_gc *gc, char *line)
{
    if (is_path_line(line))
    {
        if (get_element_path(line, config, gc))
            return (-1);
    }
    else if (is_color_line(line))
    {
        if ((!ft_strncmp(line, "F ", 2) && config->floor_found)
            || (!ft_strncmp(line, "C ", 2) && config->ceil_found))
            return (print_err("Map error: Color configuration line duplicated\n"));
        if (!ft_strncmp(line, "F ", 2))
            config->floor_found = 1;
        else if (!ft_strncmp(line, "C ", 2))
            config->ceil_found = 1;
        if (parse_color(line + 2, config, line[0], gc))
            return (-1);
    }
    return (0);
}

// Parsing des elements de la carte
// REDUIRE CETTE FONCTION
int handle_config_line_err(t_config *config, t_gc *gc, char *line, int map_started)
{
    if (map_started)
        return (print_err("Map error: Configuration lines before "
            "the map description!\n"));
    if (handle_config_line(config, gc, line))
        return (-1);
    return (0);
}

int iterate_on_lines(t_config *config, t_gc *gc, char **lines, size_t *map_len)
{
    int i;
    int map_started;

    i = -1;
    map_started = 0;
    while(lines[++i])
    {
        if (is_map_config_line(lines[i]))
        {
            if (handle_config_line_err(config, gc, lines[i], map_started))
                return (-1); 
        }
        else if (is_map_desc_line(lines[i]))
        {
            if (map_started == 0)
                map_started = 1;
            (*map_len)++;
        }
        else if (!is_empty_line(lines[i]))
            return (print_err("Map error: Invalid configuration line!\n"));
    }
    return (0);
}

int parse_elements(t_config *config, t_gc *gc, char **lines, size_t *map_len)
{
    int     i;
    int     map_started;

    i = -1;
    map_started = 0;
    if (iterate_on_lines(config, gc, lines, map_len))
        return (-1);
    if (!config->floor_found || !config->ceil_found)
        return (print_err("Map error: Color configuration line missing\n"));
    if (set_config(config, gc, *map_len))
        return (-1);
    fetch_map_desc_lines(config->map.grid, lines, gc);
    return (0);
}

