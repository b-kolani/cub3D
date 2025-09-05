#include "../includes/cub3d.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!haystack || !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (++i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (j < len - i && needle[j]
				!= '\0' && haystack[j + i] == needle[j])
				j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
	}
	return (NULL);
}
