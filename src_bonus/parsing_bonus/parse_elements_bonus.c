/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:25:38 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 17:18:54 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	set_config(t_config *config, t_gc *gc, size_t map_len)
{
	config->map.grid = gc_malloc(gc, sizeof(char *) * (map_len + 1));
	config->map.height = map_len;
	if (!config->map.grid)
		return (print_err("gc_malloc error: grid allocation failed!\n"));
	return (0);
}

int	get_element_path(const char *line, t_config *config, t_gc *gc)
{
	if (!ft_strncmp(line, "NO ", 3) && config->no == NULL)
	{
		config->no = clean_path(line + 3, gc);
		config->last_map.no_path_flag = 1;
	}
	else if (!ft_strncmp(line, "SO ", 3) && config->so == NULL)
	{
		config->so = clean_path(line + 3, gc);
		config->last_map.so_path_flag = 1;
	}
	else if (!ft_strncmp(line, "EA ", 3) && config->ea == NULL)
	{
		config->ea = clean_path(line + 3, gc);
		config->last_map.ea_path_flag = 1;
	}
	else if (!ft_strncmp(line, "WE ", 3) && config->we == NULL)
	{
		config->we = clean_path(line + 3, gc);
		config->last_map.we_path_flag = 1;
	}
	else
		return (print_err("Error: Element configuration line duplicated!\n"));
	return (0);
}

// int	get_element_path(const char *line, t_config *config, t_gc *gc)
// {
// 	if (!ft_strncmp(line, "NO ", 3) && config->no == NULL)
// 		config->no = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
// 	else if (!ft_strncmp(line, "SO ", 3) && config->so == NULL)
// 		config->so = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
// 	else if (!ft_strncmp(line, "EA ", 3) && config->ea == NULL)
// 		config->ea = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
// 	else if (!ft_strncmp(line, "WE ", 3) && config->we == NULL)
// 		config->we = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
// 	else
// 		return (print_err("Map error: Element "
// 				"configuration line duplicated!\n"));
// 	return (0);
// }

// static int	handle_config_line(t_config *config, t_gc *gc, char *line)
// {
// 	if (is_path_line(line))
// 	{
// 		if (get_element_path(line, config, gc))
// 			return (-1);
// 	}
// 	else if (is_color_line(line))
// 	{
// 		if ((!ft_strncmp(line, "F ", 2) && config->floor_found)
// 			|| (!ft_strncmp(line, "C ", 2) && config->ceil_found))
// 			return (print_err("Map error: Color "
// 					"configuration line duplicated\n"));
// 		if (!ft_strncmp(line, "F ", 2))
// 			config->floor_found = 1;
// 		else if (!ft_strncmp(line, "C ", 2))
// 			config->ceil_found = 1;
// 		if (parse_color(line + 2, config, line[0], gc))
// 			return (-1);
// 	}
// 	return (0);
// }

int	iterate_on_lines(t_config *config, t_gc *gc, char **lines, size_t *map_len)
{
	t_iter_state	list;
	t_parse_ctx		context;

	init_values_to_iterate_on_line(&list.i, &list.map_started,
		&list.f_map_line, &list.l_map_line);
	context.config = config;
	context.gc = gc;
	context.lines = lines;
	context.state = &list;
	context.map_len = map_len;
	while (lines[++list.i])
	{
		if (process_line(&context))
			return (-1);
	}
	if (*map_len > 0 && *map_len
		!= (size_t)(list.l_map_line - list.f_map_line + 1))
		return (print_err("Error: Empty lines inside map description!\n"));
	return (0);
}

int	parse_elements(t_config *config, t_gc *gc, char **lines, size_t *map_len)
{
	if (iterate_on_lines(config, gc, lines, map_len))
		return (-1);
	if (!config->floor_found || !config->ceil_found)
		return (print_err("Map error: Color configuration line missing\n"));
	if (set_config(config, gc, *map_len))
		return (-1);
	fetch_map_desc_lines(config, lines, gc);
	return (0);
}
