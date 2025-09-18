/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:32:53 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 17:03:38 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	my_access(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
}

void	set_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.x = 0;
		player->dir.y = -1;
		set_plane(player, 0.66, 0);
	}
	if (dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = 1;
		set_plane(player, -0.66, 0);
	}
	if (dir == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
		set_plane(player, 0, 0.66);
	}
	if (dir == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
		set_plane(player, 0, -0.66);
	}
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
			return (print_err("Error: Color configuration line duplicated\n"));
		if (!ft_strncmp(line, "F ", 2))
		{
			config->floor_found = 1;
			config->last_map.f_color_flag = 1;
		}
		else if (!ft_strncmp(line, "C ", 2))
		{
			config->ceil_found = 1;
			config->last_map.c_color_flag = 1;
		}
		if (parse_color(line + 2, config, line[0], gc))
			return (-1);
	}
	return (0);
}

size_t	find_max_width(t_config *config)
{
	size_t	max_len;
	int		i;

	max_len = 0;
	i = -1;
	while (config->map.grid[++i])
	{
		if (ft_strlen(config->map.grid[i]) > max_len)
			max_len = ft_strlen(config->map.grid[i]);
	}
	return (max_len);
}

int	check_player_count(char **tmp_map, int *player_count, int i)
{
	int	j;

	j = -1;
	while (++j < (int)ft_strlen(tmp_map[i]))
	{
		if (tmp_map[i][j] == 'N' || tmp_map[i][j] == 'S'
			|| tmp_map[i][j] == 'E' || tmp_map[i][j] == 'W')
		{
			if (*player_count == 1)
				return (print_err("Map error: single player required!\n"));
			(*player_count)++;
		}
	}
	return (0);
}
