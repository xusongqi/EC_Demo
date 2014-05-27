/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月13日 星期二 10时59分25秒
* 
* FileName:     main.c
* 
* Description:  
*
*/
 
#include "server.h"
#include "database.h"

int main(void)
{
	while(1)
	{
		tcp_server();
		//database();
		sleep(1);
	}

	return 0;
}
