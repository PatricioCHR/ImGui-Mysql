#pragma once

class Brocha
{
	public:
	float radio=1.0;
	SDL_Color color = {255, 0, 0,255};
		
    SDL_Texture *texture=0;
    Capas texturas;
    
    Brocha ();
	~Brocha ();
};

Brocha::Brocha()
{	
	
}

Brocha::~Brocha ()
{
	if (texture)
	{
		SDL_DestroyTexture( texture );
		texture = NULL;	
		printf ("Textura destruida \n");
	}	
	texturas.~Capas();
}