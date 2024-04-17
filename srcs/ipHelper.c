#include "../incs/ft_ping.h"

int					buildDestIpFromHost(char const *host, t_ping **ping,
		char *appName)
{
	int				ret;
	struct addrinfo hints;

	if (ping == NULL || *ping == NULL)
		return (INT_MIN);
	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = (*ping)->addrFamily;
	if ((ret = getaddrinfo(host, NULL, &hints, &(*ping)->addr)) == EAI_NONAME)
		fprintf(stderr, "%s: %s: Name or service not known\n", appName, host);
	else if (ret == EAI_AGAIN)
		fprintf(stderr, "%s: %s: Temporary failure in name resolution\n",
				appName, host);
	else if (ret == EAI_FAIL)
		fprintf(stderr, "%s: %s: Non-recoverable failure in name resolution\n",
				appName, host);
	else if (ret != 0)
		fprintf(stderr, "%s: %s: Unknown error\n", appName, host);
	else if (ret == 0 && (*ping)->addr->ai_family == AF_INET)
	{
		inet_ntop(AF_INET, &((struct sockaddr_in *)(*ping)
				->addr->ai_addr)->sin_addr, (*ping)->dest_ip, INET6_ADDRSTRLEN);
		(*ping)->dest_addr.sin_addr.s_addr = inet_addr((*ping)->dest_ip);
		(*ping)->dest_addr.sin_family = AF_INET;
	}
	else if (ret == 0 && (*ping)->addr->ai_family == AF_INET6)
	{
		inet_ntop(AF_INET6, &((struct sockaddr_in6 *)(*ping)
				->addr->ai_addr)->sin6_addr, (*ping)->dest_ip, INET6_ADDRSTRLEN);
		fprintf(stderr, "NOT defined %d %s", __LINE__, __FILE__);

	}
	else
		fprintf(stderr, "%s family not implemented", (*ping)->addr->ai_family);
	return (ret);
}

bool				getMyIp(t_ping *ping)
{
	struct ifaddrs	*addrs;
	struct ifaddrs	*tmp;
	struct sockaddr_in
					*pAddr;

	if (ping == NULL || getifaddrs(&addrs) != 0)
		return false;
	tmp = addrs;
	while (tmp) 
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == ping->addrFamily &&
			(
				ft_strcmp(NET_INTERFACE_1, tmp->ifa_name) == 0 ||
				ft_strcmp(NET_INTERFACE_2, tmp->ifa_name) == 0
			)
		)
		{
			pAddr = (struct sockaddr_in *)tmp->ifa_addr;
			ft_strlcpy(ping->source_ip, inet_ntoa(pAddr->sin_addr),
					INET6_ADDRSTRLEN + 1);
			ping->source_addr.sin_addr.s_addr = inet_addr(ping->source_ip);
			ping->source_addr.sin_family = ping->addrFamily;
		}
		tmp = tmp->ifa_next;
	}
	freeifaddrs(addrs);
	return true;
}