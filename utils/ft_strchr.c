/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:12:32 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 14:12:34 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strchr(const char *str, int c)
{
	if (!str || !c)
		return (NULL);
	while (*str && *str != c)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}
