int OPCION_DE_MENU=NINGUNA;

Icono control_bar [6];

enum ACCIONES_DE_NODOS {
	NADA,
	AGREGA,ELIMINA,CARGA,GRABA,BORRAR,SELECCIONARTODO
};


char lista_de_iconos[][100]= {
	"RECURSOS/ICONOS/add.png",
	"RECURSOS/ICONOS/min.png",
	"RECURSOS/ICONOS/carga.png",
	"RECURSOS/ICONOS/graba.png",
	"RECURSOS/ICONOS/borrar.png",
	"RECURSOS/ICONOS/selectall.png"
};

void inicializa_menu_basico_de_nodos (void) {
	bool ret=false;

	for (int index=0; index<sizeof(lista_de_iconos)/sizeof(lista_de_iconos)[0]; index++) {
		ret=false;
		ret = LoadTextureFromFile(lista_de_iconos[index],&control_bar[index].TIcono, &control_bar[index].ancho,&control_bar[index].largo);
		if (ret) printf("Textura cargada correctamente\n");
		else printf("Textura no cargada correctamente\n");
		IM_ASSERT(ret);
	}
}

int menu_basico_de_nodos (void) {
	int select=NADA;
	int items=sizeof(lista_de_iconos)/sizeof(lista_de_iconos)[0];

	for (int index=0; index<sizeof(lista_de_iconos)/sizeof(lista_de_iconos)[0]; index++) {
		autoid++;
		ImGui::PushID(autoid);
		if ( ImGui::ImageButton("##",control_bar[index].TIcono,ImVec2(control_bar[index].ancho/4, control_bar[index].largo/4)) ) {
			select=index+1;
		}
		ImGui::PopID();
		if (index<items-1) ImGui::SameLine ();
	}

	return select;

}