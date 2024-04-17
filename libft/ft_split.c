#include "libft.h"

char				**ft_split(char const *s, char c)
{
	char			*tmp;
	char			**strs;
	size_t			i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
		if (s[i++] == c)
			count ++;
	if ((strs = (char **)malloc(sizeof(char *) * (count))) == NULL)
		return (NULL);
	i = 0;
	count = 0;
	while ((tmp = ft_strchr(s + i, c)) != NULL)
	{
		strs[count++] = ft_strndup(s + i, tmp - s - i);
		i += tmp - s - i + 1;
	}
	if (s[i] != '\0')
		strs[count++] = ft_strdup(s + i);
	return (strs);
}