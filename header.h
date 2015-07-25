#ifndef HEAD
#define HEAD 

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <errno.h>
#include "./noblock/noblock.h"
#include "./list/list.h"
#include <net/if.h>
#include <sys/types.h>
#include "./neicunchi/neicunchi.h"
extern ngx_pool_t *pool[10000];
struct fujian
{
	char name[100];
	struct fujian *next;
};
struct epolldata
{
	char ip[20];
	char ipp[20];
	int fd;
	int fdd;
	int flagsfasong;
	int flagssong;
	char from[20];
	char to[20];
	char subject[100];
	char *body;
	struct fujian *fujiann;
	struct epolldata *next;
	int poll;
	struct list *buf;
};
#endif

