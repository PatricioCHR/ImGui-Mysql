
#include <iostream>
#include <ctime>
#include <chrono>


int autoid=0;
bool generacion_automatica = false;

//#define SDL ,EDITOR_IMGUI, IMGUI_OPENGL2   ELIJA LA TECNOLOGIA GRAFICA A UTILIZAR
#define IMGUI_OPENGL2
#define MULTIVIEWPORTIMGUI

//#define SDL2

bool DOCK=true;

char *arr = new char [200];

char *arrkey = new char [30000];
int sizekey=32;
std::string key="";

//#define PLATAFORMA, IMGUI_DEMO
#define PLATAFORMA
//#define IMGUI_DEMO
#define DEBUG
#define EDITOR_IMGUI

/************************************** Seccion de mysql connection *********************************/

#define EXAMPLE_HOST "localhost"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS ""
#define EXAMPLE_DB "test"

/****************************************************************************************************/

#include <NUCLEO/INTERFACE NUCLEO/carga tecnologia.h>

#include <mysql.h>
#include <mysqld_error.h>

#include "data_bases.h"

#ifdef main
#undef main
#endif /* main */

std::string datainput="";
std::string dataoutput="";
std::string cabecera="CHAR  ASCII  HEX";

std::string filePathName;
std::string filePath;

char *calign=new char [200];

//std::string arr{};

Capa capa1;
GLuint texturecapa=0;

Capa capaout;
GLuint texturecapaout=0;


bool MAXIMIZAR=false;
bool MAXIMIZAR2=false;

void ventana_de_encriptado (void);
void init_key_generator (void);
void genera_llave_f (void);
void genera_llave (void);
void encripta_string (std::string mensaje, std::string xkey , int szkey );
void encripta_imagen (void);
void encripta_byte (char *byte, char *key);
void desencripta_byte (char *byte,char *key);


void Abrir_Archivo (void);
void ventana_de_encriptado (void);

void enviar_string (void);
void enviar_imagen (void);

MYSQL obj;

double keytimetoborn=0;
double timetoupload=0;
  
int main(int, char**)
{
	
	char dbas[100]="cubiq_qkd_simulator";
	char host[300]="localhost";
	char user[100]="CUbIQ";
	char pass[100]="Luis130374.";
	int port=0;

	char nombredeventana[]="QKD Simulator Grafana";
	
	init_key_generator ();
	
		
	if (mysql_connection (&obj,host,user,pass,dbas,port))
	{
		printf ("Base de datos inicializada !\n");
	} else
		{
			printf ("Base de datos no inicializada !\n");
		}
	
#if defined(IMGUI_OPENGL2)
	ventanaIMGUI ventanamain;	
	ventanamain.io=interfaceIMGUI::inicializa_interface(&ventanamain,nombredeventana);  
#endif	

    while (interfaceNUCLEO::START==true)
    {        
    	autoid=0;
    	SDL_IO::Input_Keyboard( ventanamain.ventana );
    	
    	//  Inicializan preparativos para renderizar    	
				#if defined(IMGUI_OPENGL2)					
				        interfaceIMGUI::preparaRenderizado (&ventanamain);				        
				#endif		
				
		// Fin de preparativos para renderizar
		/************************************************************************************************/				
				//Inicio de Aplicaciones
				
				
				ventana_de_encriptado ();
				
				select_data_base (&autoid,&obj,host,user,pass,dbas,&port);
				
				if (generacion_automatica == true){
					genera_llave();
					write_database (&obj,arrkey,sizekey);
				}

					
				
				//Fin de Aplicaciones
		/************************************************************************************************/
				
		// Renderizado la escena		
		
			#if defined(IMGUI_OPENGL2)	
					
			    interfaceIMGUI::renderizaEscena(&ventanamain);
			    
			#endif		
		//Fin de renderizado


    }
    

#if defined(IMGUI_OPENGL2)
    interfaceIMGUI::destruye_interface(&ventanamain);    
#endif	


    return 0;
}


