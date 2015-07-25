#include "epollcreat.h"

struct epolldata *chuandi1;
struct epolldata *chuandi2;
int epollcreat(int kpfd,int fd,char *ip,int fdd,char *ipp)
{
	struct epoll_event ev;
	struct epolldata *ptr=(struct epolldata *)malloc(sizeof(struct epolldata));
	if(ptr==NULL)
	{
		fprintf(stderr,"%s,%d,%s",__FILE__,__LINE__,strerror(errno));
		return -1;
	}
	ptr->body=NULL;
	ptr->fujiann=NULL;
	struct epolldata *next=(struct epolldata *)malloc(sizeof(struct epolldata));
	if(next==NULL)
	{
		fprintf(stderr,"%s,%d,%s",__FILE__,__LINE__,strerror(errno));
		exit (0);
	}
	ptr->fd=fd;
	ptr->flagssong=0;
	ptr->flagsfasong=0;
	strcpy(ptr->ip,ip);
	ptr->poll=fdd;
	ptr->buf=(struct list *)malloc(sizeof(struct list));
	if(ptr->buf==NULL)
	{
		fprintf(stderr,"%s,%d,%s",__FILE__,__LINE__,strerror(errno));
		return -1;
	}
	ptr->buf->next=NULL;
	ptr->fdd=fdd;
	strcpy(ptr->ipp,ipp);
	ptr->next=next;
	ev.events=EPOLLIN;
	next->buf=(struct list *)malloc(sizeof(struct list));
	if(next->buf==NULL)
	{
		fprintf(stderr,"%s,%d,%s"__FILE__,__LINE__,strerror(errno));
		return -1;
	}
	next->buf->next=NULL;
	ev.data.ptr=ptr;
	next->fd=fdd;
	next->flagssong=0;
	next->flagsfasong=0;
	strcpy(next->ip,ipp);
	next->poll=fdd;
	strcpy(next->ipp,ip);
	next->fdd=fd;
	int res= epoll_ctl(kpfd,EPOLL_CTL_ADD,fd,&ev);
	next->next=ptr;
	next->body=NULL;
	next->fujiann=NULL;
	ev.data.ptr=next;
	chuandi1=ptr;
	chuandi2=next;
	return res||epoll_ctl(kpfd,EPOLL_CTL_ADD,fdd,&ev);
}


