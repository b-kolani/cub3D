/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:46:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/02 21:50:56 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// int	my_access(char *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	close(fd);
// 	return (0);
// }

// int	validate_config(t_config *config, t_gc *gc)
// {
// 	if (!config->no || !config->so || !config->ea || !config->we)
// 		return (print_err("Map error: element path missing\n"));
// 	if (my_access(config->no) || my_access(config->so)
// 		|| my_access(config->ea) || my_access(config->we))
// 		return (print_err("Map error: Invalid path; file not found!\n"));
// 	return (0);
// }
