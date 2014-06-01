/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月31日 星期六 11时17分15秒
* 
* FileName:     xml_analyse.h
* 
* Description:  -lxml2
*
*/

#ifndef _XML_ANALYSE_H_
#define _XML_ANALYSE_H_

#include "EC_include.h"

#define ERRX_READ_FILE			0x0001	//读取xml错误
#define ERRX_GET_ELEMENT		0x0010	//获取元素错误
#define ERRX_INFO_NOT_MATCH		0x0100	//文件信息不匹配
#define ERRX_HEAD_NOT_MATCH		0x1000	//信息头不匹配

int msg_analyse(const char * xml_msg, int msg_len);

int msg_analyse(const char * xml_msg, int msg_len)
{
	char		n = 0;				//子节点计数器
	xmlDocPtr	xml_fd = NULL;		//xml描述符
	xmlNodePtr	xml_root = NULL,	//xml的root节点
				curNode = NULL;		//xml的子节点

	xmlKeepBlanksDefault(0);//忽视xml中的空格，避免读出node = text的空节点

	/*读取msg内容*/
	xml_fd = xmlParseMemory(xml_msg, msg_len);
	if(xml_fd == NULL)
	{
		printf("read file error\n");
		return ERRX_READ_FILE;
	}

	/*获取msg中的root元素*/
	xml_root = xmlDocGetRootElement(xml_fd);
	if(xml_root == NULL)
	{
		printf("get element error\n");
		return ERRX_GET_ELEMENT;
	}


	/* 对信息头（root元素）进行匹配
	 *
	 * xml_root->name类型为xmlChar，本质上是unsigned char
	 * */
	if(!xmlStrcmp(xml_root->name, BAD_CAST "login") )
	{
		printf("login\n");
		//login();
	}
	else if(!xmlStrcmp(xml_root->name, BAD_CAST "sendmsg") )
	{
		printf("sendmsg\n");
		//recv();
	}
	else if(!xmlStrcmp(xml_root->name, BAD_CAST "logout") )
	{
		printf("logout\n");
		//logout();
	}
	else
	{	return ERRX_HEAD_NOT_MATCH;}
	
	xmlFreeDoc(xml_fd);
	xmlCleanupParser();

	return 0;
}

#endif
