/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:12:40 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 14:14:06 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strjoin(char *s1, char *s2, t_gc *gc)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)gc_malloc(gc, 1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)gc_malloc(gc, (i + 1) * sizeof(char));
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			s3[i] = s1[i];
	while (s2[j])
		s3[i++] = s2[j++];
	s3[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (s3);
}
