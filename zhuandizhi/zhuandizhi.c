#include "../header.h"
#include "zhuandizhi.h"

int zhuandizhi(char *ipaddr,int port)
{
	char buf[300];
	sprintf(buf,"iptables -t nat -I PREROUTING -p tcp --dport 25 -j DNAT --to-destination %s:%d",ipaddr,port);
	puts(buf);
	system(buf);
	return 0;
}
