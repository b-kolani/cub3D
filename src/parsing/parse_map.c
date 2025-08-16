#include "../../includes/cub3d.h"

// Lecture du fichier .cub
static char **read_map_file_lines(const char *filename, t_gc *gc)
{
    int fd;
    char    **lines;
    char    *line;
    int     i;

    fd = open(filename, O_RDONLY, 0644);
    if (fd == -1)
        return (NULL);
    lines = gc_malloc(gc, sizeof(char *) * 2048);

    line = NULL;
    i = -1;
    while ((line = get_next_line(fd, gc)) && i < 2047)
        lines[++i] = ft_strdup(line, gc);
    lines[++i] = NULL;
    close(fd);
    return (lines);
}

// Fonction principale du parsing
int	parse_cub3d_map(t_config *config, t_gc *gc, const char *filename)
{
    char    **lines;
    size_t  map_desc_len;

    map_desc_len = 0;
    if (ft_strncmp(filename + (ft_strlen(filename) - 4), ".cub", 4))
        return (print_err("File error: invalid file; need .cub extension file\n"));
    lines = read_map_file_lines(filename, gc);
    if (parse_elements(config, gc, lines, &map_desc_len)
        || validate_config(config, gc)
        || validate_map(config, gc, map_desc_len))
        return (-1);
    config->map.grid[(int)config->player.pos.y][(int)config->player.pos.x] = '0';
    return (0);
}
