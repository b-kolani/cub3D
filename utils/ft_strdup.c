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
