#include "../incs/ft_ping.h"

bool				g_interrupt;

int					main(int argc, char **argv)
{
	t_ping			*ping;
	int				signalReturn;

	if (argc < 2)
	{
		usage(argv[0]);
		return (EXIT_FAILURE);
	}
	ping = parseArgs(argc, argv);
	if (ping == NULL)
		return (EXIT_FAILURE);
	if (ping->help == true)
		usage(argv[0]);
	g_interrupt = false;
	if ((signalReturn = initSignalHandler()) != 0)
		fprintf(stderr, "Error: signal handler: '%d'\n", signalReturn);
	else if (ping->addr != NULL)
		loopPing(ping);
	freePing(&ping);
	return (EXIT_SUCCESS);
}