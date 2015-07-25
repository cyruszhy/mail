#ifndef SHAREDMUTEX_H
#define SHAREDMUTEX_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

static void * getSharedMemory(const char * name,int size,int * needInit);

static void releaseSharedMemory(const char * name,void * addr,int size);

pthread_mutex_t * getSharedMutex(const char * name);

void releaseSharedMutex(const char * name,void * addr);

#endif