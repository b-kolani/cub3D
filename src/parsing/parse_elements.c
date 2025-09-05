/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:41:03 by oait-si-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/03 20:45:02 by bkolani          ###   ########.fr       */
=======
/*   Updated: 2025/09/05 11:07:55 by oait-si-         ###   ########.fr       */
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
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
		config->no = clean_path(line + 3, gc);
	else if (!ft_strncmp(line, "SO ", 3) && config->so == NULL)
		config->so = clean_path(line + 3, gc);
	else if (!ft_strncmp(line, "EA ", 3) && config->ea == NULL)
		config->ea = clean_path(line + 3, gc);
	else if (!ft_strncmp(line, "WE ", 3) && config->we == NULL)
		config->we = clean_path(line + 3, gc);
	else
		return (print_err("Error: Element configuration line duplicated!\n"));
	return (0);
}

int	iterate_on_lines(t_config *config, t_gc *gc, char **lines, size_t *map_len)
{
	int	i;
	int	map_started;
	int	f_map_line;
	int	l_map_line;

	init_values_to_iterate_on_line(&i, &map_started, &f_map_line, &l_map_line);
	while (lines[++i])
	{
		if (is_map_config_line(lines[i]))
		{
			if (handle_config_line_err(config, gc, lines[i], map_started))
				return (-1);
		}
		else if (is_map_desc_line(lines[i]))
		{
			handle_vals_to_check_for_empty_line(&i, &map_started,
				&f_map_line, &l_map_line);
			(*map_len)++;
		}
		else if (!is_empty_line(lines[i]))
			return (print_err("Error: Invalid configuration line!\n"));
	}
	if (*map_len > 0 && *map_len != (size_t)(l_map_line - f_map_line + 1))
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
