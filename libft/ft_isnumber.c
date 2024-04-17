#include "libft.h"

int					ft_isnumber(char const *str)
{
	size_t			i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while(str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}