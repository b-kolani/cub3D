/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:29:43 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 22:16:00 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	is_path_line(const char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		return (1);
	return (0);
}

int	check_rgb_string(char *tmp)
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
	if (!num_started && !space_after_num)
		return (1);
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

void	handle_vals_to_check_for_empty_line(int *i, int *map_started,
			int *first_map_line, int *last_map_line)
{
	if (*map_started == 0)
		*map_started = 1;
	if (*first_map_line == -1)
		*first_map_line = *i;
	*last_map_line = *i;
}

int	is_last(t_parse_ctx *context)
{
	return (!context->config->last_map.we_path_flag
		|| !context->config->last_map.so_path_flag
		|| !context->config->last_map.f_color_flag
		|| !context->config->last_map.c_color_flag
		|| !context->config->last_map.no_path_flag
		|| !context->config->last_map.ea_path_flag);
}
