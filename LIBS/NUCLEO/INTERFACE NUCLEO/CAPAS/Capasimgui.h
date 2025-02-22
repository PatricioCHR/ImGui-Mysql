#include "Capas.h"



class Capasimgui: public Capas
{
	public :
		
	bool SELECTALL=false;	
	bool MULTI_VIEW=true;
	bool PROPORCIONES=true;
	bool MOSAICO=false;
	
	bool SOBRE_CAPA_ACTIVA=false;
	bool CAPA_ACTIVA_CLICK=false;
	ImVec2 poscapaactiva;
	
	SDL_Color color = {255, 0, 0,255};
	void redimenciona_todos (int ancho,int alto);
	void redimenciona_todos_los_seleccionados (int ancho,int alto);
	void despliega(void);
	
	//void redimenciona (int gancho,int galto);
	void redimenciona (int gancho,int galto,ImVec4 color);
	void redimenciona (int gancho,int galto,SDL_Color color);
	void despliega_viewer(void);
	void despliega_viewer_pinta (float radio,SDL_Color color);
	void rellena (ImVec4 *color);
	void rellena (SDL_Color *color);
	void rellena (Capa capa,SDL_Color *color);
	//void pixel (int x,int y,SDL_Color *color_de_capa);
	void pixel (int x,int y,ImVec4 *color);
	void pixel (int x,int y,SDL_Color *color);
	void SelectAll(void);
	Capasimgui ();
	~Capasimgui ();
		
		
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

Capasimgui::Capasimgui() 
{
	
}

Capasimgui::~Capasimgui()
{
	
	
}

void Capasimgui::redimenciona_todos (int ancho,int alto)
{
	nodo *temp;
	
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		
			indice->objeto.alto=alto;
			indice->objeto.ancho=ancho;
				
		indice=indice->siguiente;
	}
	
	if (temp!=NULL)
		indice=temp;
		else indice=NULL;
}

void Capasimgui::redimenciona_todos_los_seleccionados (int ancho,int alto)
{
	nodo *temp;
	
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		if (indice->seleccionado)
		{
			indice->objeto.alto=alto;
			indice->objeto.ancho=ancho;
		}
		
		indice=indice->siguiente;
	}
	
	if (temp!=NULL)
		indice=temp;
		else indice=NULL;
}

void Capasimgui::despliega(void)
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
					if (SDL_IO::KEY_CONTROL_LEFT==true)
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

