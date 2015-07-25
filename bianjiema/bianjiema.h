#ifndef BIANJIEMA 
#define BIANJIEMA 1
unsigned short gb_2_uni[95][95];
char GetBase64Value(char);
int base64_decode( char *gb2312string, char *base64string, int base64_len);
int gb2312_to_utf8(unsigned char *gb2312string, int gb2312string_len, unsigned char *utf8string);
#endif
