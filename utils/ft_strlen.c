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
