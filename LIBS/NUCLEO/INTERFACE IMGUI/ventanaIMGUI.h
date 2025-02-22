#pragma once

#include <NUCLEO/INTERFACE SDL/ventanaSDL.h>

class ventanaIMGUI:public rendererSDL
{
	public:	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	SDL_GLContext gl_context;	
	ImGuiIO io;
};


