#include <Brocha.h>
	
class Brochas 
{		
	class nodo
	{
		public:
		Brocha brocha;	
		bool seleccionado=false;
		std::string path;
		std::string nombre;
		nodo *anterior;
		nodo *siguiente;
	};
	
	public:
	nodo *indice=NULL;
	nodo *inicio=NULL;
	nodo *final=NULL;
	bool start=false;
	int numero_de_objetos=0;
	bool SELECTALL=false;	
	bool MULTI_VIEW=true;
	bool PROPORCIONES=true;
	bool MOSAICO=false;
	
	SDL_Color color_de_brocha = {255, 0, 0,255};
	
	Brochas ();
	~Brochas ();
	void add ();
	void add (int sx,int sy);
	void del (void);		
	void del_seleccionadas(void);
	void del_todos_los_nodos (void);
	void SelectAll (void);
	
	void redimenciona_todos_los_nodos (int ancho,int alto);
	void redimenciona_todos_los_nodos_seleccionados (int ancho,int alto);
	void despliega(void);
	
	//void redimenciona (int gancho,int galto);
	void redimenciona (int gancho,int galto,ImVec4 color_de_capa);
	void redimenciona (int gancho,int galto,SDL_Color color_de_capa);
	void despliega_capa(void);	
	void rellena (ImVec4 *color_de_capa);
	void rellena (SDL_Color *color_de_capa);
	void rellena (Capa capa,SDL_Color *color_de_capa);
	//void pixel (int x,int y,SDL_Color *color_de_capa);
	void pixel (int x,int y,ImVec4 *color_de_capa);
	void pixel (int x,int y,SDL_Color *color_de_capa)

		
		
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
				printf ("Capa %d destruida\n",conteo);
				
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
				temp->brocha.~Brocha();
				delete temp;
				conteo--;
				printf ("capa Eliminada quedan %d Capas siguiente anterior\n",conteo);
				return;
			}
			
		if (temp->siguiente==NULL && temp->anterior!=NULL )  //Si no hay siguiente y si hay anterior
			{
				temp->anterior->siguiente=NULL;				
				indice=temp->anterior;
				temp->brocha.~Brocha();
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
				temp->brocha.~Brocha();
				delete temp;				
				conteo--;
				printf ("capa Eliminada quedan %d capas siguiente existe anterior no\n",conteo);
				return;
			}
		inicio=NULL;
		final=NULL;
		indice=NULL;
		temp->brocha.~Brocha();
		delete temp;
		conteo--;
		start=false;
		printf ("capa Eliminada quedan %d Capas lista vacia\n",conteo);		
	}
}

void Capas::del_capas_seleccionadas(void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		if (indice->seleccionado) del_capa();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Capas::del_todas_las_capas (void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		del_capa();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Capas::SelectAll(void)
{
	nodo *temp;	
	
	if (indice!=NULL)
	{
		if (SELECTALLCAPAS==true) 
			SELECTALLCAPAS=false; else SELECTALLCAPAS=true;
		temp=indice;
		
		indice=inicio;
		while (indice!=NULL)
		{	
			
			indice->seleccionado=SELECTALLCAPAS;
			indice=indice->siguiente;
		}
		
		if (temp!=NULL)
			indice=temp;
			else indice=NULL;
	}	
	
	
}

void Capas::redimenciona_todas_las_capas (int ancho,int alto)
{
	nodo *temp;
	
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		
			indice->capa.alto=alto;
			indice->capa.ancho=ancho;
				
		indice=indice->siguiente;
	}
	
	if (temp!=NULL)
		indice=temp;
		else indice=NULL;
}

void Capas::redimenciona_todas_las_capas_seleccionadas (int ancho,int alto)
{
	nodo *temp;
	
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		if (indice->seleccionado)
		{
			indice->capa.alto=alto;
			indice->capa.ancho=ancho;
		}
		
		indice=indice->siguiente;
	}
	
	if (temp!=NULL)
		indice=temp;
		else indice=NULL;
}

void Capas::despliega(void)
{
	nodo *temp;
	if (inicio!=NULL)
	{
		temp=indice;
		indice=inicio;
		
			while (indice!=NULL)
			{						
				//ImGui::Text(indice->nombre.c_str());
				ImGui::Selectable(indice->nombre.c_str(), &indice->seleccionado);
				if (ImGui::IsItemClicked() ) 
				{
					temp=indice;
					if (KEY_CONTROL_LEFT==true)
					{
					
						if (indice->seleccionado)
						{
							indice->seleccionado=false;
						} else			
							{
								indice->seleccionado=true;
							
							}
					} else temp=indice;					
						
				}				
				if (indice==temp)
				{
					ImGui::SameLine();
					ImGui::SmallButton("*");
				}
							
				indice=indice->siguiente;		
			}
		indice=temp;
	}
}

