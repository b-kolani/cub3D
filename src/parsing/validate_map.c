/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:55:31 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 13:26:01 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	detect_map_leaks(t_gc *gc, t_config *config, char **tmp)
{
	int			x;
	int			y;
	t_bfs_args	args;

	args.config = config;
	args.gc = gc;
	args.tmp_map = tmp;
	y = -1;
	while (++y < config->map.height)
	{
		x = -1;
		while (++x < config->map.width)
		{
			if (tmp[y][x] == ' ')
			{
				if (!flood_fill_space_bfs(&args, x, y))
					return (-1);
			}
		}
	}
	return (0);
}

static int	check_walls(t_map map)
{
	int	i;

	i = -1;
	while (++i < map.height)
	{
		if (i == 0 || i == map.height - 1)
		{
			if (check_first_last_rows(map, i))
				return (-1);
		}
		else
		{
			if (check_middle_rows(map, i))
				return (-1);
		}
	}
	return (0);
}

static void	set_player_details(t_config *config, char **tmp_map, int i)
{
	config->player.pos.y = i + 0.5;
	set_player_x_pos(config, tmp_map[(int)config->player.pos.y]);
	set_player_orientation(&config->player, tmp_map[(int)config->player.pos.y]);
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
	return (0);
}

int	validate_map(t_config *config, t_gc *gc, size_t map_len)
{
	char	**tmp;
	size_t	max_len;

	if (check_walls(config->map))
		return (-1);
	max_len = find_max_width(config);
	config->map.width = max_len;
	tmp = gc_malloc(gc, sizeof(char *) * (map_len + 1));
	if (normalized(config->map.grid, tmp, gc, max_len))
		return (-1);
	if (find_player_position(config, tmp))
		return (-1);
	if (detect_map_leaks(gc, config, tmp))
		return (print_err("Map error: leak detected!\n"));
	return (0);
}
