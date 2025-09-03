/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_0.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:09:00 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/03 13:15:53 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_config(t_config *config, t_gc *gc, size_t map_len)
{
	config->map.grid = gc_malloc(gc, sizeof(char *) * (map_len + 1));
	config->map.height = map_len;
	return (0);
}

int	get_element_path(const char *line, t_config *config, t_gc *gc)
{
	if (!ft_strncmp(line, "NO ", 3) && config->no == NULL)
		config->no = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
	else if (!ft_strncmp(line, "SO ", 3) && config->so == NULL)
		config->so = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
	else if (!ft_strncmp(line, "EA ", 3) && config->ea == NULL)
		config->ea = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
	else if (!ft_strncmp(line, "WE ", 3) && config->we == NULL)
		config->we = ft_substr(line, 3, ft_strlen(line + 3) - 1, gc);
	else
		return (print_err("Map error: Element "
				"configuration line duplicated!\n"));
	return (0);
}

int	parse_color(const char *line, t_config *config,char conf_type, t_gc *gc)
{
	char	**rgb;
	int		rgb_int[3];
	size_t	len;

	rgb = ft_split(gc ,line, ',');
	len = 0;
	while (rgb[len])
		len++;
	if (parse_color_helper(rgb, rgb_int, gc, len))
		return (-1);
	if (!(rgb_int[0] >= 0 && rgb_int[0] <= 255)
		|| !(rgb_int[1] >= 0 && rgb_int[1] <= 255)
		|| !(rgb_int[2] >= 0 && rgb_int[2] <= 255))
		return (print_err("Map error: Each color need"
				" to be between 0 and 255\n"));
	if (conf_type == 'F')
		config->floor_color = (rgb_int[0] << 16)
			| (rgb_int[1] << 8) | rgb_int[2];
	else
		config->ceil_color = (rgb_int[0] << 16)
			| (rgb_int[1] << 8) | rgb_int[2];
	return (0);
}

int	handle_config_line(t_config *config, t_gc *gc, char *line)
{
	if (is_path_line(line))
	{
		if (get_element_path(line, config, gc))
			return (-1);
	}
	else if (is_color_line(line))
	{
		if ((!ft_strncmp(line, "F ", 2) && config->floor_found)
			|| (!ft_strncmp(line, "C ", 2) && config->ceil_found))
			return (print_err("Map error: Color configuration "
					"line duplicated\n"));
		if (!ft_strncmp(line, "F ", 2))
			config->floor_found = 1;
		else if (!ft_strncmp(line, "C ", 2))
			config->ceil_found = 1;
		if (parse_color(line + 2, config, line[0], gc))
			return (-1);
	}
	return (0);
}
