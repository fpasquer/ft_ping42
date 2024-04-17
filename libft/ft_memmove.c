#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstChar;
	unsigned char	*srcChar;
	size_t			i;

	dstChar = (unsigned char *)dst;
	srcChar = (unsigned char *)src;
	i = dstChar > srcChar ? len : 0;
	if (dstChar > srcChar)
		while(i-- > 0)
			dstChar[i] = srcChar[i];
	else if (dstChar < srcChar)
		while (i < len)
		{
			dstChar[i] = srcChar[i];
			i++;
		}
	return (dst);
}