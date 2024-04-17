#include "../incs/ft_ping.h"

void				freePing(t_ping **ping)
{
	if (*ping == NULL)
		return ;
	if ((*ping)->addr != NULL)
	{
		freeaddrinfo((*ping)->addr);
		(*ping)->addr = NULL;
	}
	if ((*ping)->sockfd > 0)
		close((*ping)->sockfd);
	ft_memdel((void **)ping);
}