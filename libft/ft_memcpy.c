#include "libft.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dstChar;
	unsigned char	*strChar;

	dstChar = (unsigned char *)dst;
	strChar = (unsigned char *)src;
	for (i = 0; i < n; i++)
		dstChar[i] = strChar[i];
	return (dst);
}