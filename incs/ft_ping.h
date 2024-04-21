#ifndef FT_PING
# define FT_PING

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <errno.h>
# include <ifaddrs.h>
# include <sys/time.h>
# include <math.h>
# include "../libft/libft.h"

# define __USE_GNU

# define PING_DEFAULT_COUNT		LONG_MAX
# define PING_MIN_COUNT			1
# define PING_MAX_COUNT			LONG_MAX
# define PING_DEFAULT_SIZE		56
# define PING_MIN_SIZE			0
# define PING_MAX_SIZE			INT_MAX
# define PING_ROUTE_TRIPE_TIME	5
# define NET_INTERFACE_1		"eth0@if6"
# define NET_INTERFACE_2		"enp0s3"

typedef struct		s_ping_stats
{
	struct timeval	start;
	struct timeval	stop;
	struct timeval	start_body;
	struct timeval	stop_body;
	long			i;
	long			received;
	double			min_milliseconds;
	double			max_milliseconds;
	double			avg_milliseconds;
	double			mdev_miliseconds;
}					t_ping_stats;

typedef struct		s_ping
{
	long			count;
	int				size;
	bool			verbose;
	bool			help;
	bool			quiet;
	int				addrFamily;
	char			*host;
	char			source_ip[INET6_ADDRSTRLEN + 1];
	char			dest_ip[INET6_ADDRSTRLEN + 1];
	struct addrinfo	*addr;
	struct sockaddr_in
					source_addr;
	struct sockaddr_in
					dest_addr;
	int				sockfd;
}					t_ping;

typedef struct		s_ping_option
{
	char			*name;
	int				(*f)(t_ping **ping, int i, char **argv);
}					t_ping_option;

extern bool			g_interrupt;

void				usage(char const *name_bin);
t_ping				*parseArgs(int argc, char **argv);
void				freePing(t_ping **ping);
int					parseArgsErrorsInvalidArguments(
		t_ping **ping, int i, char **argv);
int					parseArgsErrorsInvalidRange(
		t_ping **ping, int i, char **argv, long min, long max);
int					parseArgsErrorsNoHost(t_ping **ping, char **argv);
int					parseCount(t_ping **ping, int i, char **argv);
int					parseSize(t_ping **ping, int i, char **argv);
int					parseVerbose(t_ping **ping, int i, char **argv);
int					parseHelp(t_ping **ping, int i, char **argv);
int					parseQuiet(t_ping **ping, int i, char **argv);
int					parseIpv4(t_ping **ping, int i, char **argv);
int					parseIpv6(t_ping **ping, int i, char **argv);
void				showPing(t_ping *ping);
int					buildDestIpFromHost(char const *host, t_ping **ping, char *appName);
bool				getMyIp(t_ping *ping);

int					initSignalHandler(void);
void				signalHandlerInterrupt(int signal);
void				signalHandlerQuit(int signal);

void				loopPing(t_ping *ping);

double				pingStatsTimeDiffInMiliseconds(t_ping_stats *ping_stats);
double				timeDiffInMiliseconds(struct timeval *start,
		struct timeval *stop);
double				pingStatsPercentage(t_ping_stats *ping_stats);
bool				addNewRecivedPackage(t_ping_stats *ping_stats);

#endif