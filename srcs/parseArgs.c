#include "../incs/ft_ping.h"

t_ping				*initPing(int argc, char **argv)
{
	t_ping			*ping;

	if ((ping = (t_ping *)ft_calloc(1, sizeof(t_ping))) == NULL)
		return (NULL);
	ping->count = PING_DEFAULT_COUNT;
	ping->size = PING_DEFAULT_SIZE;
	ping->verbose = false;
	ping->help = false;
	ping->quiet = false;
	ping->addrFamily = AF_UNSPEC;
	ping->addr = NULL;
	ping->host = argv[argc - 1];
	return (ping);
}

int					loopThroughOptions(t_ping_option *options, t_ping **ping,
		int i, char **argv)
{
	int				j;
	bool			found;

	j = 0;
	found = false;
	while (options[j].name != NULL)
	{
		if (ft_strcmp(options[j].name, argv[i]) == 0)
		{
			i = options[j].f(ping, i, argv);
			found = true;
			break;
		}
		j++;
	}
	return (found == true ? i : parseArgsErrorsInvalidArguments(ping, i, argv));
}

t_ping				*parseArgs(int argc, char **argv)
{
	int				i;
	t_ping			*ping;
	t_ping_option	options[] = {
		{"-c", parseCount},
		{"-s", parseSize},
		{"-v", parseVerbose},
		{"-h", parseHelp},
		{"-q", parseQuiet},
		{"-4", parseIpv4},
		{"-6", parseIpv6},
		{NULL, NULL}
	};

	if ((ping = initPing(argc, argv)) == NULL)
		return (NULL);
	i = 1;
	while (i > 0 && i < argc - 1)
		i = loopThroughOptions(options, &ping, i, argv) + 1;
	if (i != argc - 1 && ping != NULL)
		parseArgsErrorsNoHost(&ping, argv);
	else if (ping != NULL && ping->addr == NULL)
		buildDestIpFromHost(argv[argc - 1], &ping, argv[0]);
	getMyIp(ping);
	return (ping);
}

void				showPing(t_ping *ping)
{
	struct addrinfo *addr;
	char			buffer[INET6_ADDRSTRLEN + 1];

	if (ping == NULL || ping->addr == NULL)
		return ;
	addr = ping->addr;
	printf("count   : %ld\n", ping->count);
	printf("size    : %d\n", ping->size);
	if (ping->addrFamily == AF_UNSPEC)
		printf("family  : IPv4 or IPv6\n");
	else if (ping->addrFamily == AF_INET)
		printf("family  : IPv4\n");
	else if (ping->addrFamily == AF_INET6)
		printf("family  : IPv6\n");
	printf("verbose : %s\n", ping->verbose == true ? "true" : "false");
	printf("help    : %s\n", ping->help == true ? "true" : "false");
	printf("quiet   : %s\n", ping->quiet == true ? "true" : "false");
	while (addr != NULL)
	{
		if (addr->ai_family == AF_INET)
			printf("addr  = %s\n", inet_ntoa(((struct sockaddr_in *)addr->ai_addr)->sin_addr));
		else if (addr->ai_family == AF_INET6)
			printf("addr6 = %s\n", inet_ntop(addr->ai_family, &((struct sockaddr_in6 *)addr->ai_addr)->sin6_addr, buffer, INET6_ADDRSTRLEN + 1));
		addr = addr->ai_next;
	}
}