/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkolani <bkolani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:42:06 by oait-si-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/03 20:40:53 by bkolani          ###   ########.fr       */
=======
/*   Updated: 2025/09/05 13:26:37 by oait-si-         ###   ########.fr       */
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
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

<<<<<<< HEAD
void	init_vars(int *front, int *back)
=======
static int	process_point(t_bfs_args *args, t_point p,
	t_queue *q, int dxdy[2][4])
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
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

<<<<<<< HEAD
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
=======
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
>>>>>>> fddb11d822baa0b625cedaa2bb1dc777ff361cc4
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
