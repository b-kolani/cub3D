/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:13:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/04 13:13:02 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup(const char *s, t_gc *gc)
{
	char	*cpy;
	size_t	s_len;

	s_len = ft_strlen(s);
	cpy = gc_malloc(gc, s_len + 1);
	ft_strlcpy(cpy, s, s_len + 1);
	return (cpy);
}
