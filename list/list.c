#include "list.h"
#include "../header.h"

struct list *initlist(int n)
{
	if(pool[n]==NULL)
	{
		perror("fdf");
		exit (0);
	}
	struct list *w=(struct list *)ngx_palloc(pool[n],sizeof(struct list));
	puts("1");
	if(w==NULL)
	{
		perror("ngx_palloc");
		exit (0);
	}
	w->len=0;
	w->buf=NULL;
	w->next=NULL;
	puts("2");
	return w;
}

struct list *initn(int n,int a)
{
	struct list *w;
	w=initlist(a);
	w->len=n;
	puts("3");
	w->buf=(char *)ngx_palloc(pool[a],n*sizeof(char));
	puts("4");
	w->next=NULL;
	return w;	
}

struct list *insertfront(struct list *w,struct list *b)
{
	w->len=w->len+b->len;
	b->next=w->next;
	w->next=b;
	return w;
}

struct list *insertlist(struct list *w,struct list *b)
{
	struct list *q=w;
	w->len=w->len;
	puts("wlen");
	w->len=w->len+b->len;
	printf("%d\n",b->len);
	puts("blen");
	if(q==NULL)
	{
		puts("kongmail");
	}
	for(;q->next!=NULL;)
	{
		puts("1");
		q=q->next;
		puts("2");
	}
	puts("qnext");
	q->next=b;
	puts("bnext");
	return w;		
}

struct list *poplist(struct list *w)
{
	if(w->len!=0)
	{
		struct list *b=w->next;
		w->next=b->next;
		w->len=w->len-b->len;
		b->next=NULL;
		return b;
	}
	return NULL;
}

void showlist(struct list *w)
{
	struct list *q=w->next;
	printf("totoal len%d\n",w->len);
	while(q!=NULL)
	{
		printf("len%d",q->len);
		puts(q->buf);
		q=q->next;
	}
}

void dellist(struct list *w)
{
	struct list *q=w;
	q=q->next;
	struct list *s;
	while(q!=NULL)
	{
		s=q;
		q=q->next;
		free(s);
	}
}