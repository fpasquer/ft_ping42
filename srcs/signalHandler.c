#include "../incs/ft_ping.h"

int					initSignalHandler(void)
{
	if (signal(SIGINT, signalHandlerInterrupt) == SIG_ERR)
		return -1;
	else if (signal(SIGQUIT, signalHandlerQuit) == SIG_ERR)
		return -2;
	else
		return 0;
}

void				signalHandlerInterrupt(int signal)
{
	(void)signal;
	g_interrupt = true;
	exit(EXIT_SUCCESS);
}

void				signalHandlerQuit(int signal)
{
	(void)signal;
	printf("Quit\n");
}