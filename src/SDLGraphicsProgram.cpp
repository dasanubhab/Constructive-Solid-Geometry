#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	m_window = NULL;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();


    // Setup our Renderer
    m_renderer = new Renderer(w,h);    
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    }


    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL(){
	//Success flag
	bool success = true;

	return success;
}

// ====================== Create the planets =============
// NOTE: I will admit it is a little lazy to have these as globals,
//       we could build on our ObjectManager structure to manage the
//       each object that is inserted and automatically create a 'SceneNode'
//       for it for example. Or otherwise, build a 'SceneTree' class that
//       manages creating nodes and setting their type.
//       (e.g. A good use of the Factory Design Pattern if you'd like to
//             invetigate further--but it is beyond the scope of this assignment).


// Create the Earth
Object* sphere2;
SceneNode* Earth;
SceneNode* Earth1;
SceneNode* Earth2;
SceneNode* Earth3;
SceneNode* Mars;
SceneNode* Jupiter;
SceneNode* block;
SceneNode* block1;
SceneNode* block2;
// Create the Sun
Object* sphere;
SceneNode* Sun;
SceneNode* Sun1;
SceneNode* Sun2;
Object* cube;
Object* cube1;
Object* cube2;
// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::Loop(){

    // ================== Initialize the planets ===============
    static float rotate = 0.0f;

    // Setup objects
    cube = new Cube();
    cube1 = new Cube();
    cube2 = new Cube();
    block = new SceneNode(cube);
    block1 = new SceneNode(cube1);
    block2 = new SceneNode(cube2);
    sphere2 = new Sphere();
    Earth = new SceneNode(sphere2);
    Earth1 = new SceneNode(sphere2);
    Earth2 = new SceneNode(sphere2);
    Earth3 = new SceneNode(sphere2);
    Mars = new SceneNode(sphere2);
    Jupiter = new SceneNode(sphere2);
    sphere = new Sphere();
    Sun = new SceneNode(sphere);
    Sun1 = new SceneNode(sphere);
    Earth->setOp("subtract");
    block2->setOp("subtract");
    Earth3->setOp("subtract");
    // Render our initial scene
    m_renderer->setRoot(Sun);
    // Make the children ie constructing the trees
    Sun->AddChild(Earth);
    Sun1->AddChild(Earth1);
    Sun1->AddChild(block1);
    Earth1->AddChild(block2);
    Sun1->AddChild(Earth2);
    Earth2->AddChild(Earth3);
    block->AddChild(Jupiter);
    block->AddChild(Mars);
    m_renderer->GetCamera(0)->SetCameraEyePosition(0.0f,0.0f,20.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 5.0f;

    // While application is running
    while(!quit){
        
        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboad input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
             m_renderer->GetCamera(0)->MouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            m_renderer->GetCamera(0)->MoveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            m_renderer->GetCamera(0)->MoveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            m_renderer->GetCamera(0)->MoveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            m_renderer->GetCamera(0)->MoveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
                            break;
                        case SDLK_RCTRL:
                            m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
                            break;
                        //Handles key inputs
                        case SDLK_1:
                            Earth->setOp("subtract");
                            m_renderer->setRoot(Sun);
                            break;
                        case SDLK_2:
                            Earth->setOp("add");
                            m_renderer->setRoot(Sun);
                            break;
                        case SDLK_3:
                            Jupiter->setOp("add");
                            Mars->setOp("add");
                            m_renderer->setRoot(block);
                            break;
                        case SDLK_4:
                            Jupiter->setOp("subtract");
                            Mars->setOp("subtract");
                            m_renderer->setRoot(block);
                            break;
                        case SDLK_5:
                            m_renderer->setRoot(Sun1);
                            break;
                    }
                break;
            }
        }
        //transform everything appropriately for scenes
        Sun->GetLocalTransform().LoadIdentity();
        Sun->GetLocalTransform().Scale(8.0f,8.0f,8.0f);
        Sun1->GetLocalTransform().LoadIdentity();
        Sun1->GetLocalTransform().Scale(8.0f,8.0f,8.0f);
        Earth->GetLocalTransform().LoadIdentity();
        Earth->GetLocalTransform().Translate(1.0f,0.0f,0.0f);
        Earth1->GetLocalTransform().LoadIdentity();
        Earth1->GetLocalTransform().Translate(0.75f,0.3f,0.0f);
        Earth1->GetLocalTransform().Scale(0.8f,0.6f,0.4f);
        Earth1->GetLocalTransform().Rotate(rotate,1.0f,0.0f,0.0f);
        Earth2->GetLocalTransform().LoadIdentity();
        Earth2->GetLocalTransform().Translate(-0.88f,-0.2f,0.0f);
        Earth2->GetLocalTransform().Scale(0.8f,0.6f,0.4f);
        Earth3->GetLocalTransform().LoadIdentity();
        Earth3->GetLocalTransform().Translate(0.1f,1.1f,0.0f);
        Earth3->GetLocalTransform().Scale(0.675f,0.83333f,1.2f);
        Mars->GetLocalTransform().LoadIdentity();
        Mars->GetLocalTransform().Scale(0.333333f,2.0f,1.0f);
        Mars->GetLocalTransform().Translate(2.0f,0.0f,0.0f);
        Jupiter->GetLocalTransform().LoadIdentity();
        Jupiter->GetLocalTransform().Scale(0.333333f,2.0f,1.0f);
        Jupiter->GetLocalTransform().Translate(-3.0f,0.0f,0.0f);
        Sun->GetWorldTransform().LoadIdentity();
        Sun1->GetWorldTransform().LoadIdentity();
        block->GetWorldTransform().LoadIdentity();
        block->GetLocalTransform().LoadIdentity();
        block->GetLocalTransform().Scale(3.0f,1.0f,2.0f);
        block1->GetLocalTransform().LoadIdentity();
        block1->GetLocalTransform().Translate(0.0f,1.0f,0.0f);
        block1->GetLocalTransform().Scale(0.75f,0.75f,0.25f);
        block2->GetLocalTransform().LoadIdentity();
        block2->GetLocalTransform().Translate(0.0f,0.0f,1.0f);
        block2->GetLocalTransform().Scale(0.5f,0.6f,0.111111f);
        m_renderer->Update();
        m_renderer->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());

        rotate+=0.1;
        if(rotate>360){rotate=0;}
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
