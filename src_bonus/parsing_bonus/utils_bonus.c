/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:03:39 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 22:21:35 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	check_middle_rows(t_map map, int i, t_gc *gc)
{
	int		last_char_idx;
	char	*str_trimmed;

	str_trimmed = ft_strtrim(map.grid[i], " \t\n\r", gc);
	last_char_idx = ft_strlen(str_trimmed) - 1;
	if (str_trimmed[0] != '1' || str_trimmed[last_char_idx] != '1')
		return (print_err("Map error: Invalid row!\n"));
	return (0);
}

void	init_vars(int *front, int *back)
{
	*front = 0;
	*back = 0;
}

int	find_player_position(t_config *config, char **tmp_map)
{
	int	i;
	int	player_count;

	i = -1;
	player_count = 0;
	while (tmp_map[++i])
	{
		if (check_player_count(tmp_map, &player_count, i))
			return (-1);
		if (player_count == 1 && (ft_strchr(tmp_map[i], 'N')
				|| ft_strchr(tmp_map[i], 'S') || ft_strchr(tmp_map[i], 'E')
				|| ft_strchr(tmp_map[i], 'W')))
			set_player_details(config, tmp_map, i);
	}
	if (player_count == 0)
		return (print_err("Error: Player not found\n"));
	return (0);
}

int	is_door_valide(char **grid, int x, int y)
{
	if (((grid[y][x - 1] == '1' && grid[y][x + 1] == '1')
		|| (grid[y + 1][x] == '1' && grid[y - 1][x] == '1')))
		return (0);
	return (1);
}

int	process_line(t_parse_ctx *context)
{
	int		i;
	char	*trimed;

	i = context->state->i;
	if (is_map_config_line(context->lines[i], context->gc))
	{
		trimed = clean_path(context->lines[i], context->gc);
		if (handle_config_line_err(context->config, context->gc,
				trimed, context->state->map_started))
			return (-1);
	}
	else if (is_map_desc_line(context->lines[i]))
	{
		if (is_last(context))
			return (print_err("Error: the map content must be the last!\n"));
		handle_vals_to_check_for_empty_line(&context->state->i,
			&context->state->map_started,
			&context->state->f_map_line,
			&context->state->l_map_line);
		(*context->map_len)++;
	}
	else if (!is_empty_line(context->lines[i]))
		return (print_err("Error: Invalid configuration line!\n"));
	return (0);
}
