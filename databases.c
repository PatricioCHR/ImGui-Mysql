int mysql_connection (char *host, char *user, char *pass,char *database,int port)
{
		
	if (!mysql_init(&obj))
	{
		printf ("Falla al inicializar mysql. !");
		return 0;
	} else
		{
			printf ("Mysql inicializado correctamente. !");
		}
		
	
	if (!mysql_real_connect(&obj,"localhost","ingchavez13","cyemaz130374","cubiq_qkd_simulator",0,NULL,0))
	{
		printf ("Falla en conexion a base de datos. !\n");
		printf("Failed to connect to database: Error: %s\n", mysql_error(&obj));
			return 0;
	} else
		{
			printf ("Conexion a base de datos exitosa. !\n");
			
			
		}
	
	return 1;
}
