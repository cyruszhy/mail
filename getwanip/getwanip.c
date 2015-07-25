#include "../header.h"
#include "getwanip.h"

int getwanip(char *wanip)
{
	struct sockaddr_in sin;
	struct ifreq ifr;
	char eth_name[16];
	char ip[16];
	int sockfd;
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		perror("socket");
		exit (0);
	}
	strcpy(eth_name,"eth0.2");
	strcpy(ifr.ifr_name,eth_name);
	if(ioctl(sockfd,SIOCGIFADDR,&ifr)<0)
	{
		fprintf(stderr,"ioctl error:%s",strerror(errno));
		exit (1);
	}
	memcpy(&sin,&ifr.ifr_addr,sizeof(sin));
	sprintf(wanip,"%s",inet_ntoa(sin.sin_addr));
	return 0;
}

