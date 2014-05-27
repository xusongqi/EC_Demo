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

#include "EC_include.h"

#define LENGTH 1024

char * server_time();

char * server_time()
{
	time_t rawtime;//服务器时间
	struct tm * server_time;
	time(&rawtime);
	server_time = localtime(&rawtime);
	return asctime(server_time);
}

void tcp_server()
{
	int listen_fd,//描述符：接受所有连接请求	
		server_fd;//描述符：处理单独的客户请求
	struct sockaddr_in server_addr,//服务端地址
					   client_addr;//客户端地址
	int sin_size;//地址长度
	unsigned short portnum = 21567;//服务器使用端口
	char server_msg[LENGTH];//发送内容长度[write()]
	char buffer[LENGTH];//存储收到的信息[read()]
	int recbytes;//	计数buffer收到的字节数[read()]

	/*设置监听的端口和IP信息*/
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(portnum);

	/*socket() */
	listen_fd = socket(AF_INET, SOCK_STREAM,0);
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, NULL, 1);//端口复用,最后两个参数常用opt=1和sizeof(opt)
	if(listen_fd == -1)
	{
		printf("SOCKET FAILED\n");
		exit(1);
	}
	printf("socket ok... ");

	/*bind() */
	if(-1 == bind(listen_fd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)))
	{
		printf("BIND FAILED\n");
		exit(1);
	}
	printf("bind ok... \n");

	/*listen() */
	if(-1 == listen(listen_fd,5))
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
		if(-1 == (server_fd = accept(listen_fd,(struct sockaddr *)(&client_addr),&sin_size)))
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
			close(listen_fd);
			/*read() 接收消息*/
			while(1)
			{
				if( (recbytes = read(server_fd,buffer,LENGTH)) <= 0)
				{
					break;
				}
				buffer[recbytes]='\0';
				printf("%s    ",buffer);
				printf("from %#x : %#x : ",ntohl(client_addr.sin_addr.s_addr),ntohs(client_addr.sin_port));	
				printf("%s\n",server_time());
			}

			close(server_fd);
			printf(" server disconnected from %#x : %#x : ",
					ntohl(client_addr.sin_addr.s_addr),ntohs(client_addr.sin_port));	
			printf("%s\n",server_time());
			exit(0);	//防止子进程进入外循环接受listen_fd;
		}//[server_fd子进程]结束
		
		/*父服务进程*/
		else
		{
			close(server_fd);
		}
	}//[while大循环]结束
	close(listen_fd);
}
#endif
