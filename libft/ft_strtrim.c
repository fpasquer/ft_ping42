#include "libft.h"

char				*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	size_t			s1Len;
	size_t			start;
	size_t			end;

	s1Len = ft_strlen(s1);
	start = 0;
	while (start < s1Len && ft_strchr(set, s1[start]) != NULL)
		start++;
	end = s1Len;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	if ((str = (char *)malloc(sizeof(char) * (end - start + 1))) == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);	
}
