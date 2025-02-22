#pragma once
#include "Capa.h"
	
class Capas 
{	
	public:
			
	class nodo
	{
		public:
		Capa objeto;	
		bool seleccionado=false;
		std::string path;
		std::string nombre;
		nodo *anterior;
		nodo *siguiente;
	};

	
	nodo *indice=NULL;
	nodo *inicio=NULL;
	nodo *final=NULL;
	bool start=false;
	int numero_de_objetos=0;	
	
	Capas ();
	~Capas ();
	void add ();
	void add (int sx,int sy);
	void del (void);		
	void del_seleccionados(void);
	void del_todos (void);
	void SelectAll (void);
	
	
};

Capas::Capas() 
{
	
}

Capas::~Capas()
{
	int conteo=numero_de_objetos;	
	nodo *temp;
	conteo=0;
	if (inicio!=NULL)
	{
		temp=indice;
		indice=inicio;
		//if (indice->sprites.nombre)	delete[] indice->sprites.nombre; 
			while (indice!=NULL)
			{
				temp=indice;
				indice=temp->siguiente;		
				delete temp;
				conteo++;
				printf ("Capa %d destruida\n",conteo);
				
			}
	
	}
	
}

void Capas::add ()
{
	indice= new nodo();
	
	numero_de_objetos++;	
	indice->nombre="capa-";	
	std::string no = std::to_string(numero_de_objetos);
	indice->nombre=indice->nombre+no;		
	printf("%s\n", indice->nombre.c_str());   
				
	if (start==false)
		{
			start=true;
			inicio=indice;
			indice->anterior=NULL;
			indice->siguiente=NULL;			
			final=indice;			
		} else
			{
				indice->anterior=final;				
				indice->siguiente=NULL;
				final->siguiente=indice;
				final=indice;				
			}
	
}

void Capas::add (int sx,int sy)
{
	add();
}

void Capas::del(void)
{
	nodo *temp;
	int conteo=0;
	if (indice!=NULL)
	{
		temp=indice;
		
		if (temp->siguiente!=NULL && temp->anterior!=NULL)  //Si existe siguiente y anterior
			{
				temp->anterior->siguiente=temp->siguiente;
				temp->siguiente->anterior=temp->anterior;
				indice=temp->anterior;
				temp->objeto.~Capa();
				delete temp;
				conteo--;
				printf ("capa Eliminada quedan %d Capas siguiente anterior\n",conteo);
				return;
			}
			
		if (temp->siguiente==NULL && temp->anterior!=NULL )  //Si no hay siguiente y si hay anterior
			{
				temp->anterior->siguiente=NULL;				
				indice=temp->anterior;
				temp->objeto.~Capa();
				final=indice;
				delete temp;
				conteo--;
				printf ("capa Eliminada quedan %d Capas anterior existe siguiente no\n",conteo);
				return;
			}
			
		if (temp->siguiente!=NULL && temp->anterior==NULL )  //Si hay siguiente y si no hay anterior
			{								
				indice=temp->siguiente;
				indice->anterior=NULL;		
				inicio=indice;		
				temp->objeto.~Capa();
				delete temp;				
				conteo--;
				printf ("capa Eliminada quedan %d capas siguiente existe anterior no\n",conteo);
				return;
			}
		inicio=NULL;
		final=NULL;
		indice=NULL;
		temp->objeto.~Capa();
		delete temp;
		conteo--;
		start=false;
		printf ("capa Eliminada quedan %d Capas lista vacia\n",conteo);		
	}
}

void Capas::del_seleccionados(void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		if (indice->seleccionado) del();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}

void Capas::del_todos (void)
{
	nodo *temp;
	nodo *temp2;
	if (indice!=NULL)	temp=indice;
	
	indice=inicio;
	while (indice!=NULL)
	{		
		temp=indice->siguiente;
		del();
		indice=temp;
	}
	if (inicio!=NULL)
		indice=inicio;
		else indice=NULL;
}
	
	
void Capas::SelectAll(void)
{
	nodo *temp;	
	
	if (indice!=NULL)
	{		
		temp=indice;
		
		indice=inicio;
		while (indice!=NULL)
		{	
			
			indice->seleccionado=true;
			indice=indice->siguiente;
		}
		
		if (temp!=NULL)
			indice=temp;
			else indice=NULL;
	}
}
