/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:48:40 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/04 18:07:06 by oait-si-         ###   ########.fr       */
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
	printf("dans access\n");
	if (my_access(config->no) || my_access(config->so)
		|| my_access(config->ea) || my_access(config->we))
	{
		return (print_err("Map error: Invalid path; file not found!\n"));
	}
	return (0);
}
