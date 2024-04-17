#include "libft.h"

char				*ft_strrchr(const char *s, int c)
{
	size_t			len;

	if ((len = ft_strlen(s)) == 0)
		return (NULL);
	else if (c == '\0')
		return ((char *)&s[len]);
	while(len-- > 0)
		if (s[len] == c)
			return ((char *)&s[len]);
	return (NULL);
}