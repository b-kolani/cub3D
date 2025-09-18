/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:26:15 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/17 16:40:16 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

int	add_sprite(t_config *config, double x, double y, t_gc *gc)
{
	t_sprite	*new_arr;
	int			i;

	new_arr = gc_malloc(gc, sizeof(t_sprite) * (config->sprites_count + 1));
	i = -1;
	while (++i < config->sprites_count)
		new_arr[i] = config->sprites[i];
	new_arr[config->sprites_count].x = x + 0.5;
	new_arr[config->sprites_count].y = y + 0.5;
	new_arr[config->sprites_count].type = ITEM_TYPE;
	new_arr[config->sprites_count].active = true;
	new_arr[config->sprites_count].anim_index = 0;
	config->sprites = new_arr;
	config->sprites_count++;
	return (0);
}

int	add_door(t_config *config, int x, int y, t_gc *gc)
{
	t_door	*new_arr;
	int		i;

	if (is_door_valide(config->map.grid, x, y))
		return (print_err("Error: door is not surrounded by walls\n"));
	new_arr = gc_malloc(gc, sizeof(t_door) * (config->doors_count + 1));
	i = -1;
	while (++i < config->doors_count)
		new_arr[i] = config->doors[i];
	new_arr[config->doors_count].x = x + 0.5;
	new_arr[config->doors_count].y = y + 0.5;
	new_arr[config->doors_count].anim_timer = 0;
	new_arr[config->doors_count].is_open = false;
	new_arr[config->doors_count].type = DOOR_TYPE;
	new_arr[config->doors_count].door_offset = 0.0;
	new_arr[config->doors_count].state = 0;
	new_arr[config->doors_count].side_hit = 0;
	config->doors = new_arr;
	config->doors_count++;
	return (0);
}

int	parse_cub3d_map(t_config *config, t_gc *gc, const char *filename)
{
	char	**lines;
	size_t	map_desc_len;

	map_desc_len = 0;
	config->sprites = NULL;
	config->sprites_count = 0;
	config->doors = NULL;
	config->doors_count = 0;
	if (ft_strncmp(filename + (ft_strlen(filename) - 4), ".cub", 4)
		|| is_hidden(filename))
		return (print_err("Error: invalid file name need \'filename.cub\'\n"));
	lines = read_map_file_lines(filename, gc);
	if (!lines)
		return (print_err("Map error: Failed when getting map lines!\n"));
	if (parse_elements(config, gc, lines, &map_desc_len)
		|| validate_config(config, gc)
		|| validate_map(config, gc, map_desc_len))
		return (-1);
	if (fill_sprites_and_doors_arrays(config, gc))
		return (-1);
	return (0);
}
