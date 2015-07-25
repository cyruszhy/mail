#include "header.h"
#include "./getwanip/getwanip.h"
#include <sys/epoll.h>
#include "./epollcreat/epollcreat.h"
#include "./qingchu/qingchu.h"
#include "./zhuanfa/zhuanfa.h"
#include <sys/timerfd.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "./heap/heap.h"
#include "./daxiaoduan/daxiaoduan.h"
#include "gb2312_to_unicode.h"
#include "./getbody/getbody.h"
#include "./bianjiema/bianjiema.h"
#include "./lock/shared.h"
#include "./hash/hash.h"
#include "./zhuandizhi/zhuandizhi.h"

#define port 2099

int maxi(int a,int b)
{
	return a > b ? a:b ;
}



char wanip[20];
void collect(int sg)
{
	char buf[300];
	sprintf(buf,"iptables -t nat -D PREROUTING -p tcp --dport 25 -j DNAT --to-destination %s:%d",wanip,port);
	system(buf);
	exit (0);
}
typedef void Sigfunc(int);
#define MAXSIZE 10000
int flagsong=0;
int stepi=100;
int flagfasong;
ngx_pool_t *pool[10000];
void sigchdl(int o)
{
	pid_t pid;
	int stat;
	pid=waitpid(-1,&stat,WNOHANG);
	while(pid>0)
	{
		pid=waitpid(-1,&stat,WNOHANG);
	}
	return ;
}
void show(struct epolldata *w)
{
	puts(w->ip);
	printf("%d\n",w->fd);
	puts(w->ipp);
	printf("%d\n",w->fdd);
}
int main()
{
	int sockfd;
	int clientfd;
	int res;
	struct epoll_event ev;
	struct epoll_event events[MAXSIZE];
	int kpfd;
	int opt;
	int epollnum;
	struct duili *time=initheap();
	struct sockaddr_in client_addr;
	struct sockaddr_in sever_addr;
	if(signal(SIGTERM,collect)==SIG_ERR)
	{
		perror("signal");
		return -1;
	}
	init_hash_table();
	int j=0;
	for(;j<7445;j++){
		int tmp;	
		tmp = gb2312_to_unicode[j][1]-0xa0a0;
		int index1;
		int index2;
		index1 = tmp>>8;
		index2 = tmp&0xff;
		if(!decidebl()){
		index1 = tmp&0xff;
		index2 = tmp>>8;
		}
		gb_2_uni[index1][index2] = gb2312_to_unicode[j][0];
	}
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		exit (0);
	}
	res=getwanip(wanip);
	if(res<0)
	{
		perror("getwanip");
		exit (0);
	}
	sever_addr.sin_family = AF_INET;
	inet_pton(AF_INET,wanip,&sever_addr.sin_addr);
	sever_addr.sin_port = htons(port);
	opt=1;
	epollnum=2;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))<0)
	{
		perror("setsockopt");
		return 0;
	}
	/*if(setnonblock(sockfd)<0)
	{
		perror("setnonblock");
		exit (0);
	}*/
	res=bind(sockfd,(struct sockaddr *)&sever_addr,sizeof(struct sockaddr));
	if(res<0)
	{
		perror("bind");
		exit (0);
	}
	res=zhuandizhi(wanip,port);
	if(res<0)
	{
		perror("zhuandizhi");
		exit (0);
	}
	listen(sockfd,5);
	kpfd=epoll_create(MAXSIZE);
	ev.events=EPOLLIN;
	struct epolldata *ptr=(struct epolldata *)malloc(sizeof(struct epolldata));
	if(ptr==NULL)
	{
		perror("ev.data.ptr");
		exit (0);
	}
	ptr->fd=sockfd;
	ev.data.ptr=ptr;
	epoll_ctl(kpfd,EPOLL_CTL_ADD,sockfd,&ev);
	/*
		加入定时器结构
	*/
	struct timeval tv;
	struct timespec now;
	clock_gettime(CLOCK_REALTIME,&now);
	struct itimerspec value;
	value.it_value.tv_sec=now.tv_sec+1;
	value.it_value.tv_nsec=now.tv_nsec;
	value.it_interval.tv_sec=1;
	value.it_interval.tv_nsec=0;
	int timerfd=timerfd_create(CLOCK_REALTIME,TFD_CLOEXEC);
	timerfd_settime(timerfd,TFD_TIMER_ABSTIME,&value,NULL);
	ev.events=EPOLLIN;
	ptr=(struct epolldata *)malloc(sizeof(struct epolldata));
	if(ptr==NULL)
	{
		perror("ev.data.ptr");
		exit (0);
	}
	ptr->fd=timerfd;
	ev.data.ptr=ptr;
	epoll_ctl(kpfd,EPOLL_CTL_ADD,timerfd,&ev);
	
	
	while(1)
	{
		int nfds;
		int w;
		int im=0;
		nfds=epoll_wait(kpfd,events,epollnum,-1);
		for(w=0;w<nfds;++w)
		{
			if(events[w].data.ptr==NULL)
			{
				continue;
			}
			if(((struct epolldata *)events[w].data.ptr)->fd==sockfd)
			{
				int clientfd;
				int severfd;
				struct sockaddr_in original_dst;
				struct sockaddr_in realsockaddr;
				struct sockaddr_in s;
				int a=sizeof(struct sockaddr);
				clientfd=accept(sockfd,(struct sockaddr *)&s,&a);
				if(clientfd<0)
				{
					perror("accept");
					exit (0);
				}
				/*if(setnonblock(clientfd)<0)
				{
					perror("setnonblock");
					exit (0);
				}*/				
				if(getsockopt(clientfd,SOL_IP,80,&original_dst,&a)<0)
				{
					perror("getsockopt");
					exit (0);
				}
				realsockaddr.sin_family=AF_INET;
				realsockaddr.sin_port=original_dst.sin_port;
				realsockaddr.sin_addr.s_addr=inet_addr(inet_ntoa(original_dst.sin_addr));
				severfd=socket(AF_INET,SOCK_STREAM,0);
				if(severfd<0)
				{
					perror("socket");
					exit (0);
				}
				if(connect(severfd,(struct sockaddr *)&realsockaddr,sizeof(struct sockaddr))<0)
				{
					perror("connect");
					exit (0);
				}
				if(epollcreat(kpfd,clientfd,inet_ntoa(s.sin_addr),severfd,inet_ntoa(original_dst.sin_addr))<0)
				{
					perror("epollcreate");
					return -1;
				}
				if(append_link_node(clientfd,chuandi1)!=0)
				{
					fprintf(stderr,"%s,%d",__FILE__,__LINE__);
				}
				if(append_link_node(severfd,chuandi2)!=0)
				{
					fprintf(stderr,"%s,%d",__FILE__,__LINE__);
				}
				pool[severfd]=ngx_create_pool(8192,NULL);
				gettimeofday(&tv,NULL);
				time=insertnum(time,tv.tv_sec+4,clientfd,1);
				time=insertnum(time,tv.tv_sec+4,severfd,1);
				++epollnum;
				++epollnum;
				continue;
			}
			if(events[w].events==EPOLLIN)
			{
				if(((struct epolldata *)events[w].data.ptr)->fd==timerfd)
				{
					double ep;
					int s=read(timerfd,&ep,sizeof(double));
					genxin(time,kpfd);
				}
				else
				{
					int mailflags;
					char buf[4096]={0};
					int res;
					mailflags=0;
					res=read(((struct epolldata *)events[w].data.ptr)->fd,buf,4096);
					if(res<=0)
					{
						if(errno==EINTR)
						{
							continue;
						}
						puts("read");
							int wenjianfd;
							char as[20];
							char *prtt1;
							char *prtt2;
							int wenjianidt=0;
							if(access("/tmp/youxiang",0)!=0)
							{
								umask(0);
								if(mkdir("/tmp/youxiang",0777)!=0)
								{
									perror("mkdir");
									return -1;
								}
							}
							if(access("/tmp/youxiang/youxiangjilu",0)==0)
							{
								wenjianfd=open("/tmp/youxiang/youxiangjilu",O_RDWR|O_APPEND);
							}
							else
							{
								wenjianfd=open("/tmp/youxiang/youxiangjilu",O_CREAT|O_RDWR,0644);
								if(wenjianfd<0)
								{
									perror("open");
									return -1;
								}
							}
							struct tm *jianfeng;
							struct timeval tvsec;
							gettimeofday(&tvsec,NULL);
							time_t waitjian;
							waitjian=tvsec.tv_sec;
							jianfeng=gmtime(&waitjian);
							char bufforn[100];
							sprintf(bufforn,"time:%d%d%d%d%d%d\nfrom:%s\nto:%s\n",jianfeng->tm_year+1900,jianfeng->tm_mon+1,jianfeng->tm_mday,jianfeng->tm_hour+8,jianfeng->tm_min,jianfeng->tm_sec,((struct epolldata *)events[w].data.ptr)->from,((struct epolldata *)events[w].data.ptr)->to);
							write(wenjianfd,bufforn,strlen(bufforn));
							sprintf(bufforn,"subject:%s\n",((struct epolldata *)events[w].data.ptr)->subject);
							write(wenjianfd,bufforn,strlen(bufforn));
							struct fujian *mid=((struct epolldata *)events[w].data.ptr)->fujiann;
							while(mid!=NULL)
							{
								sprintf(bufforn,"attachment:%s\n",mid->name);
								write(wenjianfd,bufforn,strlen(bufforn));
								puts(bufforn);
								mid=mid->next;
							}
							sprintf(bufforn,"body:%s\n",((struct epolldata *)events[w].data.ptr)->body);
							write(wenjianfd,bufforn,strlen(bufforn));
							close(wenjianfd);
						link_node_ptr findmid;
						if((findmid=find_hash_node(((struct epolldata *)events[w].data.ptr)->fd))!=NULL)
						{
							deletduili(time,findmid->i);
						}
						else
						{
							fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
						}
						if((findmid=find_hash_node(((struct epolldata *)events[w].data.ptr)->fdd))!=NULL)
						{
							deletduili(time,findmid->i);
						}
						else
						{
							fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
						}
						if(delete_link_node(((struct epolldata *)events[w].data.ptr)->fd)==0)
						{
							puts("nodelete");
						}
						if(delete_link_node(((struct epolldata *)events[w].data.ptr)->fdd)==0)
						{
							puts("nonodelete");
						}
						qingchu(kpfd,events[w].data.ptr);
						puts("read");
						--epollnum;
						--epollnum;
						continue;
					}
					link_node_ptr findmidread;
					int idt=((struct epolldata *)events[w].data.ptr)->fd;
					if((findmidread=find_hash_node(idt))==NULL)
					{
						continue;
						fprintf(stderr,"%s,%d",__FILE__,__LINE__);
						exit (0);
					}
					/*printf("genxinduilireadbefore%d\n",findmidread->i);
					printf("idtread%d\n",idt);*/
					genxinduili(time,findmidread->i);
					/*if((findmidread=find_hash_node(idt))==NULL)
					{
						fprintf(stderr,"%s,%d",__FILE__,__LINE__);
						exit (0);
					}
					printf("genxinduilireadafter%d\n",findmidread->i);*/
					printf("poll%d\n",((struct epolldata *)events[w].data.ptr)->poll);
					/*
						添加测试部分
					*/
					struct epolldata *ptr;
					ptr=(struct epolldata *)events[w].data.ptr;
						if((strstr(buf,"FROM"))!=NULL)
						{
							char *prtt1;
							char *prtt2;
							int wenjianidt=0;
							while(buf[wenjianidt]!='\0')
							{
								if(buf[wenjianidt]=='<')
								{
									prtt1=&buf[wenjianidt+1];
								}
								else if(buf[wenjianidt]=='>')
								{
									prtt2=&buf[wenjianidt];
								}
								wenjianidt++;
							}
							char *fromm=((struct epolldata *)events[w].data.ptr)->from;
							memcpy(fromm,prtt1,prtt2-prtt1);
							fromm[prtt2-prtt1]='\0';
							fromm=((struct epolldata *)events[w].data.ptr)->next->from;
							memcpy(fromm,prtt1,prtt2-prtt1);
							fromm[prtt2-prtt1]='\0';
							/*pthread_mutex_t * mutexfrom = getSharedMutex("/tmp/sd");
							pthread_mutex_lock(mutexfrom);*/
							if(access("/tmp/balck",0)==0)
							{
								FILE *fpfrom=fopen("/tmp/balck","r");
								if(fpfrom==NULL)
								{
									perror("fopen");
									return -1;
								}
								char buffrom[40];
								while(fgets(buffrom,40,fpfrom)!=NULL)
								{
									int i=strlen(buffrom);
									i=i-1;
									buffrom[i]='\0';
									if(strcmp(buffrom,fromm)==0)
									{
										link_node_ptr findmid;
										if((findmid=find_hash_node(((struct epolldata *)events[w].data.ptr)->fd))!=NULL)
										{
											printf("getlenbefore%d\n",getlen(time));
											printf("%d\n",findmid->i);
											deletduili(time,findmid->i);
											printf("getlenafter%d\n",getlen(time));
										}
										else
										{
											fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
										}
										if((findmid=find_hash_node(((struct epolldata *)events[w].data.ptr)->fdd))!=NULL)
										{
											printf("getlenbefore%d\n",getlen(time));
											printf("%d\n",findmid->i);
											deletduili(time,findmid->i);
											printf("getlenafter%d\n",getlen(time));
										}
										else
										{
											fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
										}
										if(delete_link_node(((struct epolldata *)events[w].data.ptr)->fd)==0)
										{
											puts("nodelete");
										}
										if(delete_link_node(((struct epolldata *)events[w].data.ptr)->fdd)==0)
										{
											puts("nonodelete");
										}
										qingchu(kpfd,events[w].data.ptr);
										puts("readqingchu");
										--epollnum;
										--epollnum;
										/*pthread_mutex_unlock(mutexfrom);
										releaseSharedMutex("sd",(void *)mutexfrom);*/
									goto haha;
									}
								}
							}
							/*pthread_mutex_unlock(mutexfrom);
							releaseSharedMutex("sd",(void *)mutexfrom);*/
						}
						
						if(strstr(buf,"Subject")!=NULL)
						{
							puts("subject");
							char *prtt1;
							char *prtt2;
							prtt1 = strstr(buf, "Subject");
							prtt2 =strstr(prtt1, "\r\n");
							prtt1=prtt1;
							int len;
							if(prtt2 != NULL){
								len = prtt2 - prtt1;
								char tmp1[len];
								memset(tmp1,'\0',len);
								strncat(tmp1, prtt1, len);							
								if((prtt1 = strstr(tmp1, "?GB2312?B?")) != NULL){
									if((prtt2 = strstr(prtt1,"?=")) != NULL){
										puts("zhuanma");
										prtt1 += 10;
										len = prtt2 - prtt1;
										char tmp2[len];
										memset(tmp2,'\0',len);
										strncat(tmp2, prtt1, len);
										char orgstring[100];
										memset(orgstring,'\0',100);
										len = base64_decode(orgstring, tmp2, len);
										char utf8string[100];
										memset(utf8string,'\0',100);
										len = gb2312_to_utf8(orgstring, len, utf8string);
										utf8string[len]='\0';
										char *sa=((struct epolldata *)events[w].data.ptr)->subject;
										memset(sa,'\0',len);
										strcpy(sa,utf8string);
										sa=((struct epolldata *)events[w].data.ptr)->next->subject;
										memset(sa,'\0',len);
										strcpy(sa,utf8string);
									}
							}
							else{
								char *sa=((struct epolldata *)events[w].data.ptr)->subject;
								memset(sa,'\0',len);
								strcpy(sa,&tmp1[8]);
								sa[len-8]='\0';
								sa=((struct epolldata *)events[w].data.ptr)->next->subject;
								memset(sa,'\0',len);
								strcpy(sa,&tmp1[8]);
								sa[len-8]='\0';
							}
							}
						}
						if(strstr(buf,"attachment")!=NULL)
						{
							puts("adddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
							char *prtt1 = strstr(buf, "attachment");
							char *prtt2;
							if(prtt1!=NULL)
							{
								prtt1 = strstr(prtt1, "\n");
								prtt2 =strstr(prtt1, "\r\n");
								int len;
								if(prtt2 != NULL){
									puts("sdsasdacccccccccccccccccccccccccccccccccccccccccccccccccc");
									struct fujian *mid=(struct fujian *)ngx_palloc(pool[((struct epolldata *)events[w].data.ptr)->next->poll],sizeof(struct fujian));
									mid->next=NULL;
									len = prtt2 - prtt1;
									char tmp1[len];
									memset(tmp1,'\0',len);
									strncat(tmp1, prtt1, len);							
									if((prtt1 = strstr(tmp1, "?GB2312?B?")) != NULL){
										if((prtt2 = strstr(prtt1,"?=")) != NULL){
											puts("zhuanma");
											prtt1 += 10;
											len = prtt2 - prtt1;
											char tmp2[len];
											memset(tmp2,'\0',len);
											strncat(tmp2, prtt1, len);
											char orgstring[100];
											memset(orgstring,'\0',100);
											len = base64_decode(orgstring, tmp2, len);
											char utf8string[100];
											memset(utf8string,'\0',100);
											len = gb2312_to_utf8(orgstring, len, utf8string);
											utf8string[len]='\0';
											puts(utf8string);
											puts("dfssdf");
											memcpy(mid->name,utf8string,len);
											puts("dfsdsdf");
										}
									}else{
										memset(mid->name,'\0',len);
										strcpy(mid->name,&tmp1[11]);
										mid->name[len-11]='\0';
										puts(tmp1);
									}
									puts("sdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
									struct fujian *mid1=((struct epolldata *)events[w].data.ptr)->fujiann;
									if(mid1==NULL)
									{
										mid1=mid;
										((struct epolldata *)events[w].data.ptr)->next->fujiann=mid;
									}
									else
									{
										struct fujian *mid2;
										while(mid2->next!=NULL)
										{
											mid2=mid2->next;
										}
										mid2->next=mid;
									}
									puts("dfdasssssssssssssssssssssssss");
									prtt1 = strstr(prtt2, "attachment");
								}
								else
								{
									break;
								}
							}
							puts("vnvbnbnbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
						}
					if(ptr->flagssong==0&&ptr->next->flagssong==0)
					{
						char *ptra;
						if((ptra=strstr(buf,"RCPT"))!=NULL)
						{
							ptr->flagsfasong=1;
							ptr->flagssong=1;
							int wenjianfd;
							char as[20];
							char *prtt1;
							char *prtt2;
							int wenjianidt=0;
							while(buf[wenjianidt]!='\0')
							{
								if(buf[wenjianidt]=='<')
								{
									prtt1=&buf[wenjianidt+1];
								}
								else if(buf[wenjianidt]=='>')
								{
									prtt2=&buf[wenjianidt];
								}
								wenjianidt++;
							}
							char *to=((struct epolldata *)events[w].data.ptr)->to;
							memcpy(to,prtt1,prtt2-prtt1);
							to[prtt2-prtt1]='\0';
							to=((struct epolldata *)events[w].data.ptr)->next->to;
							memcpy(to,prtt1,prtt2-prtt1);
							to[prtt2-prtt1]='\0';
						}
						else if((ptra=strstr(buf,"rcpt"))!=NULL)
						{
							ptr->flagsfasong=0;
							ptr->flagssong=1;
							int wenjianfd;
							char as[20];
							char *prtt1;
							char *prtt2;
							int wenjianidt=0;
							while(buf[wenjianidt]!='\0')
							{
								if(buf[wenjianidt]=='<')
								{
									prtt1=&buf[wenjianidt+1];
								}
								else if(buf[wenjianidt]=='>')
								{
									prtt2=&buf[wenjianidt];
								}
								wenjianidt++;
							}
							char *to=((struct epolldata *)events[w].data.ptr)->to;
							memcpy(to,prtt1,prtt2-prtt1);
							to[prtt2-prtt1]='\0';
							to=((struct epolldata *)events[w].data.ptr)->next->to;
							memcpy(to,prtt1,prtt2-prtt1);
							to[prtt2-prtt1]='\0';
						}
					}
					else
					{
						char *ptra;
						ptra=strstr(buf,"250");
						if(ptra!=NULL&&im==0)
						{
							im=1;
							ptr->next->flagssong=0;
							char getsendbuf[30]="563464232@qq.com";
							char packet[40];
							if(ptr->next->flagsfasong==0)
							{
								sprintf(packet,"rcpt to: <%s>\r\n",getsendbuf);
							}
							else
							{
								sprintf(packet,"RCPT TO: <%s>\r\n",getsendbuf);
							}
							puts(packet);
							struct list *bufsize=initn(strlen(packet),((struct epolldata *)events[w].data.ptr)->next->poll);
							puts("initn1");
							memcpy(bufsize->buf,packet,strlen(packet));
							puts("initn2");
							/*bufsize->next=((struct epolldata *)events[w].data.ptr)->next->buf->next;
							((struct epolldata *)events[w].data.ptr)->next->buf->next=bufsize;*/
							showlist(((struct epolldata *)events[w].data.ptr)->next->buf);
							((struct epolldata *)events[w].data.ptr)->next->buf=insertlist(((struct epolldata *)events[w].data.ptr)->next->buf,bufsize);
							showlist(((struct epolldata *)events[w].data.ptr)->next->buf);
							puts("initn3");
							ev.events=EPOLLOUT;
							ev.data.ptr=(struct epolldata *)events[w].data.ptr;
							puts("initn4");
							epoll_ctl(kpfd,EPOLL_CTL_MOD,((struct epolldata *)events[w].data.ptr)->fd,&ev);
							goto haha;
						}
					}
						if(strstr(buf, "<html>")!= NULL){
							char *pttr1;
							char *pttr2;
							int bodylen;
							int len;
							char mail_body[4096];
							char utf8string[4096];
							pttr1=strstr(buf,"<html>");
							if((pttr2 = strstr(pttr1, "</html>")) != NULL || (pttr2 = strstr(pttr1,"</body>")) != NULL){
								pttr2 += 7 ;
								len = pttr2 - pttr1;
								puts("111");
								puts(pttr1);
								bodylen = getbody(pttr1, len, mail_body);
								puts("222");
								len = gb2312_to_utf8(mail_body, bodylen, utf8string);
								puts("333");
								((struct epolldata *)events[w].data.ptr)->body=(char *)malloc(sizeof(char )*len);
								memcpy(((struct epolldata *)events[w].data.ptr)->body,utf8string,len);
								((struct epolldata *)events[w].data.ptr)->next->body=((struct epolldata *)events[w].data.ptr)->body;
							}
						}
					struct list *bufsize=initn(res,((struct epolldata *)events[w].data.ptr)->poll);
					puts("initn11");
					memcpy(bufsize->buf,buf,res);
					puts("initn22");
					if(bufsize==NULL)
					{
						puts("cuowulist");
					}
					((struct epolldata *)events[w].data.ptr)->buf=insertlist(((struct epolldata *)events[w].data.ptr)->buf,bufsize);
					puts("initn33");
					ev.events=EPOLLOUT;
					ev.data.ptr=((struct epolldata *)events[w].data.ptr)->next;
					puts("initn44");
					epoll_ctl(kpfd,EPOLL_CTL_MOD,((struct epolldata *)events[w].data.ptr)->fdd,&ev);
				haha:if(0);
					/*zhuanfa(((struct epolldata *)events[w].data.ptr),buf);*/
				}
			}
			else if(events[w].events==EPOLLOUT)
			{
				int idt=((struct epolldata *)events[w].data.ptr)->fd;
				link_node_ptr findmidwrite;
				if((findmidwrite=find_hash_node(idt))==NULL)
				{
					continue;
					fprintf(stderr,"%s,%d",__FILE__,__LINE__);
					exit (0);
				}
				else
				{
					/*printf("genxinduiliwritebefore%d\n",findmidwrite->i);*/
					genxinduili(time,findmidwrite->i);
					/*if((findmidwrite=find_hash_node(idt))==NULL)
					{
						fprintf(stderr,"%s,%d",__FILE__,__LINE__);
						exit (0);
					}
					printf("genxinduiliwriteafter%d\n",findmidwrite->i);*/
				}
				while(((struct epolldata *)events[w].data.ptr)->next->buf->next!=NULL)
				{
					/*showlist(((struct epolldata *)events[w].data.ptr)->next->buf);*/
					struct list *bufsize=poplist(((struct epolldata *)events[w].data.ptr)->next->buf);
					/*showlist(((struct epolldata *)events[w].data.ptr)->next->buf);*/
					/*if(bufsize!=NULL)
					{
						((struct epolldata *)events[w].data.ptr)->next->buf->next=((struct epolldata *)events[w].data.ptr)->next->buf->next->next;
					}*/
					int res=write(((struct epolldata *)events[w].data.ptr)->fd,bufsize->buf,bufsize->len);
					if(res<0)
					{
						if(errno==EPIPE)
						{
							link_node_ptr findmid;
							if((findmid=find_hash_node(((struct epolldata *)events[w].data.ptr)->fd))!=NULL)
							{
								deletduili(time,findmid->i);
							}
							else
							{
								fprintf(stderr,"%s,%d\n",__FILE__,__LINE__);
							}
							if((findmid=find_hash_node(((struct epolldata *)events[w].data.ptr)->fdd))!=NULL)
							{
								deletduili(time,findmid->i);
							}
							if(delete_link_node(((struct epolldata *)events[w].data.ptr)->fd)==0)
							{
								puts("nodelete");
							}
							if(delete_link_node(((struct epolldata *)events[w].data.ptr)->fdd)==0)
							{
								puts("nonodelete");
							}
							qingchu(kpfd,events[w].data.ptr);
							--epollnum;
							--epollnum;
							break;
						}
						perror("write");
						exit (0);
					}
					ngx_pfree(pool[((struct epolldata *)events[w].data.ptr)->poll],bufsize->buf);
					ngx_pfree(pool[((struct epolldata *)events[w].data.ptr)->poll],bufsize);
				}
				ev.events=EPOLLIN;
				ev.data.ptr=events[w].data.ptr;
				epoll_ctl(kpfd,EPOLL_CTL_MOD,((struct epolldata *)events[w].data.ptr)->fd,&ev);
			}
		}
	}
	drop_hash();
	close(sockfd);
	return 0;
}
