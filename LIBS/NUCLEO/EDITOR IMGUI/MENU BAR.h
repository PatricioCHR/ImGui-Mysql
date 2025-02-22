
void MenuBarEditor(int opcion)
{
    
   if(ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Archivos"))
				{				    				     
					if(ImGui::MenuItem("Load test"))
					     {
					     	//opcion=CARGARESCENA;
					        //abre_archivo.crea_dialogo ("Cargar Escena",".pyt");
							//OPCION_DE_MENU=CARGA_ESCENA;					        
					     }
					if(ImGui::MenuItem("Save test"))
					     {			
						 	//opcion=GRABARESCENA;
					        //abre_archivo.crea_dialogo ("Grabar Escena",".pyt");
					        //OPCION_DE_MENU=GRABA_ESCENA;
					     }
					if(ImGui::MenuItem("Merge test"))
					     {
					     	//opcion=MEZCLARESCENA;
					        //abre_archivo.crea_dialogo ("Mezclar Escena",".pyt");
							//OPCION_DE_MENU=MEZCLAR_ESCENA;					        
					     }
					ImGui::EndMenu();
				}
			
			
			if (ImGui::BeginMenu("UI"))
				{
				    if(ImGui::MenuItem("Load UI"))
					     {
					     	opcion=18;
					        //abre_archivo2.crea_dialogo ("Cargar Textura",".*");
					        //OPCION_DE_MENU=CARGA_Y_CREA_TEXTURA;
					        	
					     }
					if(ImGui::MenuItem("save UI"))
					     {
					     	opcion=19;
					        //abre_archivo.crea_dialogo ("Grabar Textura",".*");
					     }
					
					ImGui::EndMenu();
				}
				
			if (ImGui::BeginMenu("Help"))
				{
				    
					if(ImGui::MenuItem("About CUbIQ"))
					     {
					     	opcion=17;
					        //Do something
					     }
					ImGui::EndMenu();
				}
					
			ImGui::EndMainMenuBar();
		}   
}
