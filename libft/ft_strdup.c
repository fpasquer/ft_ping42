#include "libft.h"

char				*ft_strdup(const char *s1)
{
	char			*str;
	size_t			len;

	len = ft_strlen(s1);
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}