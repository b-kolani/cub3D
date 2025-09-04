/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:09:00 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/04 21:21:36 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_values_for_iterate_on_line(int *i, int *map_started,
		int *first_map_line, int *last_map_line)
{
	*i = -1;
	*map_started = 0;
	*first_map_line = -1;
	*last_map_line = -1;
}

void	handle_vals_to_check_for_empty_line(int *i, int *map_started,
		int *first_map_line, int *last_map_line)
{
	if (*map_started == 0)
		*map_started = 1;
	if (*first_map_line == -1)
		*first_map_line = *i;
	*last_map_line = *i;
}

int	set_config(t_config *config, t_gc *gc, size_t map_len)
{
	config->map.grid = gc_malloc(gc, sizeof(char *) * (map_len + 1));
	config->map.height = map_len;
	return (0);
}

int	check_for_an_empty_space_in(char **rgb)
{
	int		i;
	int		j;
	char	*tmp;
	int		flag_for_char;
	int		flag_for_space;

	i = 0;
	while (rgb[i])
	{
		tmp = rgb[i];
		j = 0;
		flag_for_char = 0;
		flag_for_space = 0;
		while (tmp[j] && ft_isspace(tmp[j]))
			j++;
		while (tmp[j])
		{
			if (!ft_isspace(tmp[j]))
				flag_for_char = 1;
			if (ft_isspace(tmp[j]) && flag_for_char)
				flag_for_space = 1;
			if (!ft_isspace(tmp[j]) && flag_for_space)
				return (print_err("Error: invalid Number in the color \n"));
			j++;
		}
		i++;
	}
	return (0);
}

int	handle_config_line_err(t_config *config, t_gc *gc, char *line, int map_started)
{
	if (map_started)
		return (print_err("Map error: Configuration lines inside "
				"the map description!\n"));
	if (handle_config_line(config, gc, line))
		return (-1);
	return (0);
}
