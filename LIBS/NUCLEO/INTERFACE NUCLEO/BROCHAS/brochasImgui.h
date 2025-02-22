#include "brochas.h"

class Brochasimgui : public Brochas
{
	public:
	bool SELECTALL=false;	
	bool MULTI_VIEW=true;
	bool PROPORCIONES=true;
	bool MOSAICO=false;
	
	Brochasimgui ();
	~Brochasimgui ();
	
	void SelectAll(void);
	//void redimenciona_todos (int ancho,int alto);
	//void redimenciona_todos_los_seleccionados (int ancho,int alto);
	void despliega(void);
	
};

Brochasimgui::Brochasimgui()
{
	
}

Brochasimgui::~Brochasimgui()
{
	
	
}

void Brochasimgui::despliega(void)
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

void Brochasimgui::SelectAll(void)
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



/*
void Brochas::redimenciona_todos (int ancho,int alto)
{
	nodo *temp;
	
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		
			indice->nodo.alto=alto;
			indice->nodo.ancho=ancho;
				
		indice=indice->siguiente;
	}
	
	if (temp!=NULL)
		indice=temp;
		else indice=NULL;
}*/

/*

void Brochas::redimenciona_todos_los_seleccionados (int ancho,int alto)
{
	nodo *temp;
	
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		if (indice->seleccionado)
		{
			indice->nodo.alto=alto;
			indice->nodo.ancho=ancho;
		}
		
		indice=indice->siguiente;
	}
	
	if (temp!=NULL)
		indice=temp;
		else indice=NULL;
}
*/


/*
void Brochas::redimenciona (int gancho,int galto,ImVec4 color)
{
	if (indice!=NULL)
	{
		if (indice->nodo.rtdata!=NULL) free(indice->nodo.rtdata);
		
			
			indice->nodo.ancho_real=gancho;
			indice->nodo.alto_real=galto;
			
			indice->nodo.rtdata = (unsigned char*) malloc(indice->nodo.ancho_real * indice->nodo.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->nodo.ancho_real*indice->nodo.alto_real*4;i+=4)
		    {
		    	*(indice->nodo.rtdata+i)=(Uint8)(color.x*255);
		    	*(indice->nodo.rtdata+i+1)=(Uint8)(color.y*255);
		    	*(indice->nodo.rtdata+i+2)=(Uint8)(color.z*255);
		    	*(indice->nodo.rtdata+i+3)=(Uint8)(color.w*255);
		    	if (idx<=indice->nodo.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->nodo.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->nodo.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->nodo.ancho_real, indice->nodo.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->nodo.rtdata);
		
	}
}
*/

/*
void Brochas::redimenciona (int gancho,int galto,SDL_Color color_de_capa)
{
	if (indice!=NULL)
	{
		if (indice->nodo.rtdata!=NULL) free(indice->nodo.rtdata);
		
			
			indice->nodo.ancho_real=gancho;
			indice->nodo.alto_real=galto;
			
			indice->nodo.rtdata = (unsigned char*) malloc(indice->nodo.ancho_real * indice->nodo.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->nodo.ancho_real*indice->nodo.alto_real*4;i+=4)
		    {
		    	*(indice->nodo.rtdata+i)=(Uint8)(color.r);
		    	*(indice->nodo.rtdata+i+1)=(Uint8)(color.g);
		    	*(indice->nodo.rtdata+i+2)=(Uint8)(color.b);
		    	*(indice->nodo.rtdata+i+3)=(Uint8)(color.a);
		    	if (idx<=indice->nodo.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->nodo.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->nodo.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->nodo.ancho_real, indice->nodo.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->nodo.rtdata);
		
	}
}
*/

/*
void Brochas::despliega_viewer(void)
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
						
							ImGui::SetNextWindowSize(ImVec2(indice->nodo.ancho, indice->nodo.alto),  0);
							ImGui::Begin(header.c_str(),NULL,window_renderer_to_imgui);
																												
							float x =( ImGui::GetWindowSize().x - (float)(indice->nodo.ancho))/2.0f; //draws grid correctly
							float y =( ImGui::GetWindowSize().y - (float)(indice->nodo.alto))/2.0f; //draws grid correctly							
    						ImVec2 imagePosition(x, y);
    						//ImGui::SetCursorPos(imagePosition);														
							
							ImGui::Image(indice->nodo.texturecapa , ImVec2((float)(indice->nodo.ancho), (float)(indice->nodo.alto)) );
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
						while (indice!=NULL)
							{		
								//float x =( ImGui::GetWindowSize().x - (float)(indice->capa.ancho))/2.0f; //draws grid correctly
								//float y =( ImGui::GetWindowSize().y - (float)(indice->capa.alto))/2.0f; //draws grid correctly							
    							//ImVec2 imagePosition(x, y);
									ImGui::Image(indice->nodo.texturecapa , ImVec2((float)(indice->nodo.ancho), (float)(indice->nodo.alto)) );
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
							ImGui::Image( indice->nodo.texturecapa , ImVec2( (float)(indice->nodo.ancho), (float)(indice->nodo.alto) ) );
							
							ImGui::End();			
							ImGui::Text(indice->nombre.c_str());
						}
					
					
				}
				
	}
}

*/

/*
void Brochas::rellena (ImVec4 *color)
{
	
	if (indice!=NULL)
	{
		if (indice->nodo.rtdata!=NULL) free(indice->nodo.rtdata);
		
			
			indice->nodo.rtdata = (unsigned char*) malloc(indice->nodo.ancho_real * indice->nodo.alto_real * 4);   
			
			float degradado=1;
			int idx=0;
		    for (int i=0;i<indice->nodo.ancho_real*indice->nodo.alto_real*4;i+=4)
		    {
		    	*(indice->nodo.rtdata+i)=(Uint8)(color->x*255);
		    	*(indice->nodo.rtdata+i+1)=(Uint8)(color->y*255);
		    	*(indice->nodo.rtdata+i+2)=(Uint8)(color->z*255);
		    	*(indice->nodo.rtdata+i+3)=(Uint8)(color->w*255);
		    	if (idx<=indice->nodo.ancho_real)
		    	{} else
					{
		    			idx=0;
		    			degradado=+0.01f;
					}
				idx++;
		    	
			}	
			glGenTextures(1, &indice->nodo.texturecapa);
			glBindTexture(GL_TEXTURE_2D, indice->nodo.texturecapa);		
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, indice->nodo.ancho_real, indice->nodo.alto_real, 0, GL_RGBA, GL_UNSIGNED_BYTE, indice->nodo.rtdata);
		
	}
	
}*/

/*
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
	
}*/

/*
void Brochas::pixel (int x,int y,ImVec4 *color_de_capa)
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
	
}*/

/*
void Brochas::pixel (int x,int y,SDL_Color *color)
{
	
	if (indice!=NULL)
	{
		if (indice->nodo.Texturas->indice.rtdata!=NULL) 
		{
		
			
			float degradado=1;
			int idx=0;
		    int i=(indice->nodo.Texturas->capa.ancho_real*y)+x;
		    
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
	
}*/

	