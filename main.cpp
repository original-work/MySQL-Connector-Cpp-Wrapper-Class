/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016/8/15 11:08:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  wangxinxin, winer632@qq.com
 *   Organization:  lj
 *
 * =====================================================================================
 * ============================== CHANGE REPORT HISTORY ================================
 * |   VERSION   |   UPDATE DATE   |   UPDATED BY   |   DESCRIPTION OF CHANGE   |*
 
 * =========================== END OF CHANGE REPORT HISTORY ============================
 */
 /*
preinstall:
yum install -y boost boost-devel boost-doc
 */
#include <stdio.h>
#include "mysqlconn_wrapper.h"


int main(int argc, char *argv[])
{
	MySQLConnWrapper db;
	db.connect();
	db.switchDb("mihao");
	db.prepare("INSERT INTO active_user(mdn, imsi, esn) VALUES (?, ?, ?)");
	db.setString(1,"13301602770");
	db.setString(2, "6160761796");
	db.setString(3, "80D8852E");
	db.execute();
	
	db.setString(1,"13301605333");
	db.setString(2, "0911785312");
	db.setString(3, "0911785312");
	db.execute();

	
	db.setString(1,"13301605371");
	db.setString(2, "6301743459");
	db.setString(3, "8094016C");
	db.execute();


	//db.execute("select * from active_user where mdn=13301602770");
	db.execute("select * from active_user");
	db.closePrepStmt();
	
	while(db.fetch()){
		string mdn=db.getString("mdn");
		printf("mdn=%s\n", mdn.c_str());
		string imsi=db.getString("imsi");
		printf("imsi=%s\n", imsi.c_str());
		string esn=db.getString(3);
		printf("esn=%s\n", esn.c_str());
	}
	
	return 0;
}
