/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:13:30 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/16 22:53:47 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((n < 1) || (s1 == s2))
		return (0);
	if (*s1 && *s1 == *s2)
		return (ft_strncmp(s1 + 1, s2 + 1, n - 1));
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
