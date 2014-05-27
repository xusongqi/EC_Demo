/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月15日 星期四 10时35分38秒
* 
* FileName:     EC_include.h
* 
* Description: include all inuse head-files and the functions' declarations
*
*/

#ifndef _EC_INCLUDE_
#define _EC_INCLUDE_

#include <errno.h>
#include <fcntl.h>
//#include <linux/in.h>
#include <mysql/mysql.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <time.h>

#define true 1
#define false 0

typedef int Status;

int tcp_server();
int database();

#endif
