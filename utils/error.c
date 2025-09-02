#include "../includes/cub3d.h"

int	print_err(const char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (1);
}
