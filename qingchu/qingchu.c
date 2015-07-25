#include "qingchu.h"


int qingchu(int kpfd,struct epolldata *events)
{
	int res= epoll_ctl(kpfd,EPOLL_CTL_DEL,events->fd,NULL);
	if(res!=0)
	{
		perror("epoll_ctlfd");
	}
	res=epoll_ctl(kpfd,EPOLL_CTL_DEL,events->fdd,NULL);
	if(res!=0)
	{
		perror("epoll_ctlfdd");
	}
	close(events->fd);
	close(events->fdd);
	puts("chuanqian");
	/*if(events->fujiann!=NULL)
	{
		struct fujian *mid=events->fujiann;
		struct fujian *mid1;
		while(mid!=NULL)
		{
			mid1=mid;
			mid=mid->next;
			free(mid1);
		}
	}*/
	puts("chuhou");
	if(events->body!=NULL)
	{
		free(events->body);
		events->body=NULL;
		events->next->body=NULL;
	}
	events->fujiann=NULL;
	if(events->buf!=NULL)
	{
		free(events->buf);
		events->buf=NULL;
	}
	if(events->next->buf!=NULL)
	{
		free(events->next->buf);
		events->next->buf=NULL;
	}
	events->next->fujiann=NULL;
	ngx_destroy_pool(pool[events->poll]);
	pool[events->poll]=NULL;
	/*struct list *qclear=events->buf->next;
	while(qclear!=NULL)
	{
		struct list *qclean=qclear;
		qclear=qclear->next;
		free(qclean->buf);
		free(qclean);
	}
	puts("change in 530bufbegin");
	free(events->next->buf);
	puts("change in 530bufend");
	free(events->buf);*/
	free(events->next);
	free(events);
	events->next=NULL;
	events=NULL;
}
