#include "../incs/ft_ping.h"

double				pingStatsTimeDiffInMiliseconds(t_ping_stats *ping_stats)
{
	if (ping_stats == NULL)
		return -1.0;
	return (timeDiffInMiliseconds(&ping_stats->start, &ping_stats->stop));
}

double					timeDiffInMiliseconds(struct timeval *start,
		struct timeval *stop)
{
	int				microseconds;

	if (start == NULL || stop == NULL)
		return -1.0;
	microseconds = (stop->tv_sec - start->tv_sec) * 1000000 +
			((int)stop->tv_usec - (int)start->tv_usec);
	return (microseconds / 1000.0);
}

double				pingStatsPercentage(t_ping_stats *ping_stats)
{
	if (ping_stats == NULL)
		return -1.0;
	return ((ping_stats->received * 100.0 / ping_stats->i) - 100.0) * -1.0;
}

bool				addNewRecivedPackage(t_ping_stats *ping_stats)
{
	double			milliseconds;

	if (ping_stats == NULL)
		return false;
	milliseconds = timeDiffInMiliseconds(&ping_stats->start_body,
			&ping_stats->stop_body);
	ping_stats->avg_milliseconds += milliseconds;
	if (milliseconds < ping_stats->min_milliseconds)
		ping_stats->min_milliseconds = milliseconds;
	else if (milliseconds > ping_stats->max_milliseconds)
		ping_stats->max_milliseconds = milliseconds;
	ping_stats->mdev_miliseconds += milliseconds * milliseconds;
	ping_stats->received++;
	return true;
}