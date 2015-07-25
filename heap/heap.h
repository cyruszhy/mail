#ifndef HEAPFUNCTION
#define HEAPFUNCTION
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#define SORTLEN 5
struct duili
{
	int fd;
	time_t sec;
	struct duili *next;
	void (*shijianchuli)(struct duili *);
};
void shijianchuli(struct duili *);
struct duili *initheap();
void Littlesort(struct duili *,int);
void Bigsort(struct duili *,int);
int getlen(struct duili *);
struct duili * insertnum(struct duili *,time_t,int,int);
void deletduili(struct duili *,int);
void genxinduili(struct duili *,int);
void genxin(struct duili *,int);
void heapshow(struct duili *);
#endif
