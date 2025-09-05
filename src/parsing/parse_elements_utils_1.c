/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:09:00 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 13:19:13 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

static int	check_rgb_string(char *tmp)
{
	int	j;
	int	num_started;
	int	space_after_num;

	j = 0;
	num_started = 0;
	space_after_num = 0;
	while (tmp[j] && ft_isspace(tmp[j]))
		j++;
	while (tmp[j])
	{
		if (!ft_isspace(tmp[j]) && !num_started)
			num_started = 1;
		if (ft_isspace(tmp[j]) && num_started)
			space_after_num = 1;
		if (!ft_isspace(tmp[j]) && space_after_num)
			return (1);
		j++;
	}
	return (0);
}

int	check_for_an_empty_space_in(char **rgb)
{
	int		i;
	char	*tmp;

	i = -1;
	while (rgb[++i])
	{
		tmp = rgb[i];
		if (check_rgb_string(tmp))
			return (print_err("Error: invalid Number in the color\n"));
	}
	return (0);
}

int	handle_config_line_err(t_config *config, t_gc *gc, char *line,
		int map_started)
{
	if (map_started)
		return (print_err("Map error: Configuration lines inside "
				"the map description!\n"));
	if (handle_config_line(config, gc, line))
		return (-1);
	return (0);
}
