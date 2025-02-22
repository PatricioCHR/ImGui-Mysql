



							
char menu_barra_de_proyecto[][20]={
									"Brochas	   ",
									"Capas         ",
									"Efectos       ",
									"Hojas		   ",
									"Materiales    ",
									"Nodos         ",
									"Sonidos       ",
									"Sprites       ",
									"Renderers     ",
									"Texturas      "
								};


void BarradeProyecto (void)
{
		
	ImGuiWindowFlags imgui_flags = 0 | ImGuiTableFlags_Borders | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersV ;
	
	ImGui::Begin("Estructura de Proyecto");
	
			for (int index=0;index<sizeof(menu_barra_de_proyecto)/sizeof(menu_barra_de_proyecto)[0];index++)
			{
	
				if (ImGui::TreeNode(menu_barra_de_proyecto[index]))
					{					
						
						ImGui::TreePop(); 
							if (strstr (menu_barra_de_proyecto[index],"Brochas") != 0)  
							{	
								
								menu_brochas ();
							//	ImGui::TreePop(); 								
							}
							
							if (strstr (menu_barra_de_proyecto[index],"Hojas") != 0)  
							{					
								//menu_basico_de_nodos ();
								//menu_hojas.Menu_basico(&noprogramada);								
								
								//ImGui::TreePop();
								//ImGui::Begin("Nodosxxx");
									//menu_hojas.Despliega_nodos();
									//menu_hojas.Menu_extendido (&noprogramada);
								//ImGui::End();
							}
							
							if (strstr (menu_barra_de_proyecto[index],"Capas") != 0)
							{	
							
								menu_capas ();
								
								/*
								if (OPCION_DE_NODOBAR==AGREGA)
								{
									printf ("agrega capa");
									motordecapas.add_capa();
								} */
								
							//	motordecapas.despliega();
								
							//	ImGui::TreePop(); 								
							}
						
							if (strstr (menu_barra_de_proyecto[index],"Nodos") != 0)
							{
								//menu_basico_de_nodos ();
								//menu_nodos(&noprogramada);
								//ImGui::TreePop(); 
								
							}
							
							if (strstr (menu_barra_de_proyecto[index],"Sprites") != 0)  
							{
								menu_basico_de_nodos ();
								//if (OPCION_DE_NODOBAR==AGREGA)
								//{
								//	printf ("agrega Sprite");
								//}
								//menu_basico_de_nodos ();
								//menu_sprites (&noprogramada);
								//ImGui::TreePop(); 
								
							}
														
							if (strstr (menu_barra_de_proyecto[index],"Texturas") != 0)  
							{
								//menu_basico_de_nodos ();
								//menu_texturas (&noprogramada);
								//ImGui::TreePop(); 
								
							}
							
							if (strstr (menu_barra_de_proyecto[index],"Renderers") != 0)  
							{
								//menu_basico_de_nodos ();						
								//Efectos_de_Renderer::menu_renderer (&noprogramada);
								//ImGui::TreePop(); 
								
							}							
							
						
					} else
						{
						};
			}	
					
		
	ImGui::End();	
}
