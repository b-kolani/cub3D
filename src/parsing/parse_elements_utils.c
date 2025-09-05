/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 18:19:40 by oait-si-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/04 11:47:00 by bkolani          ###   ########.fr       */
=======
/*   Updated: 2025/09/04 17:25:53 by oait-si-         ###   ########.fr       */
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_color_helper(char **rgb, int *rgb_int, t_gc *gc, size_t len)
{
	int	i;

	if (len < 3 || len > 3)
		return (print_err("Map error: Only 3 integers needed for a color!\n"));
	if (!is_color_integer(rgb[0], &rgb_int[0], gc)
		|| !is_color_integer(rgb[1], &rgb_int[1], gc)
		|| !is_color_integer(rgb[2], &rgb_int[2], gc))
	{
		i = -1;
		while (++i < 3)
			printf("the color [%d]; %d\n", i, rgb_int[i]);
		return (print_err("Error: Only digits are needed for each color!\n"));
	}
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
<<<<<<< HEAD
			&& color[i] != '\n' && color[i] != '-'
			&& color[i] != '+' && color[i] == ' ')
=======
			&& !ft_isspace(color[i]) && color[i] != '-' && color[i] != '+')
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
			return (0);
		i++;
	}
	*rgb_int = ft_atoi(color);
	return (1);
}

int	is_path_line(const char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "EA ", 3) || !ft_strncmp(line, "WE ", 3))
		return (1);
	return (0);
}

int	normalized(char **config_map, char **tmp,
	t_gc *gc, size_t max_len)
{
	int	i;
	int	j;

	i = -1;
	while (config_map[++i])
	{
		tmp[i] = gc_malloc(gc, max_len + 1);
		j = -1;
		while (config_map[i][++j])
			tmp[i][j] = config_map[i][j];
		while ((size_t)j < max_len)
			tmp[i][j++] = ' ';
		tmp[i][j] = '\0';
	}
	tmp[i] = NULL;
	return (0);
}
