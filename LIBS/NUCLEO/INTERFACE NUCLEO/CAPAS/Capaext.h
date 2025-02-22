float RadiodeBrocha=1.0f;

namespace Capaext
{
	
	void redimenciona (unsigned char **capa,int ancho,int alto,int profundidad) // se decide pasar la direccion del puntero por que se destruia al salir de la funcion
	{
		if (*capa!=NULL)
		{
			printf ("Memoria liberada \n");
			free(*capa);
		 } 
		*capa = (unsigned char*) malloc(ancho * alto * profundidad); 
		if (*capa!=NULL)
		{
			printf ("Memoria Generada \n");		
		 } 
	}

	void rellena (unsigned char *capa,int ancho,int alto,int profundidad,ImVec4 *color_de_capa)
	{		
		
		//if (capa!=NULL) free(capa);				
		//capa = (unsigned char*) malloc(ancho * alto * profundidad);		
		
		int bytes=ancho*alto*profundidad;
	    for (int i=0;i<bytes;i+=profundidad)
	    {
	    	*(capa+i)=(Uint8)(color_de_capa->x*255);
	    	*(capa+i+1)=(Uint8)(color_de_capa->y*255);
	    	*(capa+i+2)=(Uint8)(color_de_capa->z*255);
	    	*(capa+i+3)=(Uint8)(color_de_capa->w*255);	    	
		}
		
	}
	
	
	void rellena_alpha (unsigned char *capa,int ancho,int alto,int profundidad,ImVec4 *color_de_capa,float alpha)
	{		
		ImVec4 getcolor;
		//if (capa!=NULL) free(capa);				
		//capa = (unsigned char*) malloc(ancho * alto * profundidad);		
		
		int bytes=ancho*alto*profundidad;
	    for (int i=0;i<bytes;i+=profundidad)
	    {
	    		    	
	    	getcolor.x=(float)*(capa+i)/255.0;
    		getcolor.y=(float)*(capa+i+1)/255.0;
    		getcolor.z=(float)*(capa+i+2)/255.0;
    		getcolor.w=(float)*(capa+i+3)/255.0;
	    	
	    	if (color_de_capa->x==getcolor.x && color_de_capa->y==getcolor.y  && color_de_capa->z==getcolor.z )
	    	 {	    	 	
	    		*(capa+i+3)=(Uint8)(alpha*255);	    	
			 }
	    	
	    	
		}
		
	}
	
	void rellena_colorkey (unsigned char *capa,int ancho,int alto,int profundidad,ImVec4 *color_de_capa,ImVec4 *nuevo_colorkey)
	{		
		ImVec4 getcolor;
		//if (capa!=NULL) free(capa);				
		//capa = (unsigned char*) malloc(ancho * alto * profundidad);		
		
		int bytes=ancho*alto*profundidad;
	    for (int i=0;i<bytes;i+=profundidad)
	    {
	    		    	
	    	getcolor.x=(float)*(capa+i)/255.0;
    		getcolor.y=(float)*(capa+i+1)/255.0;
    		getcolor.z=(float)*(capa+i+2)/255.0;
    		getcolor.w=(float)*(capa+i+3)/255.0;
	    	
	    	if (color_de_capa->x==getcolor.x && color_de_capa->y==getcolor.y  && color_de_capa->z==getcolor.z )
	    	 {
	    	 	*(capa+i)=(Uint8)(nuevo_colorkey->x*255);
	    		*(capa+i+1)=(Uint8)(nuevo_colorkey->y*255);
	    		*(capa+i+2)=(Uint8)(nuevo_colorkey->z*255);
	    		//*(capa+i+3)=(Uint8)(alpha*255);	    	
			 }
	    	
	    	
		}
		
	}
			
