#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < start && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (NULL);
	return (ft_strndup(s + i, len));
}