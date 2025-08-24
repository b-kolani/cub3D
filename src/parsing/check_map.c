#include "../../includes/cub3d.h"

// Recuperer toutes lignes de description de
// la carte
void    fetch_map_desc_lines(char **grid, char **lines, t_gc *gc)
{
    int i;
    int j;

    i = -1;
    j = -1;
    while (lines[++i])
    {
        if (is_map_desc_line(lines[i]))
            grid[++j] = ft_substr(lines[i], 0, ft_strlen(lines[i]), gc);
    }
    grid[++j] = NULL;

}

// Verifier si une ligne de la carte est vide ou pas
int	is_empty_line(const char *line)
{
    int i;

    i = -1;
    while(line[++i])
    {
        if (!ft_isspace(line[i]))
            return (0);
    }
    return (1);
}

// Verifier si une ligne est une configuration ou pas
int	is_map_config_line(const char *line)
{
    if (ft_strncmp(line, "NO ", 3) != 0 && ft_strncmp(line, "SO ", 3) != 0
        && ft_strncmp(line, "EA ", 3) != 0 && ft_strncmp(line, "WE ", 3) != 0
        && ft_strncmp(line, "F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
        return (0);
    return (1);
}

// Verifier si une ligne est une description de la carte 
// ou pas
int	is_map_desc_line(const char *line)
{
    int i;

    i = -1;
    while(line[++i])
    {
        if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i])
            && line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
            && line[i] != 'W')
            return (0);
    }
    if (is_empty_line(line))
        return (0);
    return (1);
}
