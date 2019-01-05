#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *data, int nColumn, char **colValues, char **colNames)
{
    for(int i = 0; i < nColumn; ++i)
    {
	printf("%s = %s\n", colNames[i], colValues[i] ? colValues[i] : NULL);
    }
    printf("\n");
    return 0;
}

int main()
{
    sqlite3 *db = NULL;
    char *err_msg = NULL;
    char *path = "/home/huangzisheng/ftp/user.db";
    char *sql = "select * from user;";
    const char *data = "Callback function called";
    if(sqlite3_open(path, &db) != SQLITE_OK)
    {
	printf("can not open the database!\n");
	exit(-1);
    }
    else
    {
	printf("open database successful!\n");
    }
    if(sqlite3_exec(db, sql, callback, (void*)data, &err_msg) != SQLITE_OK)
    {
	printf("exec error!\n");
	exit(-1);
    }
    if(sqlite3_close(db) != SQLITE_OK)
    {
	printf("cannot close the database\n");
	exit(-1);
    }
    return 0;
}
