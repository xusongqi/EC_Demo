/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月27日 星期二 12时22分00秒
* 
* FileName:     Login.h
* 
* Description:  
*
*/

#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "EC_client_include.h"
#include "encrypt.h"

void login()
{
	char * user_name;
	char * password;
	char encrypt_pwd[33];
	_Bool flag;

	while(1)
	{
		md5(passwword, encrypt_pwd);

		flag = request_connect(user_name, encrypt_pwd);
		if(flag)
		{
			do_sth();
		}
		else
		{	printf("USER or PASSWORD ERROR\n");}
	}
}

#endif
