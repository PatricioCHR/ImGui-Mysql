namespace Menu
{
	char texturas_de_juego[][100]={
								"recursos/iconos/add.png",
								"recursos/iconos/min.png",
								"recursos/iconos/carga.png",
								"recursos/iconos/graba.png",
								"recursos/iconos/selectall.png",
								"recursos/iconos/borrar.png",								
								"recursos/iconos/candadocerrado.png",
								"recursos/iconos/candadoabierto.png",
								"recursos/iconos/linea.png",
								"recursos/iconos/curva.png",
								"recursos/iconos/rectangulo.png"
								
							};


	SDL_Texture **lista_de_texturas;
	int elementos;

	void inicializa_texturas (void)
	{		
		elementos=sizeof(texturas_de_juego)/sizeof(texturas_de_juego[0]);
						
		lista_de_texturas=new SDL_Texture* [elementos];
						
		for (int index=0;index<elementos;index++)
			{				
				lista_de_texturas[index] = interface::loadTextura(interface::ventanaSDL.renderer,texturas_de_juego[index]);				
			}			
		
	}
	
	void render_texturas (void)
	{
						
		for (int index=0;index<elementos;index++)
		{
			interface::blit(interface::ventanaSDL.renderer,lista_de_texturas[index],120*(index+1),20);
		}
		
	}	
	
	
	void destruye_texturas (void)
	{
		
		for (int index=0;index<elementos;index++)
		{
			SDL_DestroyTexture( lista_de_texturas[index] );
    		lista_de_texturas[index] = NULL;	
		}
		
		delete [] lista_de_texturas;
	}

}