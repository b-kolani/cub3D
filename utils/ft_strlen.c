/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:12:13 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/03 18:12:15 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlen(const char *str)
{
	int		i;
	size_t	len;

	i = -1;
	len = 0;
	if (!str)
		return (0);
	while (str[++i])
		len++;
	return (len);
}
