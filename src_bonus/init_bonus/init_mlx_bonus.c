/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:19:02 by bkolani           #+#    #+#             */
/*   Updated: 2025/09/17 22:20:40 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	init_mlx(t_mlx *mlx_)
{
	mlx_->mlx_ptr = mlx_init();
	if (!mlx_->mlx_ptr)
		return (print_err("mlx error: Failed to connect to mlx server\n"));
	mlx_->win_ptr = mlx_new_window(mlx_->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!mlx_->win_ptr)
		return (print_err("mlx error: Failed to create a new window\n"));
	return (0);
}

int	is_hidden(const char *path)
{
	const char	*base;

	base = path + ft_strlen(path);
	while (base > path && *(base - 1) != '/')
		base--;
	return (base[0] == '.');
}

int	is_valid(char *str)
{
	return (ft_strncmp(str + (ft_strlen(str) - 4), ".xpm", 4));
}