void Capas::redimenciona (int gancho,int galto,ImVec4 color_de_capa)
{
	if (indice!=NULL)
	{
		if (indice->capa.rtdata!=NULL) free(indice->capa.rtdata);
		
			
			indice->capa.ancho_real=gancho;
			indice->capa.alto_real=galto;
			
			indice->capa.rtdata = (unsigned char*) malloc(indice->capa.ancho_real * indice->capa.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->capa.ancho_real*indice->capa.alto_real*4;i+=4)
		    {
		    	*(indice->capa.rtdata+i)=(Uint8)(color_de_capa.x*255);
		    	*(indice->capa.rtdata+i+1)=(Uint8)(color_de_capa.y*255);
		    	*(indice->capa.rtdata+i+2)=(Uint8)(color_de_capa.z*255);
		    	*(indice->capa.rtdata+i+3)=(Uint8)(color_de_capa.w*255);
		    	if (idx<=indice->capa.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->capa.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->capa.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->capa.ancho_real, indice->capa.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->capa.rtdata);
		
	}
}

void Capas::redimenciona (int gancho,int galto,SDL_Color color_de_capa)
{
	if (indice!=NULL)
	{
		if (indice->capa.rtdata!=NULL) free(indice->capa.rtdata);
		
			
			indice->capa.ancho_real=gancho;
			indice->capa.alto_real=galto;
			
			indice->capa.rtdata = (unsigned char*) malloc(indice->capa.ancho_real * indice->capa.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->capa.ancho_real*indice->capa.alto_real*4;i+=4)
		    {
		    	*(indice->capa.rtdata+i)=(Uint8)(color_de_capa.r);
		    	*(indice->capa.rtdata+i+1)=(Uint8)(color_de_capa.g);
		    	*(indice->capa.rtdata+i+2)=(Uint8)(color_de_capa.b);
		    	*(indice->capa.rtdata+i+3)=(Uint8)(color_de_capa.a);
		    	if (idx<=indice->capa.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->capa.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->capa.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->capa.ancho_real, indice->capa.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->capa.rtdata);
		
	}
}


void Capas::despliega_capa(void)
{
	nodo *temp;
	int count=0;
	std::string head="capasViewer-";
	std::string no;
	std::string header;
	
	ImGuiWindowFlags window_renderer_to_imgui = 0 | ImGuiWindowFlags_HorizontalScrollbar ;
	
	if (inicio!=NULL)
	{
				
		if (CAPA_MULTI_VIEW && CAPA_MOSAICO==false)
			{
				temp=indice;
				indice=inicio;
				while (indice!=NULL)
					{	
						count++;
						no = std::to_string(count);
						header=head+no;		
						
							ImGui::SetNextWindowSize(ImVec2(indice->capa.ancho, indice->capa.alto),  0);
							ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
																												
							float x =( ImGui::GetWindowSize().x - (float)(indice->capa.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->capa.alto))/2.0f; //draws grid correctly							
    						ImVec2 imagePosition(x, y);
    						//ImGui::SetCursorPos(imagePosition);														
							
							ImGui::Image(indice->capa.texturecapa , ImVec2((float)(indice->capa.ancho), (float)(indice->capa.alto)) );
							if (ImGui::IsItemClicked()) 
							{
								temp=indice;					
							}
							ImGui::End();			
							ImGui::Text(indice->nombre.c_str());							
						
						indice=indice->siguiente;		
					}
				indice=temp;
			}	else
				{		
					if (CAPA_MOSAICO==true)
					{
						
						temp=indice;
						indice=inicio;
						count++;
						no = std::to_string(count);
						header=head+no;	
						ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
						while (indice!=NULL)
							{		
								//float x =( ImGui::GetWindowSize().x - (float)(indice->capa.ancho))/2.0f; //draws grid correctly
								//float y =( ImGui::GetWindowSize().y - (float)(indice->capa.alto))/2.0f; //draws grid correctly							
    							//ImVec2 imagePosition(x, y);
									ImGui::Image(indice->capa.texturecapa , ImVec2((float)(indice->capa.ancho), (float)(indice->capa.alto)) );
									if (ImGui::IsItemClicked()) 
									{
										temp=indice;					
									}									
								
								indice=indice->siguiente;		
							}
						ImGui::End();									
						indice=temp;
					} else
						{
							ImGui::Begin("CAPA VIEWER",NULL,window_renderer_to_imgui);	
							
							float x =( ImGui::GetWindowSize().x - (float)(indice->capa.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->capa.alto))/2.0f; //draws grid correctly
							float aspecto=x/y;
		    				ImVec2 imagePosition(x, y);
		    				ImGui::SetCursorPos(imagePosition);    				
							ImGui::Image( indice->capa.texturecapa , ImVec2( (float)(indice->capa.ancho), (float)(indice->capa.alto) ) );
							
							ImGui::End();			
							ImGui::Text(indice->nombre.c_str());
						}
					
					
				}
				
	}
}

void Capas::rellena (ImVec4 *color_de_capa)
{
	
	if (indice!=NULL)
	{
		if (indice->capa.rtdata!=NULL) free(indice->capa.rtdata);
		
			
			indice->capa.rtdata = (unsigned char*) malloc(indice->capa.ancho_real * indice->capa.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->capa.ancho_real*indice->capa.alto_real*4;i+=4)
		    {
		    	*(indice->capa.rtdata+i)=(Uint8)(color_de_capa->x*255);
		    	*(indice->capa.rtdata+i+1)=(Uint8)(color_de_capa->y*255);
		    	*(indice->capa.rtdata+i+2)=(Uint8)(color_de_capa->z*255);
		    	*(indice->capa.rtdata+i+3)=(Uint8)(color_de_capa->w*255);
		    	if (idx<=indice->capa.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->capa.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->capa.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->capa.ancho_real, indice->capa.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->capa.rtdata);
		
	}
	
}

void Capas::rellena (SDL_Color *color_de_capa)
{
	
	if (indice!=NULL)
	{
		if (indice->capa.rtdata!=NULL) free(indice->capa.rtdata);
		
			
			indice->capa.rtdata = (unsigned char*) malloc(indice->capa.ancho_real * indice->capa.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->capa.ancho_real*indice->capa.alto_real*4;i+=4)
		    {
		    	*(indice->capa.rtdata+i)=(Uint8)(color_de_capa->r);
		    	*(indice->capa.rtdata+i+1)=(Uint8)(color_de_capa->g);
		    	*(indice->capa.rtdata+i+2)=(Uint8)(color_de_capa->b);
		    	*(indice->capa.rtdata+i+3)=(Uint8)(color_de_capa->a);
		    	if (idx<=indice->capa.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->capa.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->capa.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->capa.ancho_real, indice->capa.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->capa.rtdata);
		
	}
	
}


void Capas::pixel (int x,int y,ImVec4 *color_de_capa)
{
	
	if (indice!=NULL)
	{
		if (indice->capa.rtdata!=NULL) 
		{
		
			
			float degradado=1;
			int idx=0;
		    int i=(indice->capa.ancho_real*y)+x;
		    
	    	*(indice->capa.rtdata+i)=(Uint8)(color_de_capa->x*255);
	    	*(indice->capa.rtdata+i+1)=(Uint8)(color_de_capa->y*255);
	    	*(indice->capa.rtdata+i+2)=(Uint8)(color_de_capa->z*255);
	    	*(indice->capa.rtdata+i+3)=(Uint8)(color_de_capa->w*255);		    	
			
			glGenTextures(1, &indice->capa.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->capa.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->capa.ancho_real, indice->capa.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->capa.rtdata);
		}
		
	}
	
}

void Capas::pixel (int x,int y,SDL_Color *color_de_capa)
{
	
	if (indice!=NULL)
	{
		if (indice->capa.rtdata!=NULL) 
		{
		
			
			float degradado=1;
			int idx=0;
		    int i=(indice->capa.ancho_real*y)+x;
		    
	    	*(indice->capa.rtdata+i)=(Uint8)(color_de_capa->r);
	    	*(indice->capa.rtdata+i+1)=(Uint8)(color_de_capa->g);
	    	*(indice->capa.rtdata+i+2)=(Uint8)(color_de_capa->b);
	    	*(indice->capa.rtdata+i+3)=(Uint8)(color_de_capa->a);		    	
			
			glGenTextures(1, &indice->capa.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->capa.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->capa.ancho_real, indice->capa.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->capa.rtdata);
		}
		
	}
	
}