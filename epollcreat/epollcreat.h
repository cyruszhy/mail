#ifndef EPOLLCREAT
#define EPOLLCREAT 1


#include <sys/types.h>
#include "../header.h"
#include <sys/epoll.h>



struct epolldata *chuandi1;
struct epolldata *chuandi2;

int epollcreate(int,int,char *,int,char *);
void Epollcreate(int,int,char *,int,char *);

#endif
