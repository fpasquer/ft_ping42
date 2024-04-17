#include "libft.h"

int					ft_toupper(int c)
{
	return (ft_islower(c) == 1 ? c - 32 : c);
}