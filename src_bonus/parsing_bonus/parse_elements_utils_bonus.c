#include "../../includes/cub3d_bonus.h"

int parse_color_helper(char **rgb, int *rgb_int, t_gc *gc, size_t len)
{
    if (len < 3 || len > 3)
    {
        free_split_alloc(rgb);
        return (print_err("Map error: Only 3 integers needed for a color!\n"));
    }
    if (!is_color_integer(rgb[0], &rgb_int[0], gc) 
        || !is_color_integer(rgb[1], &rgb_int[1], gc)
        || !is_color_integer(rgb[2], &rgb_int[2], gc))
    {
        free_split_alloc(rgb);
        return (print_err("Map error: Only digits are needed for each color!\n"));
    }
    return (0);
}

int is_color_line(const char *line)
{
    if (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2))
        return (0);
    return (1);
}

int is_color_integer(char *color, int *rgb_int, t_gc *gc)
{
    size_t i;
    char    *str_without_new_line;

    i = 0;
    str_without_new_line = NULL;
    while(i < ft_strlen(color))
    {
        if (!(color[i] >= '0' && color[i] <= '9') 
            && color[i] != '\n' && color[i] != '-'
            && color[i] != '+')
            return (0);
        if (color[i] == '\n') {
            str_without_new_line = ft_substr(color, 0, i, gc);
            break ;
        }
        i++;
    } 
    if (str_without_new_line != NULL)
        *rgb_int = ft_atoi(str_without_new_line);
    else
        *rgb_int = ft_atoi(color);
    return (1);
}

int is_path_line(const char *line)
{
    if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
        || !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
            return (1);
    return (0);
}

void    free_split_alloc(char **arr)
{
    int i;

    i = -1;
    while (arr[++i])
        free(arr[i]);
    free(arr);
}