void ventana_de_encriptado (void)
{
	ImGui::Begin("Input DATA");	
		
		ImGui::Begin("Mensaje");							
														
			sprintf(calign, "%s :","Mensaje");
			ImGui::Text(calign);
			ImGui::SameLine();
			
			autoid++;
			ImGui::PushID(autoid);    
			if (ImGui::InputText("##", arr , 200))
			   	{				   		
					
			   	};							
			ImGui::PopID();
			ImGui::Separator();
			Abrir_Archivo ();    				
			ImGui::SameLine ();
			
			if (ImGui::Button("Enviar")) 
				{
					if (arr[0]!=0)
						{
							enviar_string ();
							arr[0]=0;
						}
					if (texturecapa!=0)
						{
							enviar_imagen ();
						}
				}
				
		ImGui::End();
					
						ImGui::Separator();
						
						sprintf(calign, "%s%6s","Llave para encriptar",":");
						ImGui::Text(calign);
											
						sprintf(calign, "%s%2s","Medida de llave en Bytes",":");
						ImGui::Text(calign);
						ImGui::SameLine();
						
						autoid++;
						ImGui::PushID(autoid);    
    					if (ImGui::InputInt("##", &sizekey , 5))
						   	{				   		
								
						   	};							
						ImGui::PopID();
						
						sprintf(calign, "%s%21s","Llave",":");
						ImGui::Text(calign);
						ImGui::SameLine();
						autoid++;
						
						ImGui::PushID(autoid);    
    					if (ImGui::InputText("##", arrkey , sizekey))
						   	{				   		
								
						   	};							
						ImGui::PopID();
						
						if (ImGui::Button("Generar Key"))
						{
							genera_llave ();
							write_database (&obj,arrkey,sizekey);
						}
						
						if (ImGui::Button("Automatic Generator Key"))
						{
							if (generacion_automatica == true){
								generacion_automatica = false;
							}else{
								generacion_automatica = true;
							}
						}

						
						ImGui::Separator();
    				
	    				ImGui::BeginChild("datos");
	    				
	    				ImGui::Text(datainput.c_str());
					   	
					   	if (texturecapa!=0)
					   	{
					   		ImGui::Image( texturecapa, ImVec2(50,50) );
					   		ImGui::SameLine ();		    				
		    				if (ImGui::Button("Maximizar"))
		    				{
		    					MAXIMIZAR=true;
							}					   							   		
						}
						
						if (MAXIMIZAR==true)
						{						
							ImGuiWindowFlags window_renderer_to_imgui = 0 | ImGuiWindowFlags_HorizontalScrollbar ;
							ImGui::Begin("Visor de Imagenes",NULL,window_renderer_to_imgui);
			    				ImGui::Image( texturecapa, ImVec2(capa1.ancho_real,capa1.alto_real) );
			    				
			    				ImGui::Begin("Panel");
				    				if (ImGui::Button("Minimizar"))
					    				{
					    					MAXIMIZAR=false;
										}
								ImGui::End();
								
			    			ImGui::End();
			    			
		    			}
		    			
		    			if (MAXIMIZAR2==true)
						{						
							ImGuiWindowFlags window_renderer_to_imgui = 0 | ImGuiWindowFlags_HorizontalScrollbar ;
							ImGui::Begin("Visor de Imagenes Encriptado",NULL,window_renderer_to_imgui);
			    				ImGui::Image( texturecapaout , ImVec2(capa1.ancho_real,capa1.alto_real) );
			    				
			    				ImGui::Begin("Panel2");
				    				if (ImGui::Button("Minimizar2"))
					    				{
					    					MAXIMIZAR2=false;
										}
								ImGui::End();
								
			    			ImGui::End();
			    			
		    			}
    					
    					ImGui::EndChild();
    				
						
    				ImGui::End();
    				
    				
    				ImGui::Begin("Algoritmo DATA");

    				ImGui::Text("Textbox");

    				ImGui::End();
    				
    				/********************* Visor de informacion **************************/
    				
    				ImGui::Begin("Output DATA");
    				
	    				ImGui::Text(cabecera.c_str());
	    				
	    				ImGui::Separator();
	    				
						ImGui::BeginChild("vdd1");
	    					ImGui::Text(dataoutput.c_str());
	    					
	    					if (texturecapaout!=0)
						   	{
						   		ImGui::Image( texturecapaout, ImVec2(50,50) );
						   		ImGui::SameLine ();		    				
			    				if (ImGui::Button("Maximizar2"))
			    				{
			    					MAXIMIZAR2=true;
								}					   							   		
							}
	    				ImGui::EndChild();
	    				
	    				//ImGui::BeginChild("vdd2");
	    					
	    				//ImGui::EndChild();

    				ImGui::End();    							
					   
}



void Abrir_Archivo (void)
{ 
  // open Dialog Simple
  if (ImGui::Button("Abrir Imagen"))
    ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".jpg,.png");

  // display
  if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
  {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk())
    {
      filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
      filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
      
      if (Capaext::carga_capa(filePathName.c_str(),&capa1.rtdata,&capa1.ancho_real,&capa1.alto_real))
      {
      	printf ("Capa en memoria cargada con exito !!\n");
      	Capaext::capa_a_textura (capa1.rtdata,capa1.ancho_real,capa1.alto_real,&texturecapa);
	  }
      
                  
      // action
    }
    
    // close
    ImGuiFileDialog::Instance()->Close();
  }
}




