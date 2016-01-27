#include "../Middleware/SDL2/include/SDL.h"
#include "../Middleware/SDL2/include/SDL_opengl.h"
#include <gl\GLU.h>
#include <iostream>

using namespace std;


//prototypes
bool initSDL();
bool initGL();
void update();
void render();
void KeyInput();
void endSDL();

//variables
SDL_Window* window;
SDL_GLContext gContext;
SDL_Event e;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
bool gRenderQuad = true;
bool EndLoop = false;



bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Did not Initialize: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		window = SDL_CreateWindow("VoxelTest", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

		if (window == NULL)
		{
			cout << "Window not created: " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			gContext = SDL_GL_CreateContext(window);
			if (gContext == NULL)
			{
				cout << "Did not create gContext: " << SDL_GetError() << endl;
				return false;
			}
			else
			{
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					cout << "Vsync not set: " << SDL_GetError() << endl;
				}

				if (!initGL())
				{
					cout << "OpenGL not working: " << SDL_GetError() << endl;
					return false;
				}
			}
		}
	}

	return true;
}


bool initGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;

	if (glGetError() != GL_NO_ERROR)
	{
		cout << "Error initializing OpenGL: " << gluErrorString(GL_NO_ERROR) << endl;
		return false;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (glGetError() != GL_NO_ERROR)
	{
		cout << "Error initializing OpenGL: " << gluErrorString(GL_NO_ERROR) << endl;
		return false;
	}

	glClearColor(0.f, 0.f, 0.f, 1.f);
	if (glGetError() != GL_NO_ERROR)
	{
		cout << "Error initializing OpenGL: " << gluErrorString(GL_NO_ERROR) << endl;
		return false;
	}
	return true;
}


void update()
{
	render();
	SDL_GL_SwapWindow(window);
}


void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Render quad
	if (gRenderQuad)
	{
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();
	}
}


void KeyInput()
{
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			EndLoop = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				cout << "Left Mouse Down" << endl;
				break;
			case SDL_BUTTON_RIGHT:
				cout << "Right Mouse Down" << endl;
				break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				cout << "Left Mouse Up" << endl;
				break;
			case SDL_BUTTON_RIGHT:
				cout << "Right Mouse Up" << endl;
				break;
			}
			break;


		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				EndLoop = true;
				break;
			}
			break;


		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			}
			break;
		}

	}
}


void endSDL()
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_DeleteContext(gContext);
	SDL_Quit();
}