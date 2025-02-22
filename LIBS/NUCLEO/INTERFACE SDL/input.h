namespace SDL_IO
{
	bool SDL_Click_L=false;
	bool SDL_Click_R=false;
	bool SDL_Click_M=false;

	bool KEY_A=false;
	bool KEY_S=false;
	bool KEY_D=false;
	bool KEY_W=false;
	
	bool KEY_CONTROL_LEFT=false;
	bool KEY_CONTROL_RIGHT=false;

	bool KEY_ARROW_UP=false;
	bool KEY_ARROW_DOWN=false;
	bool KEY_ARROW_LEFT=false;
	bool KEY_ARROW_RIGHT=false;
	
	void KeyDown (SDL_KeyboardEvent *event)
	{
		if (event->repeat == 0)
		    {
		        if (event->keysym.scancode == SDL_SCANCODE_UP)
		        {
		            KEY_ARROW_UP=true;
		        }
		
		        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		        {
		            KEY_ARROW_DOWN=true;
		        }
		
		        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		        {
		            KEY_ARROW_LEFT = true;
		        }
		
		        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		        {
		            KEY_ARROW_RIGHT = true;
		        }
		        
		        if (event->keysym.scancode ==SDL_SCANCODE_LCTRL)
		        {
		        	KEY_CONTROL_LEFT=true;		
				}
				
				if (event->keysym.scancode ==SDL_SCANCODE_RCTRL)
		        {
		        	KEY_CONTROL_RIGHT=true;		
				}
						
		    }
	}
	
	void KeyUp (SDL_KeyboardEvent *event)
	{
		if (event->repeat == 0)
		    {
		        if (event->keysym.scancode == SDL_SCANCODE_UP)
		        {
		            KEY_ARROW_UP=false;
		        }
		
		        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		        {
		            KEY_ARROW_DOWN=false;
		        }
		
		        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		        {
		            KEY_ARROW_LEFT = false;
		        }
		
		        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		        {
		            KEY_ARROW_RIGHT = false;
		        }
		        
		        if (event->keysym.scancode ==SDL_SCANCODE_LCTRL)
		        {
		        	KEY_CONTROL_LEFT=false;
				}
				
				if (event->keysym.scancode ==SDL_SCANCODE_RCTRL)
		        {
		        	KEY_CONTROL_RIGHT=false;		
				}
		    }
	}
	
	void Input_Keyboard(SDL_Window* window )
	{
	    SDL_Event event;
	
	    while (SDL_PollEvent(&event))
	    {
	    	#if defined(IMGUI_OPENGL2)
	    		ImGui_ImplSDL2_ProcessEvent(&event);
	    	#endif
	    	if ( (event.type == SDL_QUIT) || ( SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode ) )
                interfaceNUCLEO::START=false;
            
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                interfaceNUCLEO::START=false;
                
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
		        {
		            SDL_Delay(10);
		            continue;
		        }

	    	
	        switch (event.type)
	        {
	            case SDL_QUIT:
	            	interfaceNUCLEO::START=false;	                
	                break;
	                
	            case SDL_MOUSEMOTION :
            		//if ( pintar==true)
				      //  {
				        	//SDL_GetWindowPosition(window,&camx, &camy);				  			
					//	}
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
	                
	            case SDL_KEYDOWN:
                	KeyDown(&event.key);
                break;

            	case SDL_KEYUP:
                	KeyUp(&event.key);
                break;
	
	            default:
	                break;
	        }
	    }
	
	}

}

namespace SDL_MOUSE
{
	bool SDL_Click_L=false;
	bool SDL_Click_R=false;
	bool SDL_Click_M=false;
	
	int SDLmousex, SDLmousey; 
}