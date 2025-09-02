#include "../../includes/cub3d.h"

// Flood_fill valider les acces du joueur depuis sa position
// aux positions ajaccentes pour detecter des fuites(comme carte non fermee)
// ou detection des vides a cote des caracteres '0' ou 'N' ou 'E' ou 'W' ou 'S

// int flood_fill_space(t_config *config, char **tmp_map, int x, int y)
// {
//     int width;
//     int height;

//     width = config->map.width;
//     height = config->map.height;
//     if (x < 0 || y < 0 || x >= width || y >= height)
//         return (1); // On sort de la map pas une fuite
//     if (tmp_map[y][x] == '1' || tmp_map[y][x] == 'F')
//         return (1);
//     if (tmp_map[y][x] == '0' || tmp_map[y][x] == 'N'
//         || tmp_map[y][x] == 'S' || tmp_map[y][x] == 'E'
//         || tmp_map[y][x] == 'W')
//         return (0); // Fuite detectee un espace est connecte a un '0' ou position du joueur
//     tmp_map[y][x] = 'F';
//     return (flood_fill_space(config, tmp_map, x + 1, y) &&
//             flood_fill_space(config, tmp_map, x, y + 1) &&
//             flood_fill_space(config, tmp_map, x - 1, y) &&
//             flood_fill_space(config, tmp_map, x, y - 1));
// }


typedef struct s_point
{
	int	x;
	int	y;
	int max_size;
}	t_point;

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


int	flood_fill_space_bfs(t_gc *gc, t_config *config, char **tmp_map, int x, int y)
{
	t_point	*q;
	int		front;
	int		back;
	int		dx[4];
	int		dy[4];
	t_point	p;

    q = gc_malloc(gc ,config->map.height * config->map.width * sizeof(t_point));
	front = 0;
	back = 0;
	init_directions(dx, dy);
	q[back++] = (t_point){x, y, config->map.height * config->map.width};
	while (front < back)
	{
		p = q[front++];
		if (p.x < 0 || p.y < 0 || p.x >= config->map.width || p.y >= config->map.height)
			continue ;
		if (tmp_map[p.y][p.x] == '1' || tmp_map[p.y][p.x] == 'F')
			continue ;
		if (tmp_map[p.y][p.x] == '0' || tmp_map[p.y][p.x] == 'N'
			|| tmp_map[p.y][p.x] == 'S' || tmp_map[p.y][p.x] == 'E'
			|| tmp_map[p.y][p.x] == 'W')
			return (0);
		tmp_map[p.y][p.x] = 'F';
		add_neighbors(q, &back, p, dx, dy);
	}
	return (1);
}
