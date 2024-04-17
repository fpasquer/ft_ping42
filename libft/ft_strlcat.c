#include "libft.h"

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			dstLen;
	size_t			srcLen;

	i = 0;
	dstLen = ft_strlen(dst);
	srcLen = ft_strlen(src);
	if (dstsize <= dstLen)
		return (srcLen + dstsize);
	while (src[i] != '\0' && i < dstsize - dstLen - 1)
	{
		dst[dstLen + i] = src[i];
		i++;
	}
	dst[dstLen + i] = '\0';
	return (dstLen + srcLen);
}