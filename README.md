MySQL-Connector-Cpp-Wrapper-Class
=================================

A Wrapper Class for the MySQL Connector/C++ Library.

Requirements
=================================

Linux distribution.

MySQL Connector/C++ Library

For more information see: http://dev.mysql.com/doc/connector-cpp/en/index.html



Which execute function should i use in MySQL connector/c++?
===========================================================


I need to write a wrapper (based on MySQL Connector/C++) which encapsulate specific SQL statements and provide user friendly interfaces, like: insert(), update(), delete(), select(), etc.

In MySQL's native C API, every SQL statement could be executed by simply call "mysql_real_query()", but now, in MySQL Connector/C++, things get a little confused. There's 3 execute functions in sql::Statment class and 6 execute functions in sql::PreparedStatement class:

mysql-connector-c++-1.1.5\driver\mysql_statement.h:

bool execute(const sql::SQLString& sql);
sql::ResultSet* executeQuery(const sql::SQLString& sql);
int executeUpdate(const sql::SQLString& sql);
mysql-connector-c++-1.1.5\driver\mysql_prepared_statement.h, 104:

bool execute();
bool execute(const sql::SQLString& sql);

sql::ResultSet executeQuery();
sql::ResultSet executeQuery(const sql::SQLString& sql);

int executeUpdate();
int executeUpdate(const sql::SQLString& sql);
I wondered why there're so many execution functions rather than a simple and unified one? And which execute function should i use for specify SQL statements?

Note: I'm using MySQL Connector/C++ 1.1.5 with MySQL Server 5.6 as backend.

c++ mysql mysql-connector
shareimprove this question
asked Dec 15 '14 at 9:18




accepted Answer
===============

Each of the three functions have a specific use, which can be guessed from their return type.

execute

This function is the most generic one. It returns a boolean value, which value is true if the query returns multiple results, or false if the query returns either nothing or an update count.

This is the function you'll want to use if you only want to use one to be as generic as possible.

If it returns true, you'll want to use ResultSet * getResultSet() to get the results.
If it returns false, you'll want to use uint64_t getUpdateCount() to get the number of updated rows.

executeQuery

This function directly returns a ResultSet which is useful for SELECT statements, and assumes there is indeed a result set to be returned.

It is equivalent to call execute() followed by getResultSet().

You'll want to use this function when you know you are using SQL code that returns results such as rows.

executeUpdate

This function returns an integer value which is useful for UPDATE statements and assumes there is an update count to be returned.

It is equivalent to call execute() followed by getUpdateCount(), even though, for some reason, the return types are different (int vs uint64_t).

This is the function to use when executing SQL statements that modify data and you need to know whether some data was modified.

So,

why there're so many execution functions rather than a simple and unified one?
the unified one is in fact execute, which can be used to execute arbitrary SQL and handle the result appropriately, while the two other ones are convenient wrappers when you know what kind of query you execute.

which execute function should i use for specify SQL statements?
In your case, since you are writing a wrapper around the SQL language, each of your functions knows which kind of statement it will execute, so use of the convenience functions will allow you to write shorter code.

For example:

insert(), update(), delete() ---> executeUpdate()
select()                     ---> executeQuery()
shareimprove this answer
answered Dec 15 '14 at 11:24

SirDarius
21.3k44459
  	 	
Thanks Darius, your answer is clear and detailed. Appreciated it. ¨C Tim John Dec 15 '14 at 15:14
add a comment
