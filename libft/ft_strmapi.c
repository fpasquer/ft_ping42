#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			i;
	char			*ret;

	i = 0;
	if ((ret = ft_calloc(1, sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	return ret;
}