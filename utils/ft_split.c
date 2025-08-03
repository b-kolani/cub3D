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

static char	*substr(const char *s, int start, int end)
{
	char	*sub;
	size_t	len;

	len = end - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

static char	**create_result(char const *s, char **result, char c, int start)
{
	int	end;
	int	index;

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
		result[index] = substr(s, start, end);
		if (!result[index])
		{
			while (index > 0)
				free(result[--index]);
			return (NULL);
		}
		index++;
		start = end;
	}
	result[index] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		start;

	start = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc((count_substrs(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!(create_result(s, result, c, start)))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
