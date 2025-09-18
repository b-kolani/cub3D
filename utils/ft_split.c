/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:55:55 by oait-si-          #+#    #+#             */
/*   Updated: 2025/09/05 14:22:37 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_substrs(char const *s, char c)
{
	int	count;
	int	in_substr;

	count = 0;
	in_substr = 0;
	while (*s)
	{
		if (*s != c && !in_substr)
		{
			in_substr = 1;
			count++;
		}
		else if (*s == c)
			in_substr = 0;
		s++;
	}
	return (count);
}

static char	*substr(t_gc *gc, const char *s, int start, int end)
{
	char	*sub;
	size_t	len;

	len = end - start;
	sub = (char *)gc_malloc(gc, len + 1);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

static char	**create_result(t_gc *gc, char const *s,
		char **result, char c)
{
	int	end;
	int	index;
	int	start;

	start = 0;
	index = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start] == '\0')
			break ;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		result[index] = substr(gc, s, start, end);
		index++;
		start = end;
	}
	result[index] = NULL;
	return (result);
}

char	**ft_split(t_gc *gc, char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)gc_malloc(gc, (count_substrs(s, c) + 1)
			* sizeof(char *));
	result = create_result(gc, s, result, c);
	return (result);
}
