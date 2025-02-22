

void menu_capas ()
{
	//char arr[100]={0};
	char *arr = new char [200]; 
	arr[0]=0;
	static int ancho=256,alto=256;
	static int anchoreal=256,altoreal=256;
	static bool mantenerescalaviewport=false;
		
	//ImGui::SameLine ();
	
	int accion=menu_basico_de_nodos ();
	
	switch (accion)
	{
		case AGREGA :
			motordecapas.add();
			printf("Ancho de capa %d x %d \n",anchoreal,altoreal);
			if (motordecapas.indice!=NULL) 
			{				
				motordecapas.redimenciona(anchoreal,altoreal,motordecapas.color);
				if (mantenerescalaviewport==false)
				{
					motordecapas.indice->objeto.ancho=anchoreal;
					motordecapas.indice->objeto.alto=altoreal;
				}
				
			}
		break;
		case BORRAR:
			motordecapas.del_seleccionados();
		break;
		case ELIMINA:
			motordecapas.del();
		break;
		case SELECCIONARTODO:
			motordecapas.SelectAll();
		break;
		case CARGA:
		break;
		case GRABA:
		break;
	}
	autoid++;ImGui::PushID(autoid);autoid++;ImGui::Text("Ancho real");
	if (ImGui::InputInt("##",&anchoreal))									
		{			
		}
	ImGui::PopID ();
					
	autoid++;ImGui::PushID(autoid);autoid++;ImGui::Text("Alto real");
	if (ImGui::InputInt("##",&altoreal))									
		{			 
		}
	ImGui::PopID ();
		
	static float comcolor[3]={(float)motordecapas.color.r/255,(float)motordecapas.color.g/255,(float)motordecapas.color.b/255};
	static float comtrans[3]={0.0,0.0,0.0};	
	autoid++;ImGui::PushID(autoid);autoid++;ImGui::Text("Color de capa a crear");
	if (ImGui::ColorEdit3("##", comcolor));	
	{
		motordecapas.color.r=comcolor[0]*255;
		motordecapas.color.g=comcolor[1]*255;
		motordecapas.color.b=comcolor[2]*255;		
	}
	ImGui::PopID();
	
	if (motordecapas.indice!=NULL)
	{
		
		static float comcolor2[3]={(float)motordecapas.color.r/255,(float)motordecapas.color.g/255,(float)motordecapas.color.b/255};
		static float comtrans2[3]={0.0,0.0,0.0};
		autoid++;ImGui::PushID(autoid);autoid++;ImGui::Text("Color de relleno");
		if (ImGui::ColorEdit3("##", comcolor2));	
			{
				static SDL_Color colorr = {255, 0, 0,255};
				colorr.r=comcolor2[0]*255;
				colorr.g=comcolor2[1]*255;
				colorr.b=comcolor2[2]*255;
				if (ImGui::IsItemFocused())
				{
					motordecapas.rellena(&colorr);
				}
				
			}
		ImGui::PopID();
	
		ImGui::SeparatorText("Escalar capa en pixeles");
		autoid++;ImGui::PushID(autoid);autoid++;ImGui::Text("Ancho");
		if (ImGui::InputInt("##",&ancho))									
			{
				if (motordecapas.PROPORCIONES)
					{
						int step=ancho-motordecapas.indice->objeto.ancho;
						motordecapas.indice->objeto.ancho=ancho;
						alto+=step;
						motordecapas.indice->objeto.alto=alto;
					}										 
					else
					 motordecapas.indice->objeto.ancho=ancho;
				 
				 motordecapas.redimenciona_todos_los_seleccionados (ancho,alto);						
			}
		ImGui::PopID();
		
		autoid++;ImGui::PushID(autoid);autoid++;ImGui::Text("Alto");
		if (ImGui::InputInt("##",&alto))									
		{
			if (motordecapas.PROPORCIONES)
			{
				int step=alto-motordecapas.indice->objeto.alto;
				motordecapas.indice->objeto.alto=alto;
				ancho+=step;
				motordecapas.indice->objeto.ancho=ancho;
			}										 
			else
			 motordecapas.indice->objeto.alto=alto;
		}
		ImGui::PopID();
	
		ImGui::Checkbox("RESTRINGIR PROPORCIONES ", &motordecapas.PROPORCIONES); 
		ImGui::Checkbox("MANTENER ESCALA EN VIEWPORT ", &mantenerescalaviewport);	
		
		if (ImGui::Button ("Redimenciona Capa"))
			{
				//OPCION_DE_MENU=TEXTURA_EDITABLE;
				if (motordecapas.indice!=NULL) 
					{										
						motordecapas.redimenciona(anchoreal,altoreal,motordecapas.color);
						motordecapas.indice->objeto.ancho=anchoreal;
						motordecapas.indice->objeto.alto=altoreal;
					}
			}
		
		if (ImGui::Button ("Rellena Capa"))
			{
				if (motordecapas.indice!=NULL) 
					{				
						motordecapas.rellena(&motordecapas.color);					
					}
			}	
			
		strcpy(arr, motordecapas.indice->nombre.c_str());
		
		ancho=motordecapas.indice->objeto.ancho;
		alto=motordecapas.indice->objeto.alto;									
		
		std::string dimenciones;
		
		dimenciones="Dimenciones = "+std::to_string(motordecapas.indice->objeto.ancho_real)+" X "+std::to_string(motordecapas.indice->objeto.alto_real);		
		   
		ImGui::BeginGroup();
		
		//ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
		
			if (ImGui::CollapsingHeader("Propiedades de capa"))
				{
					ImGui::Text(dimenciones.c_str());
									
					if (ImGui::InputText("Nombre", arr , 100))
				   	{
				   		
						motordecapas.indice->nombre=arr;
				   	};	
				   	
				   	ImGui::Text(motordecapas.indice->path.c_str());
					
					ImGui::SeparatorText("Transformaciones");
					
					ImGui::SeparatorText("Clave de Transparencias");					
					ImGui::ColorEdit3("Color de Transparencia", comtrans);
					
					if (ImGui::Button ("Crear Superficie"))
						{
						//	OPCION_DE_MENU=TEXTURA_EDITABLE;						
							motordecapas.redimenciona(anchoreal,altoreal,motordecapas.color);
						}
					if (ImGui::Button ("Superficie a Capa"))
						{
						//	OPCION_DE_MENU=TEXTURA_EDITABLE;
						}
						
					if (ImGui::InputFloat("Radio de Brocha",&RadiodeBrocha))
						{
							
						}
				
				}
			
		ImGui::EndGroup();
		
	//	ImGui::PopStyleVar(1);
		
		motordecapas.indice->objeto.ancho=ancho;
	   	motordecapas.indice->objeto.alto=alto;
	   	
	   	motordecapas.redimenciona_todos_los_seleccionados (ancho,alto);
	   	
	}
	           		
	
	
	ImGui::SeparatorText("Tipo De Presentacion");											
	
	if (ImGui::Checkbox("CAPA MULTI VIEW ", &motordecapas.MULTI_VIEW))
	{
		motordecapas.MOSAICO=false;
	};
	
	if (ImGui::Checkbox("CAPA EN MOSAICOS ", &motordecapas.MOSAICO))
	{
		motordecapas.MULTI_VIEW=false;
	};
		
	ImGui::SeparatorText("Capas");	
	if (ImGui::CollapsingHeader("Elementos"))
		{
			ImGui::Begin("CapasElements");
			motordecapas.despliega();
			ImGui::End();
		}
	
	ImGui::SeparatorText("");	
	delete [] arr;
}