/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:42:06 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/03 20:40:53 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_directions(int dx[4], int dy[4])
{
	dx[0] = 1;
	dy[0] = 0;
	dx[1] = -1;
	dy[1] = 0;
	dx[2] = 0;
	dy[2] = 1;
	dx[3] = 0;
	dy[3] = -1;
}

static void	add_neighbors(t_point *q, int *back, t_point p, int dx[4], int dy[4])
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (*back >= q->max_size)
			return ;
		q[*back].x = p.x + dx[i];
		q[*back].y = p.y + dy[i];
		(*back)++;
	}
}

int	check_for_invalide_char(char **tmp_map, t_point p)
{
	return (tmp_map[p.y][p.x] == '0' || tmp_map[p.y][p.x] == 'N'
		|| tmp_map[p.y][p.x] == 'S' || tmp_map[p.y][p.x] == 'E'
		|| tmp_map[p.y][p.x] == 'W');
}

void	init_vars(int *front, int *back)
{
	*front = 0;
	*back = 0;
}

int	flf_spce_helper(t_config *config, int *arr, char **tmp_map, t_point *q)
{
	int		dx[4];
	int		dy[4];
	t_point	p;

	init_directions(dx, dy);
	while (arr[0] < arr[1])
	{
		p = q[arr[0]++];
		if (p.x < 0 || p.y < 0 || p.x >= config->map.width
			|| p.y >= config->map.height)
			continue ;
		if (tmp_map[p.y][p.x] == '1' || tmp_map[p.y][p.x] == 'F')
			continue ;
		if (check_for_invalide_char(tmp_map, p))
			return (0);
		tmp_map[p.y][p.x] = 'F';
		add_neighbors(q, &arr[1], p, dx, dy);
	}
	return (1);
}

int	flood_fill_space_bfs(t_gc *gc, t_config *config, char **tmp_map, int x, int y)
{
	t_point	*q;
	int		front;
	int		back;
	int		front_and_back_arr[2];
	
	front_and_back_arr[0] = 0;
	front_and_back_arr[1] = 0;
	q = gc_malloc(gc, config->map.height * config->map.width * sizeof(t_point));
	init_vars(&front, &back);
	q[back++] = (t_point){x, y, config->map.height * config->map.width};
	if (!flf_spce_helper(config, front_and_back_arr, tmp_map, q))
		return (0);
	return (1);
}
