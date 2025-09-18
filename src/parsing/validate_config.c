/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:48:40 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/17 22:09:58 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_player_x_pos(t_config *config, char *pos_line)
{
	int	j;

	j = -1;
	while (pos_line[++j])
	{
		if (pos_line[j] == 'N' || pos_line[j] == 'S'
			|| pos_line[j] == 'E' || pos_line[j] == 'W')
		{
			config->player.pos.x = j + 0.5;
			break ;
		}
	}
}

void	set_plane(t_player *player, double x, double y)
{
	player->plane.x = x;
	player->plane.y = y;
}

void	set_player_orientation(t_player *player, char *pos_line)
{
	char	dir;
	int		i;

	i = -1;
	while (pos_line[++i])
	{
		if (pos_line[i] == 'N' || pos_line[i] == 'S'
			|| pos_line[i] == 'E' || pos_line[i] == 'W')
			dir = pos_line[i];
	}
	set_direction(player, dir);
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

int	check_first_last_rows(t_map map, int i)
{
	int	j;

	j = -1;
	while (map.grid[i][++j])
	{
		if (map.grid[i][j] != '1' && !ft_isspace(map.grid[i][j]))
			return (print_err("Map error: walls required!\n"));
	}
	return (0);
}
