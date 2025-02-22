#include <SDL2/SDL_image.h>

namespace FILES
{
	void inicializa_loadSDLTexture (void)
	{
		int imgFlags = IMG_INIT_PNG;
	
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
			printf( "SDL_image no puede ser inicializado : %s\n", IMG_GetError() );
			interfaceNUCLEO::START=false;
		}    
	}
	
	SDL_Texture *loadSDLTexture( SDL_Renderer *renderer,char *filename)
	{   
	    SDL_Texture *texture=NULL;	    
		texture = IMG_LoadTexture(renderer, filename);	         
	    if( texture == NULL )
	    {
	        printf( "Falla al  cargar la imagen ! %s \n",filename );
	        interfaceNUCLEO::START=false;	        
	    }	
	    return texture;
	}
	
	SDL_Texture *loadTextura( SDL_Renderer *renderer,char *filename ,int *ancho, int *alto)
	{   
	    SDL_Texture *texture=NULL;	    
		texture = IMG_LoadTexture(renderer, filename);	         
	    if( texture == NULL )
	    {
	        printf( "Falla al  cargar la imagen ! %s \n",filename );
	        interfaceNUCLEO::START=false;
	        
	    } else
	    	{
	    		SDL_QueryTexture(texture, NULL, NULL, ancho, alto);
			}	
	    return texture;
	}
	
}