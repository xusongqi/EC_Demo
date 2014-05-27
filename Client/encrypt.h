/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月26日 星期一 15时10分11秒
* 
* FileName:     ecrypt.h
* 
* Description:  编译加参数：-lssl -lcrypto
*
*/

#ifndef _ENCRYPT_H_
#define _ENCRYPT_H_

#include "EC_client_include.h"

char * md5(unsigned char * str, char * buff);

char * md5(unsigned char * str, char * buff)
{
	MD5_CTX ctx;
	unsigned char md5[16] = {0};
	char tmp[3]={'\0'};
	int i;

	MD5_Init(&ctx);

	MD5_Update(&ctx, str, strlen(str));

	MD5_Final(md5, &ctx);

	for(i = 0; i<16; i++)
	{
		sprintf(tmp, "%02x", md5[i]);
		strcat(buff, tmp);
	}
	//printf("%s\n",buff);

	return buff;
}

#endif
