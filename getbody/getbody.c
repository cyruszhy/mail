#include "getbody.h"
#include "../header.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <pwd.h>
int getbody(char *buf, int bufsize, unsigned char *body){


	unsigned char 	*ptr1, *ptr2;
	unsigned char	*prebody;
	int 	bodylen = 0;
	int 	flag1 = 0;
	int 	flag2 = 0;
	int	len;
	unsigned char	tmp;
	int 	i;
	puts("1");
	prebody = (unsigned char *)malloc(4096);
	if( buf != NULL) {
		ptr1 = strstr(buf, "</head>");
		if(NULL == (ptr2 = strstr(ptr1, "</body>"))) ptr2 = strstr(ptr1, "</html>");
				puts("11");
		ptr1 += 16;
		puts(ptr1);
		len = ptr2 - ptr1;
		while(len > 0){
			if(flag1 == 1){
				flag2 = 0;
				if(*ptr1 == '>'){
					flag1 = 0;
				}
			}

			else {
				if(*ptr1 == '<') {
					if(flag2 == 1) {
						flag2 = 0;
						prebody[bodylen] = '\n';
						bodylen++;
					}
					flag1 = 1;
				}
				else if(strncmp(ptr1,"=\r\n",3) == 0 || strncmp(ptr1,"=0A",3) == 0) {
					
					ptr1 += 3;
					len -= 3;
					continue;
				}
				else {
					flag2 = 1;
					prebody[bodylen] = *ptr1;
					bodylen++;

				}
			}
			ptr1++;
			len--;
		}
	}
	puts("2");
	len = 0;
	i = 0;
	while(len < bodylen){	
		tmp = 0;
		if(prebody[len] == '='){			
			if(prebody[len+1] == '=') len += 2;
			else len += 1;		
			if(prebody[len] >= '0' && prebody[len] <= '9') tmp += (prebody[len] - '0')*16;
			else tmp += (prebody[len] - 55)*16;
			if(prebody[len+1] >= '0' && prebody[len+1] <= '9' ) tmp += (prebody[len+1] -'0');
			else tmp += (prebody[len+1] -55);		
			body[i] = tmp;			
			i++;
			len += 2;
		}
		else{		
			body[i]= prebody[len];		
			i++;
			len++;
		}
	}
	puts("3");
	free(prebody);
	return len;
}

