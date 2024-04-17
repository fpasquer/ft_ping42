#include "libft.h"

double				ft_pow(double nb, int exp)
{
	double			ret;
	int				entier;

	if (nb == 0)
		return (0.0);
	if (exp == 0)
		return ((nb < 0) ? -1.0 : 1.0);
	ret = 1;
	entier = exp;
	while (entier != 0)
	{
		ret = (exp > 0) ? ret * nb : ret / nb;
		entier = (entier < 0) ? entier + 1 : entier - 1;
	}
	return (ret);
}