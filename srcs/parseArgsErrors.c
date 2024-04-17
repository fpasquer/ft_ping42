#include "../incs/ft_ping.h"

int					parseArgsErrorsInvalidArguments(
		t_ping **ping, int i, char **argv)
{
	fprintf(stderr, "%s: invalid argument: '%s'\n", argv[0], argv[i]);
	if (*ping != NULL && ping != NULL)
		freePing(ping);
	return (-2);
}

int					parseArgsErrorsInvalidRange(
		t_ping **ping, int i, char **argv, long min, long max)
{
	fprintf(stderr, 
		"%s: invalid argument: '%s': out of range: %ld <= value <= %ld\n", 
		argv[0], 
		argv[i],
		min,
		max
	);
	if (*ping != NULL && ping != NULL)
		freePing(ping);
	return (-2);
}

int					parseArgsErrorsNoHost(t_ping **ping, char **argv)
{
	fprintf(stderr, "%s: usage error: Destination address required\n", argv[0]);
	if (*ping != NULL && ping != NULL)
		freePing(ping);
	return (-2);
}