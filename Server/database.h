/* 
* Author:		xusongqi@live.com
* 
* Created Time: 2014年05月15日 星期四 10时33分33秒
* 
* FileName:     database.c
* 
* Description:  
*
*/
 
#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "EC_include.h"

int database()
{
	MYSQL * dbfp;
	MYSQL_RES * res;
	MYSQL_ROW  row;
	char *query = "select * from user;";
	int t,r;

	mysql_init(dbfp);

	if(!mysql_real_connect(dbfp, "localhost", "root", "xsq921222", "EC_Demo", 0, NULL, 0))
	{
		printf("DB_error: mysql_real_connect();\n");
		mysql_close(dbfp);
		return false;
	}printf("mysql_real_connect()...ok\n");

	if(mysql_query(dbfp, query))
	{
		printf("DB_error:mysql_query();\n");
		mysql_close(dbfp);
		return false;
	}printf("mysql_query()...ok\n");
	
	res = mysql_use_result(dbfp);//逐行的结果集检索
	if(res)
	{
		for(r = 0; r < mysql_field_count(dbfp); r++)//mysql_field_count()返回上次执行的结果列的数目
		{
			row = mysql_fetch_row(res);//从结果集获取下一行
			if(row < 0)
			{break;}
			for(t = 0; t < mysql_num_fields(res); t++)
			{printf("%s\n",row[t]);}
		}
	}
	mysql_free_result(res);
	mysql_close(dbfp);

	return true;
}

#endif
