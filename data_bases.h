
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<double> fsec;

int mysql_connection (MYSQL *obj,char *host, char *user, char *pass,char *database,int port);

void select_data_base (int *autoid,MYSQL *obj,char *host, char *user, char *pass,char *database,int *port);

void write_database (MYSQL *mysql,char *arrkey,int sz);