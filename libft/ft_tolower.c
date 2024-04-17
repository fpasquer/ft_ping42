#include "libft.h"

int					ft_tolower(int c)
{
	return (ft_isupper(c) == 1 ? c + 32 : c);
}