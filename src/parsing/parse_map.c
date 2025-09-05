/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:44:50 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 11:11:38 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	count_map_lines(const char *filename, t_gc *gc)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_err("Error opening file\n"), -1);
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

static char	**read_map_file_lines(const char *filename, t_gc *gc)
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

int	parse_cub3d_map(t_config *config, t_gc *gc, const char *filename)
{
	char	**lines;
	size_t	map_desc_len;

	map_desc_len = 0;
	if (ft_strncmp(filename + (ft_strlen(filename) - 4), ".cub", 4))
		return (print_err("Error: invalid file; need .cub extension file\n"));
	lines = read_map_file_lines(filename, gc);
	if (!lines)
		return (1);
	if (parse_elements(config, gc, lines, &map_desc_len)
		|| validate_config(config, gc)
		|| validate_map(config, gc, map_desc_len))
		return (-1);
	config->map.grid
	[(int)config->player.pos.y][(int)config->player.pos.x] = '0';
	return (0);
}

int	ft_check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	parse_color(const char *line, t_config *config, char conf_type, t_gc *gc)
{
	char	**rgb;
	int		rgb_int[3];
	size_t	len;

	rgb = ft_split(gc, line, ',');
	len = 0;
	if (check_for_an_empty_space_in(rgb))
		return (-1);
	while (rgb[len])
		len++;
	if (parse_color_helper(rgb, rgb_int, gc, len))
		return (-1);
	if (rgb_int[0] < 0 || rgb_int[0] > 255
		|| rgb_int[1] < 0 || rgb_int[1] > 255
		|| rgb_int[2] < 0 || rgb_int[2] > 255)
		return (print_err("Error: Each color need to be between 0 and 255\n"));
	if (conf_type == 'F')
		config->floor_color = (rgb_int[0] << 16)
			| (rgb_int[1] << 8) | rgb_int[2];
	else
		config->ceil_color = (rgb_int[0] << 16)
			| (rgb_int[1] << 8) | rgb_int[2];
	return (0);
}
