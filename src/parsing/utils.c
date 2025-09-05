/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:25:20 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 13:26:16 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_middle_rows(t_map map, int i)
{
	int	last_char_idx;

	last_char_idx = ft_strlen(map.grid[i]) - 1;
	if ((map.grid[i][0] != '1' && !ft_isspace(map.grid[i][0]))
		|| (map.grid[i][last_char_idx] != '1'
		&& !ft_isspace(map.grid[i][last_char_idx])))
		return (print_err("Map error: invalid walls!\n"));
	return (0);
}

void	init_vars(int *front, int *back)
{
	*front = 0;
	*back = 0;
}
