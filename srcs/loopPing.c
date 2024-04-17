#include "../incs/ft_ping.h"

uint16_t			checksum(void *addr, int size) {
	uint16_t	*buff;
	uint32_t	sum;

	buff = (uint16_t *)addr;
	for (sum = 0; size > 1; size -= 2)
		sum += *buff++;
	if (size == 1)
		sum += *(uint8_t*)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return (~sum);
}

bool				initIp(
	struct iphdr *ip,
	size_t package_size,
	struct sockaddr_in *source_addr,
	struct sockaddr_in *dest_addr
)
{
	if (ip == NULL || source_addr == NULL || dest_addr == NULL)
		return false;
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = package_size;
	ip->id = htons(getpid());
	ip->frag_off = 0;
	ip->ttl = 64;
	ip->protocol = IPPROTO_ICMP;
	ip->check = 0;
	ip->saddr = source_addr->sin_addr.s_addr;
	ip->daddr = dest_addr->sin_addr.s_addr;
	return true;
}

bool				initIcmpHeader(struct icmphdr *icmphdr, uint16_t sequence)
{
	if (icmphdr == NULL)
		return false;
	icmphdr->type = ICMP_ECHO;
	icmphdr->code = 0;
	icmphdr->checksum = 0;
	icmphdr->un.echo.id = getpid();
	icmphdr->un.echo.sequence = sequence;
	return true;
}

bool				initData(char *data, size_t size)
{
	if (data == NULL)
		return false;
	if (size > 0)
		ft_memset(data, rand() % 255, size);
	return true;
}

char				*initPackage(char *package, const size_t package_size,
		t_ping *ping, const u_int16_t sequence)
{
	struct iphdr	*ip;
	struct icmphdr	*icmphdr;
	char			*data;

	if (package == NULL || ping == NULL)
		return NULL;
	ip = (struct iphdr *)package;
	icmphdr = (struct icmphdr *)(package + sizeof(struct iphdr));
	data = (char *)(package + sizeof(struct iphdr) + sizeof(struct icmphdr));
	initIp(ip, package_size, &ping->source_addr, &ping->dest_addr);
	initIcmpHeader(icmphdr, sequence);
	initData(data, ping->size);
	icmphdr->checksum = checksum(icmphdr, sizeof(struct icmphdr) + ping->size);
	ip->check = checksum(ip, sizeof(struct iphdr));
	return package;
}

bool				openSocket(t_ping *ping)
{
	int				on;
	struct timeval	timeout;

	if (ping == NULL)
		return false;
	on = 1;
	timeout.tv_sec = PING_ROUTE_TRIPE_TIME * 2;
	timeout.tv_usec = 0;
	if((ping->sockfd = socket(ping->addrFamily, SOCK_RAW, IPPROTO_ICMP)) < 0)
		perror("socket error");
	else if (setsockopt(ping->sockfd, IPPROTO_IP,	IP_HDRINCL, &on, sizeof(on)) < 0)
		perror("socket option 1 error");
	else if (setsockopt(ping->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)))
		perror("socket option 2 error");
	return true;
}

int					sendPackageRequest(char *package, const size_t package_size, t_ping *ping)
{
	int				ret;

	ret = sendto(ping->sockfd, package, package_size, 0,
			(struct sockaddr *)&ping->dest_addr, sizeof(struct sockaddr));
	if (ret < 0)
		perror("sendto Error");
	return ret;
}

int					readPackageResponse(char *package, const size_t package_size, t_ping *ping)
{
	int				ret;
	size_t			lenAddr;

	lenAddr = 0;
	ret = recvfrom(ping->sockfd, package, package_size, 0,
			(struct sockaddr*)&ping->source_addr, (socklen_t *)&lenAddr);
	if (ret < 0)
		perror("recvfrom Error");
}

void				loopBody(char *package, const size_t package_size, t_ping *ping, u_int16_t sequence)
{
	struct timeval	start;
	struct timeval	stop;
	int				retRead;
	struct iphdr	*ip;
	struct icmphdr	*icmphdr;
	char			*data;

	ip = (struct iphdr *)package;
	icmphdr = (struct icmphdr *)(package + sizeof(struct iphdr));
	data = (char *)(package + sizeof(struct iphdr) + sizeof(struct icmphdr));
	initPackage(package, package_size, ping, sequence);
	if (gettimeofday(&start, NULL) < 0)
		perror("gettimeofday Error 1");
	if (sendPackageRequest(package, package_size, ping) > 0)
		retRead = readPackageResponse(package, package_size, ping);
	if (gettimeofday(&stop, NULL) < 0)
		perror("gettimeofday Error 2");
	if (retRead > 0 && icmphdr->type == ICMP_ECHOREPLY && icmphdr->code == 0) {
		int microseconds = (stop.tv_sec - start.tv_sec) * 1000000 + ((int)stop.tv_usec - (int)start.tv_usec);
		printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", package_size - sizeof(struct iphdr), inet_ntoa(ping->dest_addr.sin_addr), icmphdr->un.echo.sequence, ip->ttl, microseconds / 1000.0);
	} else if (retRead > 0) {
		printf("%lu bytes from %s: type=%d, code=%d\n", package_size - sizeof(struct iphdr), inet_ntoa(ping->dest_addr.sin_addr), icmphdr->type, icmphdr->code);
	} else {
		printf("Not defined");
	}
}


void				loopPing(t_ping *ping)
{
	char			*package;
	size_t			package_size;
	struct timeval	start;
	struct timeval	stop;
	long			i;

	
	package_size = sizeof(struct iphdr) + sizeof(struct icmphdr) + ping->size;
	i = 0;
	openSocket(ping);
	if ((package = ft_calloc(1, package_size)) == NULL){
		perror("malloc error");
	}
	while (i < ping->count && g_interrupt == false)
	{
		loopBody(package, package_size, ping, (u_int16_t)++i);
		sleep(1);
	}
	if (package != NULL)
		ft_memdel((void **)(&package));
	return ;
}