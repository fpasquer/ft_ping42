#include "libft.h"

char				*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	size_t			s1Len;
	size_t			s2Len;

	s1Len = ft_strlen(s1);
	s2Len = ft_strlen(s2);
	if ((str = (char *)malloc(sizeof(char) * (s1Len + s2Len + 1))) == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1Len + 1);
	ft_strlcpy(str + s1Len, s2, s2Len + 1);
	return (str);
}