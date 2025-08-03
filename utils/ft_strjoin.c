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
	if (!s3)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i])
			s3[i] = s1[i];
	while (s2[j])
		s3[i++] = s2[j++];
	s3[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	// free(s1);
	return (s3);
}
