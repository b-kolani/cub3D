/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:33:06 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/09 12:40:27 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

static int	check_walls(t_map map, t_gc *gc)
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
			if (check_middle_rows(map, i, gc))
				return (-1);
		}
	}
	return (0);
}

void	set_player_details(t_config *config, char **tmp_map, int i)
{
	config->player.pos.y = i + 0.5;
	set_player_x_pos(config, tmp_map[(int)config->player.pos.y]);
	set_player_orientation(&config->player, tmp_map[(int)config->player.pos.y]);
}

static int	normalized(char **config_map, char **tmp, t_gc *gc, size_t max_len)
{
	int	i;
	int	j;

	i = -1;
	while (config_map[++i])
	{
		tmp[i] = gc_malloc(gc, max_len + 1);
		if (!tmp[i])
			return (print_err("gc_malloc error: tmp allocation failed\n"));
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

int	validate_map(t_config *config, t_gc *gc, size_t map_len)
{
	char	**tmp;
	size_t	max_len;

	if (check_walls(config->map, gc))
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
