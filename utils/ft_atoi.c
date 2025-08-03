#include "../includes/cub3d.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	while (('\t' <= str[i] && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = 10 * number;
		if (number < number / 10)
			return (-(sign > 0));
		number += str[i++] - '0';
	}
	return (sign * number);
}
