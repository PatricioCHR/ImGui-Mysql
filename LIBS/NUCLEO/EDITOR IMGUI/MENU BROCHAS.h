inline void menu_brochas ()
	{
		char *arr = new char [200]; 
		arr[0]=0;
		float RadiodeBrocha=1.0f;
		
		float color_de_brocha[3]={0.1,0.2,0.3};
		
		ImGui::Begin("Space Brochas");
			
		int accion=menu_basico_de_nodos ();			
		
		switch (accion)
		{
			case AGREGA :
				motordebrochas.add();				
				if (motordebrochas.indice!=NULL) 
				{				
					
					
				}
			break;
			case BORRAR:
				motordebrochas.del_seleccionados();
			break;
			case ELIMINA:
				motordebrochas.del();
			break;
			case SELECCIONARTODO:
				motordebrochas.SelectAll();
			break;
			case CARGA:
			break;
			case GRABA:
			break;
		}	
			
		if (motordebrochas.indice!=NULL)
			{		
				strcpy(arr, motordebrochas.indice->nombre.c_str());
				
				ImGui::SeparatorText("Nombre :");
				autoid++;ImGui::PushID(autoid);
				if (ImGui::InputText("##", arr , 100))
				   	{
				   		
						motordebrochas.indice->nombre=arr;
				   	};
				ImGui::PopID();
			
				//ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.8f);				
				ImGui::SeparatorText("Color :");				
				//ImGui::Label("Selecciona Color debrocha");	
				static float comcolor2[3]={(float)motordebrochas.color.r/255,(float)motordebrochas.color.g/255,(float)motordebrochas.color.b/255};
				static float comtrans2[3]={0.0,0.0,0.0};
					
				autoid++;ImGui::PushID(autoid);autoid++;
				if (ImGui::ColorEdit3("##", (float*)&comcolor2))
				{					
					motordebrochas.indice->objeto.color.r=comcolor2[0]*255;
					motordebrochas.indice->objeto.color.g=comcolor2[1]*255;
					motordebrochas.indice->objeto.color.b=comcolor2[2]*255;					
				}
				ImGui::PopID();
				
				ImGui::SeparatorText("Radio :");
				autoid++;ImGui::PushID(autoid);
				ImGui::SliderFloat("##", &motordebrochas.indice->objeto.radio, 0, 100, "%.3f", 0);								
				ImGui::PopID();
				
				autoid++;ImGui::PushID(autoid);
				if (ImGui::InputFloat("##",&motordebrochas.indice->objeto.radio))
					{
						
					}
				ImGui::PopID();
			}
		
		
		ImGui::Begin("Brochas Elements");
		motordebrochas.despliega();
		ImGui::End();
		
			
		ImGui::End ();
		
		ImGui::SeparatorText("");	
		delete [] arr;
	}