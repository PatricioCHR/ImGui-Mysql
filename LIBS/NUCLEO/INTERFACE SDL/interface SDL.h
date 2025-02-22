#include <NUCLEO/INTERFACE SDL/rendererSDL.h>

namespace interfaceSDL
{
	
	void inicializa_interface(rendererSDL *w,char *nombre)
	{
	    int rendererFlags, windowFlags;
	    
	    w->nombre=nombre;
	
	    rendererFlags = SDL_RENDERER_ACCELERATED;
	
	    windowFlags = 0;
	
	    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	    {
	        printf("Falla al inicializar SDL: %s\n", SDL_GetError());
	        interfaceNUCLEO::START=false;
	    }
	    
	    SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		
		w->ancho=DM.w*0.8;
		w->alto=DM.h*0.8;
	    
		w->ventana = SDL_CreateWindow(w->nombre, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w->ancho , w->alto , windowFlags);    
	    
		    
	    if (!w->ventana)
	    {
	        printf("Falla al abrir %d x %d ventana : %s\n", w->ancho , w->alto , SDL_GetError());
	        interfaceNUCLEO::START=false;
	    }    
	    
	    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	
	    w->renderer = SDL_CreateRenderer(w->ventana, -1, rendererFlags);
	    
	    if (!w->renderer)
	    {
	        printf("Falla al crear el renderer : %s\n", SDL_GetError());
	        interfaceNUCLEO::START=false;
	    }
	    
	    FILES::inicializa_loadSDLTexture();
	    
	}	
	
	void destruye_interface(rendererSDL *w)
	{
		SDL_DestroyRenderer(w->renderer);
		SDL_DestroyWindow(w->ventana);
	}	
	
	void preparaRenderizado(rendererSDL *w)
	{
	    SDL_SetRenderDrawColor(w->renderer, 96, 128, 255, 255);
	    SDL_RenderClear(w->renderer);	    
	}
	
	void renderizaEscena(rendererSDL *w)
	{
	    SDL_RenderPresent(w->renderer);	    
	    
	}
	
	
	
	

	void blit(SDL_Renderer *renderer,SDL_Texture *texture, int x, int y)
	{
	    SDL_Rect dest;
	
	    dest.x = x;
	    dest.y = y;
	    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	    SDL_RenderCopy(renderer, texture, NULL, &dest);
	}
	
}