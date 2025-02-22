#include  "interfaceNUCLEO.h"

//Si nuestro programa usa la librería SDL.h, hacen falta: SDL.dll
//Si usamos SDL_image.h necesitaremos jpeg.dll, libpng12.dll, libtiff.dll, zlib1.dll y SDL_image.dll

#if defined(IMGUI_OPENGL2)

	//-lSDL2
	//-lSDL2main
	//-lSDL2_image	
	//-lopengl32
	//-Iimgui

	
	#include <SDL2/SDL.h>	  
	#include <SDL_opengl.h>	
		
	#include "imgui.h"
	#include "imgui_impl_sdl2.h"
	#include "imgui_impl_opengl2.h"				
	
	#define STB_IMAGE_IMPLEMENTATION
	#define STBI_MSC_SECURE_CRT
	#define STB_IMAGE_WRITE_IMPLEMENTATION
	
	#include "STB-MASTER/stb_image.h"
	#include "STB-MASTER/stb_image_write.h"
	#include "IMAGENLOADERS/ImagenLoaders.h"
	
	#include <NUCLEO/INTERFACE IMGUI/cursor_IMGUI.h>
	
	cursor_imgui cursor_brocha;
	
	#include <NUCLEO/INTERFACE SDL/rendererSDL.h>
	#include <NUCLEO/INTERFACE IMGUI/ventanaIMGUI.h>
	
	#include "NUCLEO/INTERFACE IMGUI/dockspace.h"
	#include "NUCLEO/FILES/files.h"	
	
	#include <NUCLEO/INTERFACE IMGUI/interface IMGUI.h>	
	
	#include "imguifiledialog.h"
	#include <NUCLEO/INTERFACE SDL/input.h>
	
	#include <NUCLEO/EDITOR IMGUI/MENU BAR.h>
	
	#include <NUCLEO/INTERFACE NUCLEO/CAPAS/capaext.h>
	#include <NUCLEO/INTERFACE NUCLEO/CAPAS/capa.h>
	#include <NUCLEO/INTERFACE NUCLEO/CAPAS/capas.h>
	#include <NUCLEO/INTERFACE NUCLEO/CAPAS/capasimgui.h>
	//#include <NUCLEO/INTERFACE SDL/texturaSDL.h>	
	//#include <NUCLEO/INTERFACE SDL/sprite.h>

		
#endif



/* Nucleo Rutinas compatibles con cualquier tecnologia grafica */


/* Nucleo Rutinas compatibles con cualquier tecnologia grafica */

#if defined(IMGUI_OPENGL2)
		
			
#endif
