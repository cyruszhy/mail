#include "daxiaoduan.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
int decidebl()
{
	union{
		char decideblj[2];
	}decidebls={0x0102};
	if(decidebls.decideblj[0]==0x02){
		return 0;
	}else if(decidebls.decideblj[0]==0x01){
		return 1;
	}else{
		fprintf(stderr,"%s,%d,%s\n",__FILE__,__LINE__,strerror(errno));
		return -1;
	}
}
