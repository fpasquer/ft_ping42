#include "../incs/ft_ping.h"

int					parseCount(t_ping **ping, int i, char **argv)
{
	long			count;

	if (ping == NULL || *ping == NULL)
		return (i);
	if (ft_isnumber(argv[i + 1]) == 0)
		return (parseArgsErrorsInvalidArguments(ping, i + 1, argv));
	count = ft_atol(argv[i + 1]);
	if (count < PING_MIN_COUNT || count > PING_MAX_COUNT)
		return (parseArgsErrorsInvalidRange(
			ping, i + 1, argv, PING_MIN_COUNT, PING_MAX_COUNT
		));
	(*ping)->count = count;
	return (i + 1);
}

int					parseSize(t_ping **ping, int i, char **argv)
{
	int				size;

	if (ping == NULL || *ping == NULL)
		return (i);
	if (ft_isnumber(argv[i + 1]) == 0)
		return (parseArgsErrorsInvalidArguments(ping, i + 1, argv));
	size = ft_atoi(argv[i + 1]);
	if (size < PING_MIN_SIZE || size > PING_MAX_SIZE)
		return (parseArgsErrorsInvalidRange(
			ping, i + 1, argv, PING_MIN_SIZE, PING_MAX_SIZE
		));
	(*ping)->size = size;
	return (i + 1);
}

int					parseVerbose(t_ping **ping, int i, char **argv)
{
	if (ping == NULL || *ping == NULL || argv == NULL)
		return (i);
	(*ping)->verbose = (*ping)->verbose == false;
	return (i);
}

int					parseHelp(t_ping **ping, int i, char **argv)
{
	if (ping == NULL || *ping == NULL || argv == NULL)
		return (i);
	(*ping)->help = (*ping)->help == false;
	return (i);
}

int					parseQuiet(t_ping **ping, int i, char **argv)
{
	if (ping == NULL || *ping == NULL || argv == NULL)
		return (i);
	(*ping)->quiet = (*ping)->quiet == false;
	return (i);
}

int					parseIpv4(t_ping **ping, int i, char **argv)
{
	if (ping == NULL || *ping == NULL || argv == NULL)
		return (i);
	(*ping)->addrFamily = AF_INET;
	return (i);
}

int					parseIpv6(t_ping **ping, int i, char **argv)
{
	if (ping == NULL || *ping == NULL || argv == NULL)
		return (i);
	(*ping)->addrFamily = AF_INET6;
	return (i);
}