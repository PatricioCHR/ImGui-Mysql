enum ACCIONES_DE_NODOS {
	NADA,	
	AGREGA,ELIMINA,CARGA,GRABA,BORRAR,SELECCIONARTODO
};

char lista_de_iconos[][100]={
							"RECURSOS/ICONOS/add.png",
							"RECURSOS/ICONOS/min.png",
							"RECURSOS/ICONOS/carga.png",
							"RECURSOS/ICONOS/graba.png",
							"RECURSOS/ICONOS/borrar.png",
							"RECURSOS/ICONOS/selectall.png"
							};

int menu_basico_de_nodos (void)
{
	int select=NADA;
	int items=sizeof(lista_de_iconos)/sizeof(lista_de_iconos)[0];
	
	for (int index=0;index<sizeof(lista_de_iconos)/sizeof(lista_de_iconos)[0];index++)
	{
		autoid++;		
		ImGui::PushID(autoid);    
		if ( ImGui::ImageButton("##",control_bar[index].TIcono,ImVec2(control_bar[index].ancho/4, control_bar[index].largo/4)) )	
			{
				select=index+1;
			}
		ImGui::PopID();
		if (index<items-1) ImGui::SameLine ();
	}
	
	return select;
	
}