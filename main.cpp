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

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int main(int argc, char *argv[])
{
	MySQLConnWrapper db;
	db.init("127.0.0.1:11008", "root", "fdjkd&wi278^@6DGHfyTF");
	db.connect();
	db.switchDb("mihao");

#if 0	
	db.prepare("INSERT INTO active_user(create_time, mdn, imsi, esn) VALUES (?, ?, ?, ?)");
	string now=currentDateTime();
	db.setString(1,now);
	db.setString(2,"13301602770");
	db.setString(3, "6160761796");
	db.setString(4, "80D8852E");
	db.execute();

	db.setString(1,now);
	db.setString(2,"13301605333");
	db.setString(3, "0911785312");
	db.setString(4, "0911785312");
	db.execute();

	db.setString(1,now);
	db.setString(2,"13301605371");
	db.setString(3, "6301743459");
	db.setString(4, "8094016C");
	db.execute();
#endif

	char mdn[]="13301602770";
	char sql[100];
	sprintf(sql,"delete from active_user where mdn=%s",mdn);
	db.execute(sql);
	db.closePrepStmt();
	db.closeCon();

#if 0
	//db.execute("select * from active_user where mdn=13301602770");
	db.execute("select * from active_user");
	db.closeCon();


	while(db.fetch()){
		string create_time=db.getString("create_time");
		printf("create_time=%s\n", create_time.c_str());
		string mdn=db.getString("mdn");
		printf("mdn=%s\n", mdn.c_str());
		string imsi=db.getString("imsi");
		printf("imsi=%s\n", imsi.c_str());
		string esn=db.getString(3);
		printf("esn=%s\n", esn.c_str());
	}
#endif	
	return 0;
}
