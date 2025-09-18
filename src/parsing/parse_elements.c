/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:41:03 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/17 16:33:22 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strtrim(char const *s1, char const *set, t_gc *gc)
{
	size_t	start;
	size_t	end;
	char	*neww;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_check_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_check_set(s1[end - 1], set))
		end--;
	neww = (char *)gc_malloc(gc, sizeof(char) * (end - start + 1));
	ft_strlcpy(neww, s1 + start, end - start + 1);
	return (neww);
}

char	*clean_path(const char *line, t_gc *gc)
{
	char	*trimmed;

	while (*line && ft_isspace(*line))
		line++;
	trimmed = ft_strtrim(line, " \t\n\r", gc);
	if (*trimmed == '\0')
	{
		print_err("Error: Empty or invalid texture path\n");
		return (NULL);
	}
	return (trimmed);
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
	set_config(config, gc, *map_len);
	fetch_map_desc_lines(config->map.grid, lines, gc);
	return (0);
}
