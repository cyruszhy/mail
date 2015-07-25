#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "bianjiema.h"
#include <stdlib.h>
#include <fcntl.h>
#include <pwd.h>
char GetBase64Value(char ch)
{
	if ((ch >= 'A') && (ch <= 'Z'))
	{
		return ch - 'A';
	}
	if ((ch >= 'a') && (ch <= 'z'))
	{
		return ch - 'a' + 26;
	}
	if ((ch >= '0') && (ch <= '9'))
	{
		return ch - '0' + 52;
	}
	switch (ch) 
	{
		case '+':
		return 62;
		case '/':
		return 63;
		case '=':
		return 0;
		default:
		return 0;
	}
}
int base64_decode( char *gb2312string, char *base64string, int base64_len)
{
    int 	count = 0;
	int 	index = base64_len-1;
	unsigned char Base64Encode[4];
	int gb2312stringlen=0;
	while(base64string[index] == '=') {
		
		count++;
		index--;
	}

	while( base64_len > 2 )
	{
		Base64Encode[0] = GetBase64Value(base64string[0]);
		Base64Encode[1] = GetBase64Value(base64string[1]);
		Base64Encode[2] = GetBase64Value(base64string[2]);
		Base64Encode[3] = GetBase64Value(base64string[3]);

		*gb2312string ++ = (Base64Encode[0] << 2) | (Base64Encode[1] >> 4);
		*gb2312string ++ = (Base64Encode[1] << 4) | (Base64Encode[2] >> 2);
		*gb2312string ++ = (Base64Encode[2] << 6) | (Base64Encode[3]);

		base64string += 4;
		base64_len -= 4;
		gb2312stringlen += 3;
	}
	return gb2312stringlen - count;
}


int gb2312_to_utf8(unsigned char *gb2312string, int gb2312string_len, unsigned char *utf8string)
{
	int 	i;
	unsigned int 	index1,index2;
	unsigned short	tmp;
	unsigned short 	*p;
	unsigned char	*gb2312_char;
	unsigned char 	*utf8_char;
	int	utf8string_len = 0;
	unsigned short 	*twochar;
	gb2312_char  =(unsigned char *)gb2312string;
	utf8_char = (unsigned char *)utf8string;
	i = 0;
	while(i<gb2312string_len){	
		if(*gb2312_char >= 0x0 && *gb2312_char <= 0x7f){	
			*utf8_char = *gb2312_char;
			utf8_char++;
			utf8string_len++;
			gb2312_char++;
			i++;
		}else{
			twochar = (unsigned short *)gb2312_char;
			tmp = *twochar - 0xa0a0;
			index1 = tmp >> 8;
			index2 = tmp & 0xff;			
			tmp = gb_2_uni[index1][index2];
			*(utf8_char) = ((tmp >> 12) & 0x0f) | 0xe0;
			*(utf8_char+2) = (tmp & 0x3f) | 0x80;
			*(utf8_char+1) = ((tmp >> 6) & 0x3f) |0x80;
			utf8_char += 3;
			utf8string_len += 3;
			gb2312_char += 2;
			i +=2;
		}
	}
	return utf8string_len;
}




