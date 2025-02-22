#pragma once

#include <NUCLEO/INTERFACE SDL/ventanaSDL.h>

class rendererSDL:public ventanaSDL
	{		
		public:
		SDL_Renderer *renderer;
	};