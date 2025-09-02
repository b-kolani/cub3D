#include "../../includes/cub3d.h"

// Valider les elements
int	my_access(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

int	validate_config(t_config *config, t_gc *gc)
{
	if (!config->no || !config->so || !config->ea || !config->we)
		return (print_err("Map error: element path missing\n"));
	if (my_access(ft_substr(config->no, 0, ft_strlen(config->no), gc))
		|| my_access(ft_substr(config->so, 0, ft_strlen(config->so), gc))
		|| my_access(ft_substr(config->ea, 0, ft_strlen(config->ea), gc))
		|| my_access(ft_substr(config->we, 0, ft_strlen(config->we), gc)))
		return (print_err("Map error: Invalid path; file not found!\n"));
	return (0);
}
