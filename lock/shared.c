#include "shared.h"
void * getSharedMemory(const char * name,int size,int * needInit)
{
	int fd;
	if(access(name,0)!=0)
	{
		fd=open(name,O_CREAT|O_RDWR,0644);
		if(fd<0)
		{
			fprintf(stderr,"%s,%d,%s\n",__FILE__,__LINE__,strerror(errno));
			exit (0);
		}
		*needInit=1;
	}
	else
	{
		fd=open(name,O_RDWR);
		if(fd<0)
		{
			fprintf(stderr,"%s,%d,%s\n",__FILE__,__LINE__,strerror(errno));
			exit (0);
		}
		*needInit=0;
	}
	

	int ret = ftruncate(fd,size);
	if(ret == -1) abort();

	void * ptr = mmap(0,size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

	close(fd);

	if(ptr == (void *)-1) abort();

	return ptr;
}

void releaseSharedMemory(const char * name,void * addr,int size)
{
	int ret = munmap(addr,size);
	if(ret == -1) abort();
}

pthread_mutex_t * getSharedMutex(const char * name)
{
	int needInit = 0;
	pthread_mutex_t * mutex = (pthread_mutex_t *)getSharedMemory(name,sizeof(pthread_mutex_t),&needInit);	

	if(needInit == 1)
	{
 	 	pthread_mutexattr_t attr;
 	    int r = pthread_mutexattr_init(&attr);
 	    if(r != 0) abort();
    	
 	    r = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
 	    if(r != 0) abort();
 	    	
 	    r = pthread_mutex_init(mutex, &attr);
 	    if(r != 0) abort();
 	    
 	    r = pthread_mutexattr_destroy(&attr);
 	    if(r != 0) abort();
	}

	return mutex;
}

void releaseSharedMutex(const char * name,void * addr)
{
	releaseSharedMemory(name,addr,sizeof(pthread_mutex_t));
}

