//#include <NUCLEO/INTERFACE IMGUI/ventanaIMGUI.h>
//#include <ventanaIMGUI.h>

namespace interfaceIMGUI
{	

int switchtecnologia=2;
bool r1=0;
bool r2=1;
	
ImGuiIO& inicializa_interface(ventanaIMGUI *w,char *nombre)
	{
		int rendererFlags;
		w->nombre=nombre;
	    // Setup SDL
	    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	    {
	        printf("Error: %s\n", SDL_GetError());
	        //return -1;
	    }
	
	    // From 2.0.18: Enable native IME.
		#ifdef SDL_HINT_IME_SHOW_UI
		    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		#endif
	
	    // Setup window
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	    
	    SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);		
		w->ancho=DM.w*0.8;
		w->alto=DM.h*0.8;
	    
	    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	    w->ventana = SDL_CreateWindow(w->nombre, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w->ancho, w->alto, window_flags);
	    if (w->ventana == nullptr)
	    {
	        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
	       // return -1;
	    }
	    
	    rendererFlags = SDL_RENDERER_ACCELERATED;
	    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	
	    w->renderer = SDL_CreateRenderer(w->ventana, -1, rendererFlags);
	    
	    if (!w->renderer)
	    {
	        printf("Falla al crear el renderer : %s\n", SDL_GetError());
	        interfaceNUCLEO::START=false;
	    }
	    
	    w->gl_context = SDL_GL_CreateContext(w->ventana);
	    SDL_GL_MakeCurrent(w->ventana, w->gl_context);
	    SDL_GL_SetSwapInterval(1); // Enable vsync
	    
	    // Setup Dear ImGui context
	    IMGUI_CHECKVERSION();
	    ImGui::CreateContext();
	    
	    ImGuiIO& io = ImGui::GetIO(); (void)io;
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	    //#if defined(MULTIVIEWPORTIMGUI)	    
	    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	    //#endif
	    //io.ConfigViewportsNoAutoMerge = false;
	    io.ConfigViewportsNoTaskBarIcon = false;
	    
	    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	    
	    // Setup Dear ImGui style
	    //ImGui::StyleColorsDark();
	    ImGui::StyleColorsClassic();
	    //ImGui::StyleColorsLight();
	
	    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	    ImGuiStyle& style = ImGui::GetStyle();
	    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	    {
	        style.WindowRounding = 0.0f;
	        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	    }
	
	    // Setup Platform/Renderer backends
	    ImGui_ImplSDL2_InitForOpenGL(w->ventana, w->gl_context);
	    ImGui_ImplOpenGL2_Init();
	
	    // Load Fonts
	    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	    // - Read 'docs/FONTS.md' for more instructions and details.
	    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	    //io.Fonts->AddFontDefault();
	    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	    //IM_ASSERT(font != nullptr);
	    
	    FILES::inicializa_loadSDLTexture();
	    
		return (ImGuiIO&) io;

	}

	

void preparaRenderizado(ventanaIMGUI *w)
	{
	    // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        
        //#if defined(DOCKSPACE_MAIN)
			DockSpaceUI();	
		//#endif
             
        //SDL_SetRenderDrawColor(w->renderer, 96, 128, 255, 255);
	    //SDL_RenderClear(w->renderer);

	}

void renderizaEscena (ventanaIMGUI *w)
	{	    
	    
	   // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)(w->io.DisplaySize.x), (int)(w->io.DisplaySize.y) );
        glClearColor(w->clear_color.x * w->clear_color.w, w->clear_color.y * w->clear_color.w, w->clear_color.z * w->clear_color.w, w->clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        // For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        
        if (w->io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }
        
        switch (switchtecnologia)
        {		
        	case 1:
        		SDL_RenderPresent(w->renderer);
        	break;
       		case 2:       			
			   SDL_GL_SwapWindow(w->ventana);			   
			break;
   		}
   		
	}
	
	void selecciona_tecnologia (void)
	{
		ImGui::Begin("Selecciona tecnologia");
			if (ImGui::RadioButton("SDL", &r1))
		      {
		        	switchtecnologia=1;
		        	//r2=false;
		      }
		    if (ImGui::RadioButton("IMGUI SDL", &r2))
		      {
		        	switchtecnologia=2;
		        	//r1=false;
		      }
		ImGui::End ();
	}

	void destruye_interface(ventanaIMGUI *w)
	{
			
		SDL_DestroyRenderer(w->renderer);
		
		// Cleanup
	    ImGui_ImplOpenGL2_Shutdown();
	    ImGui_ImplSDL2_Shutdown();
	    ImGui::DestroyContext();
		
		
		
	    SDL_GL_DeleteContext(w->gl_context);	    
	    SDL_DestroyWindow(w->ventana);
	    SDL_Quit();

	}
	
	
	
	void blit(SDL_Renderer *renderer,SDL_Texture *texture, int x, int y)
	{
	    SDL_Rect dest;
	
	    dest.x = x;
	    dest.y = y;
	    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	    SDL_RenderCopy(renderer, texture, NULL, &dest);
	}
	
}