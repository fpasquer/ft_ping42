#include "libft.h"

int					ft_isalpha(int c)
{
	if (ft_islower(c) != 0 || ft_isupper(c) != 0)
		return (1);
	return (0);
}