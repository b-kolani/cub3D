/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:32:12 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/05 17:04:25 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

static void	set_direction(t_player *player, char dir)
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
// int validate_config(t_config *config, t_gc *gc)
// {
//     if (!config->no || !config->so || !config->ea || !config->we)
//         return (print_err("Map error: element path missing\n"));
//     if (access(ft_substr(config->no, 0, ft_strlen(config->no), gc), F_OK)
//         || access(ft_substr(config->so, 0, ft_strlen(config->so), gc), F_OK)
//         || access(ft_substr(config->ea, 0, ft_strlen(config->ea), gc), F_OK)
//         || access(ft_substr(config->we, 0, ft_strlen(config->we), gc), F_OK))
//         return (print_err("Map error: Invalid path; file not found!\n"));
//     return (0);
// }
