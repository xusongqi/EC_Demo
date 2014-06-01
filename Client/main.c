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
	char user_name[30];
	unsigned char pwd[30];
	char crypto_pwd[33] = {'\0'};
	
	while(1)
	{
		printf("your user name:\n");
		scanf("%s",user_name);
		printf("your password:\n");

	}

	md5((unsigned char *)pwd, crypto_pwd);

	printf("%s\n",crypto_pwd);

	return 0;
}
