
	
class Brochas 
{
	public:
	class nodo
	{
		public:
		Brocha objeto;	
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
	int numero_de_objetos=0;

	
	SDL_Color color = {255, 0, 0,255};
	float radio=1.0f;
	
	Brochas ();
	~Brochas ();
	void add ();
	void add (int sx,int sy);
	void del (void);		
	void del_seleccionados(void);
	void del_todos (void);
	void SelectAll (void);
	

	
	//void redimenciona (int gancho,int galto);
	//void redimenciona (int gancho,int galto,ImVec4 color_de_capa);
	//void redimenciona (int gancho,int galto,SDL_Color color_de_capa);
	//void despliega_viewer(void);	
	//void rellena (ImVec4 *color);
	//void rellena (SDL_Color *color);
	//void rellena (Capa brocha,SDL_Color *color);
	//void pixel (int x,int y,SDL_Color *color_de_capa);
	//void pixel (int x,int y,ImVec4 *color);
	//void pixel (int x,int y,SDL_Color *color)

		
		
	/*	
	
	void click (int x,int y);
	void Carga_sprite (SDL_Renderer *renderer,const char* file);
	void add_capa (SDL_Renderer *renderer,const char* file);		
	void SelectAll (void);	
	
	void despliega_capa(void);
	void despliega_capa_y_pinta (int x,int y,bool click,SDL_Renderer *renderer);
	
	void color_key (SDL_Renderer *renderer,ImVec4 *clear_color);
	
	//void renderer (SDL_Renderer*& renderer);
	void renderer (SDL_Renderer *renderer);
	
	void Graba_capas (const char* file);
	void Carga_capas (SDL_Renderer *renderer,const char* file); 
	
	*/
};

Brochas::Brochas() 
{
	
}

Brochas::~Brochas()
{
	int conteo=numero_de_objetos;	
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
			printf ("Brocha %d destruida\n",conteo);				
		}
	}
	
}

void Brochas::add ()
{
	indice= new nodo();
	
	numero_de_objetos++;	
	indice->nombre="Brocha-";	
	std::string no = std::to_string(numero_de_objetos);
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

void Brochas::add (int sx,int sy)
{
	add();
}

void Brochas::del (void)
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
				temp->objeto.~Brocha();
				delete temp;
				conteo--;
				printf ("Brocha Eliminada quedan %d brochas siguiente anterior\n",conteo);
				return;
			}
			
		if (temp->siguiente==NULL && temp->anterior!=NULL )  //Si no hay siguiente y si hay anterior
			{
				temp->anterior->siguiente=NULL;				
				indice=temp->anterior;
				temp->objeto.~Brocha();
				final=indice;
				delete temp;
				conteo--;
				printf ("Brocha Eliminada quedan %d brochas anterior existe siguiente no\n",conteo);
				return;
			}
			
		if (temp->siguiente!=NULL && temp->anterior==NULL )  //Si hay siguiente y si no hay anterior
			{								
				indice=temp->siguiente;
				indice->anterior=NULL;		
				inicio=indice;		
				temp->objeto.~Brocha();
				delete temp;				
				conteo--;
				printf ("Brocha Eliminada quedan %d brochas siguiente existe anterior no\n",conteo);
				return;
			}
		inicio=NULL;
		final=NULL;
		indice=NULL;
		temp->objeto.~Brocha();
		delete temp;
		conteo--;
		start=false;
		printf ("Brocha Eliminada quedan %d brochas lista vacia\n",conteo);		
	}
}

void Brochas::del_seleccionados(void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		if (indice->seleccionado) del();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Brochas::del_todos (void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		del();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Brochas::SelectAll(void)
{
	nodo *temp;	
	
	if (indice!=NULL)
	{
		
		temp=indice;
		
		indice=inicio;
		while (indice!=NULL)
		{	
			
			indice->seleccionado=true;
			indice=indice->siguiente;
		}
		
		if (temp!=NULL)
			indice=temp;
			else indice=NULL;
	}	
	
	
}


