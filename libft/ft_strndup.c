#include "libft.h"

char				*ft_strndup(const char *s1, size_t n)
{
	char			*str;

	if ((str = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}