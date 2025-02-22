

void menu_capas ()
{
	//char arr[100]={0};
	char *arr = new char [200]; 
	arr[0]=0;
	static int ancho=360,alto=480;
	static int anchoreal=360,altoreal=480;
	static bool mantenerescalaviewport=false;
	
	//ImGui::SameLine ();
	
	int accion=menu_basico_de_nodos ();
	
	
	if (accion==0 )			
		{										
			motordecapas.add_capa();
			printf("Ancho de capa %d x %d \n",anchoreal,altoreal);
			if (motordecapas.indice!=NULL) 
			{
				ImVec4 color (motordecapas.color_de_capa.r,motordecapas.color_de_capa.r,motordecapas.color_de_capa.b,motordecapas.color_de_capa.a);
				motordecapas.redimenciona(anchoreal,altoreal,color);
				if (mantenerescalaviewport==false)
				{
					motordecapas.indice->capa.ancho=anchoreal;
					motordecapas.indice->capa.alto=altoreal;
				}
				
			}
		}			
	
	if ( accion==1)
		{				
			motordecapas.del_capa();			
		}								
	
	
	if ( accion==2)
		{	
			if (motordecapas.indice)
				{
					OPCION_DE_MENU=CARGACAPA;
					//abre_archivo.crea_dialogo ("Cargar Sprite",".*");
				}											
		}
	
	
	if ( accion==3)
		{
			motordecapas.del_capa ();			
		}
	
	if ( accion==4)
		{
			motordecapas.del_capas_seleccionadas();
		}
		
	if ( accion==5)
		{
			motordecapas.SelectAll();
		}
		
	if (ImGui::InputInt("Ancho Real",&anchoreal))									
	{
		
	}
					
	if (ImGui::InputInt("Alto Real",&altoreal))									
	{
		 
	}
	
	ImGui::SeparatorText("Escalar capa en pixeles");
	if (ImGui::InputInt("Ancho",&ancho))									
	{
		if (motordecapas.CAPA_PROPORCIONES)
		{
			int step=ancho-motordecapas.indice->capa.ancho;
			motordecapas.indice->capa.ancho=ancho;
			alto+=step;
			motordecapas.indice->capa.alto=alto;
		}										 
		else
		 motordecapas.indice->capa.ancho=ancho;
		 
		 motordecapas.redimenciona_todas_las_capas_seleccionadas (ancho,alto);						
	}
	
	if (ImGui::InputInt("Alto",&alto))									
	{
		if (motordecapas.CAPA_PROPORCIONES)
		{
			int step=alto-motordecapas.indice->capa.alto;
			motordecapas.indice->capa.alto=alto;
			ancho+=step;
			motordecapas.indice->capa.ancho=ancho;
		}										 
		else
		 motordecapas.indice->capa.alto=alto;
	}
	
	ImGui::Checkbox("RESTRINGIR PROPORCIONES ", &motordecapas.CAPA_PROPORCIONES); 
	ImGui::Checkbox("MANTENER ESCALA EN VIEWPORT ", &mantenerescalaviewport);
	
	
	
	ImGui::ColorEdit3("Color KEY", (float*)&motordecapas.color_de_capa);	
		
	if (ImGui::Button ("Redimenciona Capa"))
		{
			//OPCION_DE_MENU=TEXTURA_EDITABLE;
			if (motordecapas.indice!=NULL) 
				{
					ImVec4 color (motordecapas.color_de_capa.r,motordecapas.color_de_capa.r,motordecapas.color_de_capa.b,motordecapas.color_de_capa.a);
					motordecapas.redimenciona(anchoreal,altoreal,color);
					motordecapas.indice->capa.ancho=anchoreal;
					motordecapas.indice->capa.alto=altoreal;
				}
		}
	
 
	if (motordecapas.indice!=NULL)
	{
			
		strcpy(arr, motordecapas.indice->nombre.c_str());
		
		ancho=motordecapas.indice->capa.ancho;
		alto=motordecapas.indice->capa.alto;									
		
		std::string dimenciones;
		
		dimenciones="Dimenciones = "+std::to_string(motordecapas.indice->capa.ancho_real)+" X "+std::to_string(motordecapas.indice->capa.alto_real);		
		   
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
					//ImGui::ColorEdit3("Color KEY", (float*)&clear_color);
					ImGui::ColorEdit3("Color KEY", (float*)&motordecapas.color_de_capa);
					if (ImGui::Button ("Crear Superficie"))
						{
						//	OPCION_DE_MENU=TEXTURA_EDITABLE;
						ImVec4 color (motordecapas.color_de_capa.r,motordecapas.color_de_capa.r,motordecapas.color_de_capa.b,motordecapas.color_de_capa.a);
							motordecapas.redimenciona(anchoreal,altoreal,color);
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
		
		motordecapas.indice->capa.ancho=ancho;
	   	motordecapas.indice->capa.alto=alto;
	   	
	   	motordecapas.redimenciona_todas_las_capas_seleccionadas (ancho,alto);
	   	
	}
	           		
	
	
	ImGui::SeparatorText("Tipo De Presentacion");											
	
	if (ImGui::Checkbox("CAPA MULTI VIEW ", &motordecapas.CAPA_MULTI_VIEW))
	{
		motordecapas.CAPA_MOSAICO=false;
	};
	
	if (ImGui::Checkbox("CAPA EN MOSAICOS ", &motordecapas.CAPA_MOSAICO))
	{
		motordecapas.CAPA_MULTI_VIEW=false;
	};
		
	ImGui::SeparatorText("Capas");	
	if (ImGui::CollapsingHeader("Elementos"))
		{
			motordecapas.despliega();
		}
	
	ImGui::SeparatorText("");	
	delete [] arr;
}