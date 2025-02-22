#pragma once

class Capa
{	
public:
    unsigned char *rtdata=NULL;
    GLuint texturecapa=0;
    int alto=480;
	int ancho=360;
	int alto_real=480;
	int ancho_real=360;
	int posx=0,posy=0;
    int formatobit=GL_RGBA;
    int formatodatos=GL_UNSIGNED_BYTE;
   	Capa ();
	~Capa ();
};

Capa::Capa()
{	
	
}

Capa::~Capa ()
{
	if (texturecapa)
	{
		glDeleteTextures(1, &texturecapa );
		printf ("Textura destruida \n");
	}
	if (rtdata!=NULL) 
		{
			free(rtdata); 
			rtdata=NULL;
		}
}