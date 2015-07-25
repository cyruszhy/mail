#ifndef LIST
#define LIST 1


#include <stdlib.h>
#include <stdio.h>

struct list
{
	int len;
	char *buf;
	struct list *next;	
};

struct list *initlist(int n);
struct list *initn(int n,int a);
struct list *insertlist(struct list *w,struct list *b);
struct list *insertfront(struct list *w,struct list *b);
struct list *poplist(struct list *w);
void showlist(struct list *w);
void dellist(struct list *w);

#endif
