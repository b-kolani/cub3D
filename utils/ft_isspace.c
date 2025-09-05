#include "../includes/cub3d.h"

int	ft_isspace(const char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}
