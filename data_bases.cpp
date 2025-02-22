#include <string>
#include <stdio.h>
#include <ImGui.h>
#include <ctime>
#include <chrono>
#include <mysql.h>
#include <mysqld_error.h>
#include "data_bases.h"


extern double keytimetoborn;
extern double timetoupload;

char error[200]="";

using namespace std;

bool conexion=false;


int mysql_connection (MYSQL *obj,char *host, char *user, char *pass,char *database,int port)
{
		
	if (!mysql_init(obj))
	{
		printf ("Falla al inicializar mysql. !\n");
		conexion=false;
		return 0;
	} else
		{
			printf ("Mysql inicializado correctamente. !\n");
		}	
	
	if (!mysql_real_connect(obj,host,user,pass,database,port,NULL,0))
	{
		printf ("Falla en conexion a base de datos. !\n");
		printf ("Failed to connect to database: Error: %s\n", mysql_error(obj));
		conexion=false;
		return 0;
	} else
		{
			printf ("Conexion a base de datos exitosa. !\n");
			conexion=true;			
		}
	
	return 1;
}

void select_data_base (int *autoid,MYSQL *obj,char *host, char *user, char *pass,char *database,int *port)
{

	ImGui::Begin ("Database Connection");
		*autoid++;
		ImGui::PushID(autoid); 
		ImGui::Text ("Host :");	ImGui::InputText("##", host , 300);
		ImGui::PopID();
		
		*autoid++;		   
		ImGui::PushID(autoid); 
		ImGui::Text ("User :");	
		ImGui::InputText("##", user , 100);
		ImGui::PopID();
		
		*autoid++;
		ImGui::PushID(autoid); 
		ImGui::Text ("Password :");	ImGui::InputText("##", pass , 100,ImGuiInputTextFlags_Password);
		ImGui::PopID();
		
		*autoid++;
		ImGui::PushID(autoid); 
		ImGui::Text ("Database :");	ImGui::InputText("##", database , 100);
		ImGui::PopID();
		
		*autoid++;
		ImGui::PushID(autoid); 
		ImGui::Text ("Port :"); ImGui::InputInt("##",port);
		ImGui::PopID();		
		
		if (ImGui::Button ("Conexion"))
		{
			if (mysql_connection (obj,host, user, pass,database,*port))
			{				
				conexion=true;
			} 
		}		
		
		ImGui::SeparatorText("database status");
		if (conexion)
		{
			ImGui::Text ("Conexion ok !! :");
			ImGui::Text ("");
		}			
		else
			{
				ImGui::Text ("No conexion :");	
				ImGui::Text (error);	
			}			
		
	ImGui::End ();
}

void write_database (MYSQL *mysql,char *arrkey,int sz)
{
	char query[1000],*end;
	char ctemp[10];
	
	char sdatetime[50];	
	time_t timestamp;
	struct tm datetime;

		
	strcpy(query,"Insert INTO keyscubiq (`Keyqkd`,Sizekey,timetoborn,Date) VALUES ( '");
	strcat (query,arrkey);
	strcat (query,"','");
	
	itoa(sz,ctemp,10);
	strcat (query,ctemp);
	strcat (query,"','");
	
	sprintf(ctemp, "%.4f", keytimetoborn);	
	strcat (query,ctemp);
	strcat (query,"','");
		
	timestamp = time(NULL);
	datetime = *localtime(&timestamp);
	strftime(sdatetime, 50, "%Y-%m-%d %H:%M:%S ", &datetime);
    
    printf ("%s",&sdatetime);	
	
	strcat (query,sdatetime);
	strcat (query,"') ");
	
	printf ("%s\n",query);	 
	
    auto t0 = Time::now();
	
	if (mysql_query(mysql,query))
	{
		strcpy(error,mysql_error(mysql));
		printf("Error : %s\n", mysql_error(mysql));
	}	

    auto t1 = Time::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);
    
    printf("Time to upload %f s\n", fs.count());
    printf("Time to upload %d ms\n",d.count() );
	
	
}
