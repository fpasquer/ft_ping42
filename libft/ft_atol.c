#include "libft.h"

long				ft_atol(const char *str)
{
	int				ret;
	int				signe;
	size_t			i;

	signe = 1;
	ret = 0;
	i = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
		signe = str[i++] == '-' ? -1 : 1;
	while (ft_isdigit(str[i]) == 1)
		ret = ret * 10 + str[i++] - '0';
	return (ret * signe);
}