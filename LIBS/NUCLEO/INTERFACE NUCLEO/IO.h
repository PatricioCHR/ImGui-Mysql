
bool SDL_Click_L=false;
bool SDL_Click_R=false;
bool SDL_Click_M=false;

int SDLmousex, SDLmousey; // Variables de Mouse y Ventanas    

void get_IO (void)
{
	
    SDL_Event event;        
    SDL_GetMouseState(&SDLmousex, &SDLmousey);
        

	while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            
            if ( (event.type == SDL_QUIT) || ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
                
            switch (event.type) // EVENTOS DE TECLADO Y MOUSE
            {
            	case SDL_MOUSEMOTION :
            		if ( pintar==true)
				        {
				        	//SDL_GetWindowPosition(window,&camx, &camy);
						
				  			
						}
            	break;
            	
            	case SDL_MOUSEBUTTONDOWN :
            		//ImGui::SetNextWindowFocus();
					if (event.button.button == (SDL_BUTTON_LEFT )) 
						{
							SDL_Click_L=true;
							//bool SDL_Click_M=false;	
							
						}
					if (event.button.button == (SDL_BUTTON_RIGHT)) 
						{					
							SDL_Click_R=true;
							//bool SDL_Click_M=false;
						}
            	break;
            	
            	case SDL_MOUSEBUTTONUP :
            		//ImGui::SetNextWindowFocus();
					if (event.button.button == (SDL_BUTTON_LEFT )) 
						{
							SDL_Click_L=false;
							//bool SDL_Click_M=false;	
							
						}
					if (event.button.button == (SDL_BUTTON_RIGHT)) 
						{					
							SDL_Click_R=false;
							//bool SDL_Click_M=false;
						}
            	break;
            	
            	case SDL_KEYDOWN :
            		if (event.key.keysym.sym ==SDLK_LCTRL)
						KEY_CONTROL_LEFT=true;						
            	break;
            	case SDL_KEYUP :
            		if (event.key.keysym.sym==SDLK_LCTRL )
						KEY_CONTROL_LEFT=false;
            	break;
			}
			
			
        }		
}