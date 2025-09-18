/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_bonus__.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:01:11 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 22:20:03 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	parse_color_helper(char **rgb, int *rgb_int, t_gc *gc, size_t len)
{
	if (len < 3 || len > 3)
		return (print_err("Map error: Only 3 integers needed for a color!\n"));
	if (!is_color_integer(rgb[0], &rgb_int[0], gc)
		|| !is_color_integer(rgb[1], &rgb_int[1], gc)
		|| !is_color_integer(rgb[2], &rgb_int[2], gc))
		return (print_err("Map error: Only "
				"digits are needed for each color!\n"));
	return (0);
}

int	is_color_line(const char *line)
{
	if (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2))
		return (0);
	return (1);
}

int	is_color_integer(char *color, int *rgb_int, t_gc *gc)
{
	size_t	i;
	char	*str_without_new_line;

	i = 0;
	(void)gc;
	str_without_new_line = NULL;
	while (i < ft_strlen(color))
	{
		if (!(color[i] >= '0' && color[i] <= '9')
			&& !ft_isspace(color[i]))
			return (0);
		i++;
	}
	*rgb_int = ft_atoi(color);
	return (1);
}

int	fill_sprites_and_doors_arrays(t_config *config, t_gc *gc)
{
	int	i;
	int	j;

	i = -1;
	while (config->map.grid[++i])
	{
		j = -1;
		while (config->map.grid[i][++j])
		{
			if (config->map.grid[i][j] == '3')
			{
				if (add_sprite(config, j, i, gc))
					return (-1);
			}
			else if (config->map.grid[i][j] == '4')
			{
				if (add_door(config, j, i, gc))
					return (-1);
			}
		}
	}
	return (0);
}

int	validate_config(t_config *config, t_gc *gc)
{
	(void)gc;
	if (!config->no || !config->so || !config->ea || !config->we)
		return (print_err("Map error: element path missing\n"));
	if (my_access(config->no) || my_access(config->so)
		|| my_access(config->ea) || my_access(config->we)
		|| is_hidden(config->no) || is_hidden(config->so)
		|| is_hidden(config->ea) || is_hidden(config->we)
		|| is_valid(config->ea) || is_valid(config->no)
		|| is_valid(config->so) || is_valid(config->we))
		return (print_err("Map error: Invalid path !\n"));
	return (0);
}
