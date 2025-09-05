/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:40:55 by oait-si-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/03 20:18:20 by bkolani          ###   ########.fr       */
=======
/*   Updated: 2025/09/05 13:19:26 by oait-si-         ###   ########.fr       */
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fetch_map_desc_lines(char **grid, char **lines, t_gc *gc)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (lines[++i])
	{
		if (is_map_desc_line(lines[i]))
			grid[++j] = ft_substr(lines[i], 0, ft_strlen(lines[i]), gc);
	}
	grid[++j] = NULL;
}

int	is_empty_line(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isspace(line[i]))
			return (0);
	}
	return (1);
}

int	is_map_config_line(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) != 0
		&& ft_strncmp(line, "SO ", 3) != 0
		&& ft_strncmp(line, "EA ", 3) != 0
		&& ft_strncmp(line, "WE ", 3) != 0
		&& ft_strncmp(line, "F ", 2) != 0
		&& ft_strncmp(line, "C ", 2) != 0)
		return (0);
	return (1);
}

int	is_map_desc_line(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1'
			&& line[i] != '0'
			&& !ft_isspace(line[i])
			&& line[i] != 'N'
			&& line[i] != 'S'
			&& line[i] != 'E'
			&& line[i] != 'W')
			return (0);
	}
	if (is_empty_line(line))
		return (0);
	return (1);
}

void	init_values_to_iterate_on_line(int *i, int *map_started,
			int *first_map_line, int *last_map_line)
{
	*i = -1;
	*map_started = 0;
	*first_map_line = -1;
	*last_map_line = -1;
}
