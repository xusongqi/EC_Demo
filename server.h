/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月13日 星期二 09时59分55秒
* 
* FileName:     server.h
* 
* Description:  
*
*/
#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/in.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

#define LENGTH 1024

void tcp_server();

void tcp_server()
{
	/*描述符*/
	int sfp,//接受所有连接请求	
		nfp;//处理单独的客户请求
	struct sockaddr_in server_addr,//服务端地址
					   client_addr;//客户端地址
	int sin_size;//地址长度
	unsigned short portnum = 21567;//服务器使用端口
	char server_msg[LENGTH];
	
	//read()相关变量
	char buffer[LENGTH];//存储read()收到的信息
	int recbytes;//	计数buffer收到的字节数

	/*设置监听的端口和IP信息*/
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(portnum);

	/*socket() */
	sfp = socket(AF_INET, SOCK_STREAM,0);
	setsockopt(sfp, SOL_SOCKET, SO_REUSEADDR, NULL, 1);//端口复用
	if(sfp == -1)
	{
		printf("SOCKET FAILED\n");
		exit(1);
	}
	printf("socket ok... ");

	/*bind() */
	if(-1 == bind(sfp,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)))
	{
		printf("BIND FAILED\n");
		exit(1);
	}
	printf("bind ok... \n");

	/*listen() */
	if(-1 == listen(sfp,5))
	{
		printf("LISTEN FAILED\n");
		exit(1);
	}
	printf("listen ok...");
	
	sin_size = sizeof(struct sockaddr_in);
	
	/*开启服务*/
	while(1)
	{
		/*accept() */
		if(-1 == (nfp = accept(sfp,(struct sockaddr *)(&client_addr),&sin_size)))
		{
			printf("ACCEPT FAILED\n");
			exit(1);
		}
		/*输出目标的ip和端口*/
		printf("accept ok... \nserver start get connect from %#x : %#x\n",
					ntohl(client_addr.sin_addr.s_addr),ntohs(client_addr.sin_port));	

		/*单个客户连接子进程*/
		if(fork() == 0)
		{
			close(sfp);
			/*read() 接收消息*/
			while(1)
			{
				if( (recbytes = read(nfp,buffer,LENGTH)) <= 0)
				{
					break;
				}
				buffer[recbytes]='\0';
				printf("%s    ",buffer);
				printf("    【READ SUCCESS】\n");
			}

			close(nfp);
			printf(" server disconnected from %#x : %#x\n",
					ntohl(client_addr.sin_addr.s_addr),ntohs(client_addr.sin_port));	
			exit(0);	//防止子进程进入外循环接受sfp;
		}//[nfp子进程]结束
		
		/*父服务进程*/
		else
		{
			close(nfp);
		}
	}//[while大循环]结束
	close(sfp);
}
#endif
