#include "libft.h"

char				*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				len;
	unsigned int	nb;

	i = 0;
	len = 1;
	nb = n < 0 ? -n : n;
	while ((unsigned int)(nb / ft_pow(10.0, len)) > 0)
		len++;
	if (n < 0)
		len++;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (n < 0)
	{
		str[i++] = '-';
		len--;
	}
	while (len-- > 0)
	{
		str[i++] = nb / ft_pow(10.0, len) + '0';
		nb %= (unsigned int)ft_pow(10.0, len);
	}
	str[i] = '\0';
	return (str);
}