#include "noblock.h"



int setnonblock(int fd)
{
	if(fcntl(fd,F_SETFL,fcntl(fd,F_GETFL,0)|O_NONBLOCK)<0)
	{
		perror("fcntl");
		return -1;
	}
	return 0;
}
