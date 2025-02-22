class Nodos
{	
	public:
	class nodo
	{
		public:
		void *objeto;
		int tipo;
		bool seleccionado=false;
		std::string path;
		std::string nombre;
		nodo *anterior;
		nodo *siguiente;
	};
		
	
	nodo *indice=NULL;
	nodo *inicio=NULL;
	nodo *final=NULL;
	bool start=false;
	int numero_de_nodos=0;// se refiere al numero de nodos creados durante el funcionamiento del software
	int indice_de_autonombre=0;
	bool SELECT_ALL=false;	
	
	
	Nodos ();
	~Nodos ();
	void add_nodo ();
	void add_nodo (char *prefijo);
	void add_nodos (char *prefijo,int *cantidad);	
	void add_nodo (int sx,int sy);
	void del_nodo (void);		
	void del_nodos_seleccionados(void);
	void del_todos_los_nodos (void);
	void SelectAll (void);		
	
};

Nodos::Nodos() 
{
	
}

Nodos::~Nodos()
{
	int conteo=numero_de_nodos;	
	nodo *temp;
	conteo=0;
	if (inicio!=NULL)
	{
		temp=indice;
		indice=inicio;
		//if (indice->sprites.nombre)	delete[] indice->sprites.nombre; 
			while (indice!=NULL)
			{
				temp=indice;
				indice=temp->siguiente;		
				delete temp;
				conteo++;
				printf ("Capa %d destruida\n",conteo);
				
			}
	
	}
	
}

void Nodos::add_nodo ()
{
	indice= new nodo();
	
	numero_de_nodos++;	
	indice_de_autonombre++;
	indice->nombre="Nodo-";	
	std::string no = std::to_string(indice_de_autonombre);
	indice->nombre=indice->nombre+no;		
	printf("%s\n", indice->nombre.c_str());   
				
	if (start==false)
		{
			start=true;
			inicio=indice;
			indice->anterior=NULL;
			indice->siguiente=NULL;			
			final=indice;			
		} else
			{
				indice->anterior=final;				
				indice->siguiente=NULL;
				final->siguiente=indice;
				final=indice;				
			}
	
}

void Nodos::add_nodo (char *prefijo)
{
	indice= new nodo();
	
	numero_de_nodos++;	
	indice_de_autonombre++;
	indice->nombre=std::string(prefijo);	
	std::string no = std::to_string(indice_de_autonombre);
	indice->nombre=indice->nombre+no;		
	printf("%s\n", indice->nombre.c_str());   
				
	if (start==false)
		{
			start=true;
			inicio=indice;
			indice->anterior=NULL;
			indice->siguiente=NULL;			
			final=indice;			
		} else
			{
				indice->anterior=final;				
				indice->siguiente=NULL;
				final->siguiente=indice;
				final=indice;				
			}
	
}


void Nodos::add_nodos (char *prefijo,int *cantidad)
{
	for (int ciclo=0;ciclo<(*cantidad);ciclo++)
		add_nodo(prefijo);
}

void Nodos::add_nodo (int sx,int sy)
{
	add_nodo();
}

void Nodos::del_nodo(void)
{
	nodo *temp;
	int conteo=0;
	if (indice!=NULL)
	{
		temp=indice;
		
		if (temp->siguiente!=NULL && temp->anterior!=NULL)  //Si existe siguiente y anterior
			{
				temp->anterior->siguiente=temp->siguiente;
				temp->siguiente->anterior=temp->anterior;
				indice=temp->anterior;
				//temp->hoja.~Hoja();
				delete temp;
				conteo--;
				printf ("capa Eliminada quedan %d Capas siguiente anterior\n",conteo);
				return;
			}
			
		if (temp->siguiente==NULL && temp->anterior!=NULL )  //Si no hay siguiente y si hay anterior
			{
				temp->anterior->siguiente=NULL;				
				indice=temp->anterior;
				//temp->hoja.~Hoja();
				final=indice;
				delete temp;
				conteo--;
				printf ("capa Eliminada quedan %d Capas anterior existe siguiente no\n",conteo);
				return;
			}
			
		if (temp->siguiente!=NULL && temp->anterior==NULL )  //Si hay siguiente y si no hay anterior
			{								
				indice=temp->siguiente;
				indice->anterior=NULL;		
				inicio=indice;		
				//temp->hoja.~Hoja();
				delete temp;				
				conteo--;
				printf ("capa Eliminada quedan %d capas siguiente existe anterior no\n",conteo);
				return;
			}
		inicio=NULL;
		final=NULL;
		indice=NULL;
		//temp->hoja.~Hoja();
		delete temp;
		conteo--;
		start=false;
		printf ("capa Eliminada quedan %d Capas lista vacia\n",conteo);		
	}
}

void Nodos::del_nodos_seleccionados(void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		if (indice->seleccionado) del_nodo();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Nodos::del_todos_los_nodos (void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		del_nodo();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Nodos::SelectAll(void)
{
	nodo *temp;	
	
	if (indice!=NULL)
	{
		if (SELECT_ALL==true) 
			SELECT_ALL=false; else SELECT_ALL=true;
		temp=indice;
		
		indice=inicio;
		while (indice!=NULL)
		{	
			
			indice->seleccionado=SELECT_ALL;
			indice=indice->siguiente;
		}
		
		if (temp!=NULL)
			indice=temp;
			else indice=NULL;
	}	
	
	
}
	
