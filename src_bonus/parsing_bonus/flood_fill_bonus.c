/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:25:06 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/08 12:53:46 by bkolani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

static void	add_neighbors(t_queue *q, t_point p, int dx[4], int dy[4])
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (q->back >= q->max_size)
			return ;
		q->data[q->back].x = p.x + dx[i];
		q->data[q->back].y = p.y + dy[i];
		q->back++;
	}
}

int	check_for_invalide_char(char **tmp_map, t_point p)
{
	return (tmp_map[p.y][p.x] == '0' || tmp_map[p.y][p.x] == 'N'
		|| tmp_map[p.y][p.x] == 'S' || tmp_map[p.y][p.x] == 'E'
		|| tmp_map[p.y][p.x] == 'W');
}

static int	process_point(t_bfs_args *args, t_point p,
	t_queue *q, int dxdy[2][4])
{
	if (p.x < 0 || p.y < 0 || p.x >= args->config->map.width
		|| p.y >= args->config->map.height)
		return (1);
	if (args->tmp_map[p.y][p.x] == '1' || args->tmp_map[p.y][p.x] == 'F')
		return (1);
	if (check_for_invalide_char(args->tmp_map, p))
		return (0);
	args->tmp_map[p.y][p.x] = 'F';
	add_neighbors(q, p, dxdy[0], dxdy[1]);
	return (1);
}

int	flood_fill_space_bfs(t_bfs_args *args, int x, int y)
{
	t_queue	q;
	int		dxdy[2][4];
	t_point	p;

	q.max_size = args->config->map.height * args->config->map.width;
	q.data = gc_malloc(args->gc, q.max_size * sizeof(t_point));
	init_vars(&q.front, &q.back);
	init_directions(dxdy[0], dxdy[1]);
	q.data[q.back++] = (t_point){x, y};
	while (q.front < q.back)
	{
		p = q.data[q.front++];
		if (!process_point(args, p, &q, dxdy))
			return (0);
	}
	return (1);
}
