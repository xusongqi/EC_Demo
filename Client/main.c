/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月26日 星期一 15时23分40秒
* 
* FileName:     main.c
* 
* Description:  
*
*/
 
#include "encrypt.h"

int main(void)
{
	char md5_str[33] = {'\0'};
	unsigned char * str = "asdf";
	
	md5((unsigned char *)str, md5_str);

	printf("%s\n",md5_str);

	return 0;
}
