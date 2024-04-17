#include "libft.h"

void				ft_putchar_fd(char c, int fd)
{
	ssize_t			ret;
	
	ret = write(fd, &c, 1);
	ret = ret - 1;
}
