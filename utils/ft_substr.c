/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:12:24 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/03 18:12:37 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, t_gc *gc)
{
	char	*sub_str;
	size_t	s_len;
	size_t	cpy_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup("", gc));
	if (s_len - start < len)
		cpy_len = s_len - start;
	else
		cpy_len = len;
	sub_str = gc_malloc(gc, cpy_len + 1);
	ft_strlcpy(sub_str, s + start, cpy_len + 1);
	return (sub_str);
}
