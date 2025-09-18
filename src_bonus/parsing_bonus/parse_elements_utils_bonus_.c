/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils_bonus_.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:55:51 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 22:18:08 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

int	parse_color(const char *line, t_config *config,
	char conf_type, t_gc *gc)
{
	char	**rgb;
	int		rgb_int[3];
	size_t	len;

	if (count_comma(line))
		return (print_err("Error: only 3 Numbers for colors\n"));
	rgb = ft_split(gc, line, ',');
	len = 0;
	if (check_for_an_empty_space_in(rgb))
		return (-1);
	while (rgb[len])
		len++;
	if (parse_color_helper(rgb, rgb_int, gc, len))
		return (-1);
	if (rgb_int[0] < 0 || rgb_int[0] > 255
		|| rgb_int[1] < 0 || rgb_int[1] > 255
		|| rgb_int[2] < 0 || rgb_int[2] > 255)
		return (print_err("Error: Each color need to be between 0 and 255\n"));
	if (conf_type == 'F')
		config->floor_color = (rgb_int[0] << 16)
			| (rgb_int[1] << 8) | rgb_int[2];
	else
		config->ceil_color = (rgb_int[0] << 16)
			| (rgb_int[1] << 8) | rgb_int[2];
	return (0);
}

int	handle_config_line_err(t_config *config, t_gc *gc, char *line,
		int map_started)
{
	(void)map_started;
	if (handle_config_line(config, gc, line))
		return (-1);
	return (0);
}

int	ft_check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
