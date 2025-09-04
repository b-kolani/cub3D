/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:46:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/04 21:36:56 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
			return (print_err("Map error: Color configuration line duplicated\n"));
		if (!ft_strncmp(line, "F ", 2))
			config->floor_found = 1;
		else if (!ft_strncmp(line, "C ", 2))
			config->ceil_found = 1;
		if (parse_color(line + 2, config, line[0], gc))
			return (-1);
	}
	return (0);
}