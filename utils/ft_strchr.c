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
