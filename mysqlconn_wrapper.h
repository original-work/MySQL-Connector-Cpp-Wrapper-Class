 /*
 * =====================================================================================
 *
 *       Filename:  mysqlconn_wrapper.h
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

#ifndef MYSQLCONN_WRAPPER_H
#define	MYSQLCONN_WRAPPER_H

#include "mysql_connection.h"
	
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class MySQLConnWrapper
{

public:

	/* Your MySQL server settings */
	MySQLConnWrapper();
	~MySQLConnWrapper();
	void init(string h, string u, string p);
	string getHost();
	string getUser();
	string getPassword();
	void manageException(sql::SQLException& e);
	void connect();
	void switchDb(const string& db_name);
	void prepare(const string& query);
	void setInt(const int& num, const int& data);
	void setString(const int& num, const string& data);
	void execute(const string& query = "");
	bool fetch();
	sql::ResultSet* getRes();
	string getString(const string& field);
	string getString(const int& index);
	int getInt(const string& field);
	int getInt(const int& index);
 	 void closeCon();



private:

	string host;
	string user;
	string password;
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* prep_stmt;
	sql::ResultSet* res;

};


#endif	/* MYSQLCONN_WRAPPER_H */


