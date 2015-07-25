#include "heap.h"
#include "../hash/hash.h"
#include "../qingchu/qingchu.h"


static int heaplength=0;
void Littlesort(struct duili *a,int len)
{
	int i;
	int j;
	struct duili t;
	for(i=len/2-1;i>=0;i--)
	{
		while(2*i+1<len)
		{
			j=2*i+1;
			if((j+1)<len)
			{
				if(a[j].sec>a[j+1].sec)
				{
					j++;
				}
			}
			if(a[i].sec>a[j].sec)
			{
				int mid1=a[i].fd;
				time_t mid2=a[i].sec;
				a[i].fd=a[j].fd;
				a[i].sec=a[j].sec;
				a[j].fd=mid1;
				a[j].sec=mid2;
				link_node_ptr findmid;
				link_node_ptr findmid1; 
				if((findmid=(find_hash_node(a[i].fd)))!=NULL)
				{
					if(a[i].fd!=findmid->fd)
					{
						fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
						exit (0);
					}
					findmid->i=i;
				}
				else
				{
					fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
					exit (0);
				}
				if((findmid1=(find_hash_node(a[j].fd)))!=NULL)
				{
					if(a[j].fd!=findmid1->fd)
					{
						fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
						exit (0);
					}
					findmid1->i=j;
				}
				else
				{
					fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
					exit (0);
				}
				i=j;
			} 
			else
			{
				break;
			}
		}
	}
}
void shijianchuli(struct duili *w)
{
	w->sec=0;
	w->fd=-1;
}
void Bigsort(struct duili *a,int len)
{
	int i;
	int j;
	struct duili t;
	for(i=len/2-1;i>=0;i--)
	{
		while(2*i+1<len)
		{
			j=2*i+1;
			if((j+1)<len)
			{
				if(a[j].sec<a[j+1].sec)
				{
					j++;
				}
			}
			if(a[j].sec<a[j+1].sec)
			{
				t=a[j];
				a[j]=a[i];
				a[i]=t;
				i=j;
			}
			else
			{
				break;
			}
		}
	}
}
int getlen(struct duili *a)
{
	int i=0;
	while(a[i].sec!=0)
	{
		i++;
		if(i==(SORTLEN+heaplength))
		{
			puts("getlen");
			return i;
		}
	}
	return i;
}
void genxinduili(struct duili *a,int match)
{
	int len=getlen(a);
	if(match<len)
	{
		/*
			统归增加定时间隔
		*/	
		struct timeval tv;
		gettimeofday(&tv,NULL);
		if(a[match].sec==0)
		{
			fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
			exit (0);
		}
		a[match].sec=tv.tv_sec+4;
		Littlesort(a,len);
	}
	else
	{
		fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
	}
}
void deletduili(struct duili *a,int match)
{
	int len=getlen(a);	
	if(match<len)
	{
		int fd=a[len-1].fd;
		time_t sec=a[len-1].sec;
		a[len-1].fd=a[match].fd;
		a[len-1].sec=a[match].sec;
		a[match].fd=fd;
		a[match].sec=sec;
		link_node_ptr findmidd;
		if((findmidd=(find_hash_node(a[match].fd)))!=NULL)
		{
			if(a[match].fd!=findmidd->fd)
			{
				fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
				exit (0);
			}
			findmidd->i=match;
		}
		else
		{
			fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
			exit (0);
		}
		a[len-1].shijianchuli(&a[len-1]);
		len=getlen(a);
		if(len==1)
		{
			link_node_ptr findmid;
			if((findmid=(find_hash_node(a[0].fd)))!=NULL)
			{
				if(a[0].fd!=findmid->fd)
				{
					fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
					exit (0);
				}
				findmid->i=0;
			}
			else
			{
				fprintf(stderr,"%s,%d\n"__FILE__,__LINE__);
				exit (0);
			}
		}
		else
		{
			Littlesort(a,len);
		}
	}
}
struct duili * insertnum(struct duili *a,time_t num,int fd,int flags)
{
	int len=getlen(a);
	
	if(len==(SORTLEN+heaplength))
	{
		int length=heaplength+SORTLEN;
		int w=0;
		int i=length;
		heaplength=heaplength+20;
		struct duili *b=(struct duili *)malloc(sizeof(struct duili)*(SORTLEN+heaplength));
		for(;w<length;w++)
		{
			b[w].sec=a[w].sec;
			b[w].fd=a[w].fd;
			b[w].shijianchuli=a[w].shijianchuli;
			b[w].next=NULL;
		}
		free(a);
		a=b;
		for(;i<(heaplength+SORTLEN);i++)
		{
			b[i].sec=0;b[i].fd=-1;
			b[i].shijianchuli=shijianchuli;
			b[i].next=NULL;
		}
		b[len].fd=fd;
		b[len].sec=num;
		link_node_ptr findmid;
		if((findmid=find_hash_node(fd))==NULL)
		{
			fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
			exit (0);
		}
		else
		{
			findmid->i=len;
		}
		if(flags==0)
		{
			Bigsort(b,len+1);
		}
		else if(flags==1)
		{
			Littlesort(b,len+1);
		}
		else
		{
			exit (0);
		}
		return b;
	}
	else
	{
		a[len].fd=fd;
		a[len].sec=num;
		link_node_ptr findmid;
		if((findmid=find_hash_node(fd))==NULL)
		{
			fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
			exit (0);
		}
		else
		{
			findmid->i=len;
		}
		if(flags==0)
		{
			Bigsort(a,len+1);
		}
		else if(flags==1)
		{
			Littlesort(a,len+1);
		}
		else
		{
			exit (0);
		}
		return a;
	}
}
void genxin(struct duili *a,int kpfd)
{
	int len=getlen(a);
	struct timeval tv;
	gettimeofday(&tv,NULL);
	while(len!=0&&tv.tv_sec>a[0].sec)
	{
		puts("3");
		puts("4");
		struct duili te=a[len-1];
		link_node_ptr findmid;
		link_node_ptr findmid1;
		a[len-1]=a[0];
		a[0]=te;
		if((findmid=find_hash_node(a[len-1].fd))==NULL)
		{
			fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
			heapshow(a);
			a[len-1].fd=-1;
			a[len-1].sec=0;
			len=getlen(a);
			if(len!=0)
			{
				Littlesort(a,len);
			}
			continue;
			/*exit (0);*/
		}
		deletduili(a,findmid->i);
		heapshow(a);
		if((findmid1=find_hash_node(findmid->mid->fdd))==NULL)
		{
			fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
			continue;
			/*exit (0);*/
		}
		deletduili(a,findmid1->i);
		heapshow(a);
		qingchu(kpfd,findmid->mid);
		if(delete_link_node(findmid->fd)==0)
		{
			puts("nodelete");
		}
		if(delete_link_node(findmid1->fd)==0)
		{
			puts("nonodelete");
		}
		len=getlen(a);
		if(len!=0)
		{
			Littlesort(a,len);
		}
	}
}
struct duili *initheap()
{
	int i=0;
	struct duili *a=(struct duili *)malloc(sizeof(struct duili )*SORTLEN);
	for(;i<(SORTLEN+heaplength);i++)
	{
		a[i].sec=0;a[i].fd=-1;
		a[i].shijianchuli=shijianchuli;
		a[i].next=NULL;
	}
	return a;
}
void heapshow(struct duili *a)
{
	int i=0;
	for(;i<(SORTLEN+heaplength);i++)
	{
		printf("%d\n",a[i].fd);
		printf("%d\n",a[i].sec);
	}
}




















