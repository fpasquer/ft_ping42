#include "libft.h"

size_t				ft_strlcpy(char * dst, const char * src, size_t dstsize)
{
	size_t			i;
	size_t			srcLen;

	i = 0;
	srcLen = ft_strlen(src);
	if (dstsize == 0)
		return (srcLen);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srcLen);
}