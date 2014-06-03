/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年06月01日 星期日 15时29分55秒
* 
* FileName:     connect.h
* 
* Description:  
*
*/

#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "EC_client_include.h"

#define LENGTH 1024

int tcp_client()
{
	int i,								//循环变量
		choice,							//用户功能选择
		cnt_fd,							//连接的描述符
		recbytes;						//计数器
	char recv_buffer[LENGTH]={'\0'},	//发送数据缓冲区
		 send_buffer[LENGTH]={'\0'},	//接收数据缓冲区
		 user_name[30] = {'\0'},		//用户名
		 user_password[30] = {'\0'},	//密码
		 encrypt_password[32] = {'\0'};	//加密后的密码
	struct sockaddr_in server_addr,		//服务端地址
					   client_addr;		//客户端地址
	unsigned short portnum = 21567;		//端口信息

	cnt_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(cnt_fd <= 0)
	{
		printf("SOCKET FAILED\n");
		return -1;
	}
	printf("socket...ok\t");

	memset(&server_addr, sizeof(server_addr), '\0');		//将目标地址变量置零
	server_addr.sin_family = AF_INET;						//设置目标地址的地址描述，一般都是AF_INET
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//设置目标IP
	server_addr.sin_port = htons(portnum);					//设置目标端口

	if(connect(cnt_fd, (struct sockaddr *)(&server_addr), sizeof(server_addr) ) == -1)
	{
		printf("CONNECT FAILED\n");
		return -1;
	}printf("connect ...ok\n");

	while(1)
	{
		printf("1.登录用户\n");
		printf("2.发送数据\n");
		printf("3.登出用户\n");
		printf("0.退出程序\n");
		scanf("%d",&choice);
		getchar();

		switch(choice)
		{
			case 1:
				//printf("用户名：\n");
				i = 0;
				do{
				scanf("%c", &user_name[i]);
				}while( user_name[i++] != '\n' );

			//	printf("密码：\n");
				i = 0;
				do{
				scanf("%c", &user_password[i]);
				}while( user_password[i++] != '\n' );

				encrypt(user_password, sizeof(user_password), encrypt_password);
				printf("%s",encrypt_password);
				//xmlString(send_buffer);
				sprintf(send_buffer, "<?xml version=\'1.0\' encoding=\'UTF-8\' ?><login><user_name>%s</user_name><user_pwd> %s</user_pwd></login>", user_name,user_password);
				write(cnt_fd, send_buffer, LENGTH);
				fflush(stdin);
				break;
			case 2:
				puts("non-available yet");
				break;
			case 3:
				puts("non-available yet");
				break;
			case 0:
				exit(0);
		}

	}
}

#endif
