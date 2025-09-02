#include "../../includes/cub3d.h"

// Lecture du fichier .cub
static int	count_map_lines(const char *filename, t_gc *gc)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	line = get_next_line(fd, gc);
	while (line)
	{
		count++;
		line = get_next_line(fd, gc);
	}
	close(fd);
	return (count);
}

static  char	**read_map_file_lines(const char *filename, t_gc *gc)
{
	int		fd;
	char	**lines;
	char	*line;
	int		count;
	int		i;

	count = count_map_lines(filename, gc);
	if (count == 0)
		 return (print_err("Error: the map is empty\n"), NULL);
	lines = gc_malloc(gc, sizeof(char *) * (count + 1));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	line = get_next_line(fd, gc);
	while (line)
	{
		lines[i] = ft_strdup(line, gc);
		i++;
		line = get_next_line(fd, gc);
	}
	lines[i] = NULL;
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
	if(!lines)
		return (1);
    if (parse_elements(config, gc, lines, &map_desc_len) || validate_config(config, gc)
        || validate_map(config, gc, map_desc_len))
        return (-1);
    config->map.grid[(int)config->player.pos.y][(int)config->player.pos.x] = '0';
    return (0);
}