	void capa_a_textura (unsigned char *capa,int ancho,int alto,GLuint *texturecapa)
	{
		glGenTextures(1, texturecapa);
		glBindTexture(GL_TEXTURE_2D, *texturecapa);		
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, capa);
	}
	
	void capa_a_texturab (unsigned char **capa,int ancho,int alto,GLuint *texturecapa)
	{
		glGenTextures(1, texturecapa);
		glBindTexture(GL_TEXTURE_2D, *texturecapa);		
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, *capa);
	}
	
	/*
	void rellena_hoja (Hojas *nodos,ImVec4 *color_de_hoja)
	{
		Capaext::rellena (nodos->indice->hoja.capa.rtdata,nodos->indice->hoja.capa.ancho_real,nodos->indice->hoja.capa.alto_real,4,color_de_hoja);
		Capaext::capa_a_textura(nodos->indice->hoja.capa.rtdata,nodos->indice->hoja.capa.ancho_real,nodos->indice->hoja.capa.alto_real,&nodos->indice->hoja.capa.texturecapa);
	}
	*/
	
	void pixel_a_capa (unsigned char *capa,int ancho,int alto,int *x,int *y,ImVec4 *color_de_capa)
	{
		if (*x>=ancho) *x=ancho-1;
		if (*y>=alto) *y=alto-1;
		if (*x<0) *x=0;
		if (*y<0) *y=0;
	    int i=(ancho*4*(*y)+(*x)*4);
	    
    	*(capa+i)=(Uint8)(color_de_capa->x*255);
    	*(capa+i+1)=(Uint8)(color_de_capa->y*255);
    	*(capa+i+2)=(Uint8)(color_de_capa->z*255);
    	*(capa+i+3)=(Uint8)(color_de_capa->w*255);		
	}
		
	void pixel_a_textura (unsigned char *capa,int ancho,int alto,int *x,int *y,ImVec4 *color_de_capa,GLuint *texturecapa)
	{
		if (*x>=ancho) *x=ancho-1;
		if (*y>=alto) *y=alto-1;
		if (*x<0) *x=0;
		if (*y<0) *y=0;
	    int i=(ancho*4*(*y)+(*x)*4);
	    
    	*(capa+i)=(Uint8)(color_de_capa->x*255);
    	*(capa+i+1)=(Uint8)(color_de_capa->y*255);
    	*(capa+i+2)=(Uint8)(color_de_capa->z*255);
    	*(capa+i+3)=(Uint8)(color_de_capa->w*255);		    	
		
		glGenTextures(1, texturecapa);
		glBindTexture(GL_TEXTURE_2D, *texturecapa);		
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, capa);	
	}
	
	 
	void get_color_de_capa  (unsigned char *capa,ImVec4 *color_picker,int ancho,int alto,int x,int y)
	{
		if (x>=ancho) x=ancho-1;
		if (y>=alto) y=alto-1;
		if (x<0) x=0;
		if (y<0) y=0;
	    int i=(ancho*4*(y)+(x)*4);
	    
    	color_picker->x=(float)*(capa+i)/255.0;
    	color_picker->y=(float)*(capa+i+1)/255.0;
    	color_picker->z=(float)*(capa+i+2)/255.0;
    	color_picker->w=(float)*(capa+i+3)/255.0;		
	}
	
	/*
	void pixel_a_hoja (Hojas *nodos,int *x,int *y,ImVec4 *color_de_capa)
	{
		Capaext::pixel_a_textura(nodos->indice->hoja.capa.rtdata,nodos->indice->hoja.capa.ancho_real,nodos->indice->hoja.capa.alto_real,x,y,color_de_capa,&nodos->indice->hoja.capa.texturecapa);		
	}
	*/
	
	void circulo_relleno_a_capa (unsigned char *capa,int ancho,int alto,int *x,int *y,SDL_Color *color_de_capa,float *radio)
	{		
		
		for (float ra=0;ra<*radio;ra++)
		{
			float pr=ra*6.28318530718f;
			float step=6.28318530718f/pr;
			
			float xf=(float)(*x);
			float yf=(float)(*y);
			
			for (float df=0.0f;df<pr;df++)
			{				
				int px=int ( cos( ((float)df) * step )*(float)ra ) +xf;
				int py=int ( sin( ((float)df) * step )*(float)ra ) +yf;
			
				if (px>=0 && px<ancho && py>=0 && py<alto ) 
				{
					int i=(ancho*4*(py)+px*4);
	    
			    	*(capa+i)=(Uint8)(color_de_capa->r);
			    	*(capa+i+1)=(Uint8)(color_de_capa->g);
			    	*(capa+i+2)=(Uint8)(color_de_capa->b);
			    	*(capa+i+3)=(Uint8)(color_de_capa->a);
				}
				
			}
		}
	}
	
	/*
	void circulo_relleno_a_capa (unsigned char *capa,int ancho,int alto,int *x,int *y,ImVec4 *color_de_capa,float *radio)
	{		
		
		for (float ra=0;ra<*radio;ra++)
		{
			float pr=ra*6.28318530718f;
			float step=6.28318530718f/pr;
			
			float xf=(float)(*x);
			float yf=(float)(*y);
			
			for (float df=0.0f;df<pr;df++)
			{				
				int px=int ( cos( ((float)df) * step )*(float)ra ) +xf;
				int py=int ( sin( ((float)df) * step )*(float)ra ) +yf;
			
				if (px>=0 && px<ancho && py>=0 && py<alto ) 
				{
					int i=(ancho*4*(py)+px*4);
	    
			    	*(capa+i)=(Uint8)(color_de_capa->x*255);
			    	*(capa+i+1)=(Uint8)(color_de_capa->y*255);
			    	*(capa+i+2)=(Uint8)(color_de_capa->z*255);
			    	*(capa+i+3)=(Uint8)(color_de_capa->w*255);
				}
				
			}
		}
	}*/
	
	void circulo_a_capa (unsigned char *capa,int ancho,int alto,int *x,int *y,ImVec4 *color_de_capa)
	{
		float ra=RadiodeBrocha;
		
		float pr=ra*6.28318530718f;
		float step=6.28318530718f/pr;
		
		float xf=(float)(*x);
		float yf=(float)(*y);
		
		for (float df=0.0f;df<pr;df++)
		{				
			int px=(int) ( cos( ((float)df) * step )*(float)ra ) +xf;
			int py=(int) ( sin( ((float)df) * step )*(float)ra ) +yf;
		
			if (px>=0 && px<ancho && py>=0 && py<alto ) 
			{
				int i=(ancho*4*(py)+px*4);
    
		    	*(capa+i)=(Uint8)(color_de_capa->x*255);
		    	*(capa+i+1)=(Uint8)(color_de_capa->y*255);
		    	*(capa+i+2)=(Uint8)(color_de_capa->z*255);
		    	*(capa+i+3)=(Uint8)(color_de_capa->w*255);
			}
			
		}
		
	}
	
	bool carga_capa(const char* filename, unsigned char **image_data, int* out_width, int* out_height)
	{		    
	    *image_data = stbi_load(filename, out_width, out_height, NULL, 4);
	    if (*image_data == NULL)
	        return false;	
	    return true;
	} 
	
}