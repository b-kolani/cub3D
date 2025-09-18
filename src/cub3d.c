/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:33:04 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/17 22:13:14 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_comma(const char *line)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == ',')
			count++;
		if (count >= 3)
			return (1);
	}
	return (0);
}

int	is_valid(char *str)
{
	return (ft_strncmp(str + (ft_strlen(str) - 4), ".xpm", 4));
}

int	main(int ac, const char **av)
{
	t_game	*game;

	if (ac != 2)
		return (print_err("Usage: ./cub3D <map>.cub\n"));
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (print_err("game allocation failed\n"));
	game->gc = malloc(sizeof(t_gc));
	if (!game->gc)
		return (print_err("Allocation of gc failed\n"));
	game->gc->head = NULL;
	if (parse_cub3d_map(&game->config, game->gc, av[1]))
	{
		gc_free(game);
		return (-1);
	}
	if (rendering(game))
	{
		gc_free(game);
		return (-1);
	}
	gc_free(game);
	return (0);
}
