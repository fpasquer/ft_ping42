#include "../incs/ft_ping.h"

void				usage(char const *name_bin)
{
	fprintf(stderr, "%s -vh [-c count] [-s size] <HOST>\n", name_bin);
}