void Capasimgui::redimenciona (int gancho,int galto,ImVec4 color)
{
	if (indice!=NULL)
	{
		if (indice->objeto.rtdata!=NULL) free(indice->objeto.rtdata);
		
			
			indice->objeto.ancho_real=gancho;
			indice->objeto.alto_real=galto;
			
			indice->objeto.rtdata = (unsigned char*) malloc(indice->objeto.ancho_real * indice->objeto.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->objeto.ancho_real*indice->objeto.alto_real*4;i+=4)
		    {
		    	*(indice->objeto.rtdata+i)=(Uint8)(color.x*255);
		    	*(indice->objeto.rtdata+i+1)=(Uint8)(color.y*255);
		    	*(indice->objeto.rtdata+i+2)=(Uint8)(color.z*255);
		    	*(indice->objeto.rtdata+i+3)=(Uint8)(color.w*255);
		    	if (idx<=indice->objeto.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;		    	
			}	
			glGenTextures(1, &indice->objeto.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->objeto.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->objeto.ancho_real, indice->objeto.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->objeto.rtdata);
		
	}
}

void Capasimgui::redimenciona (int gancho,int galto,SDL_Color color)
{
	if (indice!=NULL)
	{
		if (indice->objeto.rtdata!=NULL) free(indice->objeto.rtdata);
		
			
			indice->objeto.ancho_real=gancho;
			indice->objeto.alto_real=galto;
			
			indice->objeto.rtdata = (unsigned char*) malloc(indice->objeto.ancho_real * indice->objeto.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->objeto.ancho_real*indice->objeto.alto_real*4;i+=4)
		    {
		    	*(indice->objeto.rtdata+i)=(Uint8)(color.r);
		    	*(indice->objeto.rtdata+i+1)=(Uint8)(color.g);
		    	*(indice->objeto.rtdata+i+2)=(Uint8)(color.b);
		    	*(indice->objeto.rtdata+i+3)=(Uint8)(color.a);
		    	if (idx<=indice->objeto.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;		    	
			}	
			glGenTextures(1, &indice->objeto.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->objeto.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->objeto.ancho_real, indice->objeto.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->objeto.rtdata);		
	}
}


void Capasimgui::despliega_viewer(void)
{
	nodo *temp;
	int count=0;
	std::string head="capasViewer-";
	std::string no;
	std::string header;
	
	ImGuiWindowFlags window_renderer_to_imgui = 0 | ImGuiWindowFlags_HorizontalScrollbar ;
	
	if (inicio!=NULL)
	{
				
		if (MULTI_VIEW && MOSAICO==false)
			{
				temp=indice;
				indice=inicio;
				while (indice!=NULL)
					{	
						count++;
						no = std::to_string(count);
						header=head+no;		
						
							ImGui::SetNextWindowSize(ImVec2(indice->objeto.ancho, indice->objeto.alto),  0);
							ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
							if (ImGui::IsItemClicked()) 
							{
								temp=indice;					
							}
																												
							float x =( ImGui::GetWindowSize().x - (float)(indice->objeto.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->objeto.alto))/2.0f; //draws grid correctly							
    						ImVec2 imagePosition(x, y);
    						ImGui::SetCursorPos(imagePosition);														
							
							ImGui::Image(indice->objeto.texturecapa , ImVec2((float)(indice->objeto.ancho), (float)(indice->objeto.alto)) );
							if (ImGui::IsItemHovered())
									{
										cursor_brocha.refresh ();
										cursor_brocha.circle();
									}
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
					if (MOSAICO==true)
					{						
						temp=indice;
						indice=inicio;
						count++;
						no = std::to_string(count);
						header=head+no;	
						ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
						if (ImGui::IsItemClicked()) 
							{
								temp=indice;					
							}
						while (indice!=NULL)
							{		
								//float x =( ImGui::GetWindowSize().x - (float)(indice->objeto.ancho))/2.0f; //draws grid correctly
								//float y =( ImGui::GetWindowSize().y - (float)(indice->objeto.alto))/2.0f; //draws grid correctly							
    							//ImVec2 imagePosition(x, y);
									ImGui::Image(indice->objeto.texturecapa , ImVec2((float)(indice->objeto.ancho), (float)(indice->objeto.alto)) );
									if (ImGui::IsItemHovered())
									{
										cursor_brocha.refresh ();
										cursor_brocha.circle();
										
									}
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
							if (ImGui::IsItemClicked()) 
							{
								temp=indice;					
							}
							
							float x =( ImGui::GetWindowSize().x - (float)(indice->objeto.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->objeto.alto))/2.0f; //draws grid correctly
							float aspecto=x/y;
		    				ImVec2 imagePosition(x, y);
		    				ImGui::SetCursorPos(imagePosition);    				
							ImGui::Image( indice->objeto.texturecapa , ImVec2( (float)(indice->objeto.ancho), (float)(indice->objeto.alto) ) );
							if (ImGui::IsItemHovered())
									{
										cursor_brocha.refresh ();
										cursor_brocha.circle();
									}
							
							ImGui::End();			
							ImGui::Text(indice->nombre.c_str());
						}					
				}				
	}
}

void Capasimgui::despliega_viewer_pinta (float radio,SDL_Color color)
{
	nodo *temp;
	int count=0;
	std::string head="capasViewer-";
	std::string no;
	std::string header;
	
	ImGuiWindowFlags window_renderer_to_imgui = 0 | ImGuiWindowFlags_HorizontalScrollbar ;
	
	if (inicio!=NULL)
	{
				
		if (MULTI_VIEW && MOSAICO==false)
			{
				temp=indice;
				indice=inicio;
				while (indice!=NULL)
					{	
						count++;
						no = std::to_string(count);
						header=head+no;		
						
							ImGui::SetNextWindowSize(ImVec2(indice->objeto.ancho, indice->objeto.alto),  0);
							ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
							if (ImGui::IsItemClicked()) 
							{
								temp=indice;
								
							}
							
																												
							float x =( ImGui::GetWindowSize().x - (float)(indice->objeto.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->objeto.alto))/2.0f; //draws grid correctly							
    						ImVec2 imagePosition(x, y);
    						ImGui::SetCursorPos(imagePosition);														
							
							ImVec2 pintura=ImGui::GetCursorScreenPos();
							ImGui::Image(indice->objeto.texturecapa , ImVec2((float)(indice->objeto.ancho), (float)(indice->objeto.alto)) );
							
							if (ImGui::IsItemHovered())
									{
										cursor_brocha.refresh ();
										cursor_brocha.circle();
										if (SDL_IO::SDL_Click_L)
										{												
											int px=cursor_brocha.pos.x-pintura.x;
											int py=cursor_brocha.pos.y-pintura.y;
											Capaext::circulo_relleno_a_capa (indice->objeto.rtdata,indice->objeto.ancho_real,indice->objeto.alto_real,&px,&py,&color,&radio);
											Capaext::capa_a_texturab (&indice->objeto.rtdata,indice->objeto.ancho_real,indice->objeto.alto_real,&indice->objeto.texturecapa);
										}
									}
							
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
					if (MOSAICO==true)
					{						
						temp=indice;
						indice=inicio;
						count++;
						no = std::to_string(count);
						header=head+no;	
						ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
							
						if (ImGui::IsItemClicked()) 
							{
								temp=indice;					
							}
						while (indice!=NULL)
							{		
								//float x =( ImGui::GetWindowSize().x - (float)(indice->objeto.ancho))/2.0f; //draws grid correctly
								//float y =( ImGui::GetWindowSize().y - (float)(indice->objeto.alto))/2.0f; //draws grid correctly							
    							//ImVec2 imagePosition(x, y);
								ImVec2 pintura=ImGui::GetCursorScreenPos();
								ImGui::Image(indice->objeto.texturecapa , ImVec2((float)(indice->objeto.ancho), (float)(indice->objeto.alto)) );
								
								if (ImGui::IsItemHovered())
								{
									cursor_brocha.refresh ();
									cursor_brocha.circle();
									if (SDL_IO::SDL_Click_L)
									{											
										int px=cursor_brocha.pos.x-pintura.x;
										int py=cursor_brocha.pos.y-pintura.y;
										Capaext::circulo_relleno_a_capa (indice->objeto.rtdata,indice->objeto.ancho_real,indice->objeto.alto_real,&px,&py,&color,&radio);
										Capaext::capa_a_texturab (&indice->objeto.rtdata,indice->objeto.ancho_real,indice->objeto.alto_real,&indice->objeto.texturecapa);
									}
								}
							
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
							
							if (ImGui::IsItemClicked()) 
							{
								temp=indice;					
							}
							
							float x =( ImGui::GetWindowSize().x - (float)(indice->objeto.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->objeto.alto))/2.0f; //draws grid correctly
							float aspecto=x/y;
		    				ImVec2 imagePosition(x, y);
		    				ImGui::SetCursorPos(imagePosition);
		    				ImVec2 pintura=ImGui::GetCursorScreenPos();
							ImGui::Image( indice->objeto.texturecapa , ImVec2( (float)(indice->objeto.ancho), (float)(indice->objeto.alto) ) );
							if (ImGui::IsItemHovered())
								{
									cursor_brocha.refresh ();
									cursor_brocha.circle();
									if (SDL_IO::SDL_Click_L)
									{											
										int px=cursor_brocha.pos.x-pintura.x;
										int py=cursor_brocha.pos.y-pintura.y;
										Capaext::circulo_relleno_a_capa (indice->objeto.rtdata,indice->objeto.ancho_real,indice->objeto.alto_real,&px,&py,&color,&radio);
										Capaext::capa_a_texturab (&indice->objeto.rtdata,indice->objeto.ancho_real,indice->objeto.alto_real,&indice->objeto.texturecapa);
									}
								}
							
							ImGui::End();			
							ImGui::Text(indice->nombre.c_str());
						}					
				}				
	}
}

void Capasimgui::rellena (ImVec4 *color)
{
	
	if (indice!=NULL)
	{
		if (indice->objeto.rtdata!=NULL) free(indice->objeto.rtdata);
		
			
			indice->objeto.rtdata = (unsigned char*) malloc(indice->objeto.ancho_real * indice->objeto.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->objeto.ancho_real*indice->objeto.alto_real*4;i+=4)
		    {
		    	*(indice->objeto.rtdata+i)=(Uint8)(color->x*255);
		    	*(indice->objeto.rtdata+i+1)=(Uint8)(color->y*255);
		    	*(indice->objeto.rtdata+i+2)=(Uint8)(color->z*255);
		    	*(indice->objeto.rtdata+i+3)=(Uint8)(color->w*255);
		    	if (idx<=indice->objeto.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->objeto.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->objeto.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->objeto.ancho_real, indice->objeto.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->objeto.rtdata);
		
	}
	
}

void Capasimgui::rellena (SDL_Color *color)
{
	
	if (indice!=NULL)
	{
		if (indice->objeto.rtdata!=NULL) free(indice->objeto.rtdata);
		
			
			indice->objeto.rtdata = (unsigned char*) malloc(indice->objeto.ancho_real * indice->objeto.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->objeto.ancho_real*indice->objeto.alto_real*4;i+=4)
		    {
		    	*(indice->objeto.rtdata+i)=(Uint8)(color->r);
		    	*(indice->objeto.rtdata+i+1)=(Uint8)(color->g);
		    	*(indice->objeto.rtdata+i+2)=(Uint8)(color->b);
		    	*(indice->objeto.rtdata+i+3)=(Uint8)(color->a);
		    	if (idx<=indice->objeto.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->objeto.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->objeto.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->objeto.ancho_real, indice->objeto.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->objeto.rtdata);
		
	}
	
}


void Capasimgui::pixel (int x,int y,ImVec4 *color)
{
	
	if (indice!=NULL)
	{
		if (indice->objeto.rtdata!=NULL) 
		{
		
			
			float degradado=1;
			int idx=0;
		    int i=(indice->objeto.ancho_real*y)+x;
		    
	    	*(indice->objeto.rtdata+i)=(Uint8)(color->x*255);
	    	*(indice->objeto.rtdata+i+1)=(Uint8)(color->y*255);
	    	*(indice->objeto.rtdata+i+2)=(Uint8)(color->z*255);
	    	*(indice->objeto.rtdata+i+3)=(Uint8)(color->w*255);		    	
			
			glGenTextures(1, &indice->objeto.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->objeto.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->objeto.ancho_real, indice->objeto.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->objeto.rtdata);
		}
		
	}
	
}

void Capasimgui::pixel (int x,int y,SDL_Color *color)
{
	
	if (indice!=NULL)
	{
		if (indice->objeto.rtdata!=NULL) 
		{
		
			
			float degradado=1;
			int idx=0;
		    int i=(indice->objeto.ancho_real*y)+x;
		    
	    	*(indice->objeto.rtdata+i)=(Uint8)(color->r);
	    	*(indice->objeto.rtdata+i+1)=(Uint8)(color->g);
	    	*(indice->objeto.rtdata+i+2)=(Uint8)(color->b);
	    	*(indice->objeto.rtdata+i+3)=(Uint8)(color->a);		    	
			
			glGenTextures(1, &indice->objeto.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->objeto.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->objeto.ancho_real, indice->objeto.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->objeto.rtdata);
		}
		
	}
	
}

void Capasimgui::SelectAll(void)
{
	nodo *temp;	
	
	if (indice!=NULL)
	{
		if (SELECTALL==true) 
			SELECTALL=false; else SELECTALL=true;
		temp=indice;
		
		indice=inicio;
		while (indice!=NULL)
		{	
			
			indice->seleccionado=SELECTALL;
			indice=indice->siguiente;
		}
		
		if (temp!=NULL)
			indice=temp;
			else indice=NULL;
	}
}