void enviar_string (void)
{
	int ikey=0;
	char *stringnew=new char [250];
	char *stringnew2=new char [250];
	char code;
	
	std::string datos(arr);
	std::string str2(arr);
	
	datainput+=str2+"\n";
		
	for (int ciclo=0;ciclo<datos.size();ciclo++)
	{		
		if (key!="")
		{
			code=key[ikey];
			encripta_byte (&arr[ciclo],&code);
			ikey++;
			if (ikey==sizekey)
			{
				ikey=0;
			}
		}
		sprintf(stringnew, "%2c %6d %6X\n",arr[ciclo],arr[ciclo],arr[ciclo]);		
		std::string str(stringnew);		
		dataoutput+=str;		
	}
}

void enviar_imagen (void)
{
	int ikey=0;
	int idato;
	char code;
	capaout.ancho_real=capa1.ancho_real;
	capaout.alto_real=capa1.alto_real;	
	capaout.ancho=capa1.ancho;
	capaout.alto=capa1.alto;	
		
	Capaext::redimenciona (&capaout.rtdata,capaout.ancho_real,capaout.alto_real,4);		
	//Capaext::copia_capa (capa1.rtdata,capaout.rtdata,capaout.alto_real*capaout.ancho_real*4);
	int bytes =capaout.alto_real*capaout.ancho_real*4;	
	
	for (int i=0;i<bytes;i++)
	    {
	    	if (key!="")
			{
				code=key[ikey];	
				
				ikey+=1;
				if (ikey==sizekey)
				{
					ikey=0;
				}
			}
	    	idato=*(capa1.rtdata+i)+code;
	    	if (idato>255)
	    	{
	    		idato-=255;
			}
			
	    	*(capaout.rtdata+i)=(char)idato;
	    	
		}
		
	if (key!="")
	{
	
		bytes =capaout.alto_real*capaout.ancho_real*4;	
		ikey=0;
		for (int pasos=0;pasos<10;pasos++)	
		{	
			for (int i=0;i<bytes;i+=4)
			    {
			    	if (key!="")
					{
						code=key[ikey];	
						
						ikey+=1;
						if (ikey==sizekey)
						{
							ikey=0;
						}
					}
					if ((i+1)%2)
			    		idato=(int)(*(capa1.rtdata+i))*code*20;
			    	else
			    		idato=(int)(*(capa1.rtdata+i))*code*20;
			    				
			    	*(capaout.rtdata+i)=idato;
			    	
				}
		}
	}
	
	Capaext::capa_a_textura (capaout.rtdata,capaout.ancho_real,capaout.alto_real,&texturecapaout);
}



void init_key_generator (void)
{
	arr[0]=0;
	arrkey[0]=0;
}

void encripta_byte (char *byte, char *key)
{
	int ibyte;
	int ikey;
	int ires;
	
	ibyte=*byte;
	ikey=*key;
	
	ires=ibyte+ikey;
	
	if (ires>255)
	{
		ires=ires-255;
	}
	
	*byte=(char) ires;
		
}

void desencripta_byte (char *byte,char *key)
{
	int ibyte;
	int ikey;
	int ires;
	
	ibyte=*byte;
	ikey=*key;
	
	ires=ibyte-ikey;
	
	if (ires<0)
	{
		ires=ires+255;
	}
	
	*byte=(unsigned char) ires;
		
}

static const char alphanum[] =		//Caracteres permitidos en la encriptacion
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
		".,;:!#$%&/()?¡{}~`^+-";

inline void genera_llave_f (void)
{		
	int ciclo=0;
	int d=0;
	key="";	
	for (ciclo=0;ciclo<sizekey;ciclo++)
	{
		d=alphanum[rand() % (sizeof(alphanum) - 1)];
		arrkey[ciclo]=d;
		key+=std::to_string(d);		
		printf ("%5c   %d\n",d,d);
	}
	arr[ciclo]=0;
}

 
void genera_llave (void)
{
	
	auto t0 = Time::now();
	
	genera_llave_f ();
			
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);  	    
    printf("time to born %d ms\n",d.count() );
    keytimetoborn=fs.count();
    printf("Time to born %e s\n", keytimetoborn);
}


void encripta_string (std::string mensaje, std::string xkey , int szkey )
{
	int ikey=0;	
	int byte=0;
	
	for (int i=0;i<mensaje.size();i++)
	{
		byte=(int)mensaje[i];
		printf ("%d\n",byte);
	}
}

void encripta_imagen (void)
{
}






