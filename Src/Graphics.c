#include "TinyWeb/Graphics.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"

/* Define some consts */
#define TITLE "TinyWeb"
#define WIDTH 800
#define HEIGHT 600

/* The SDL window */
SDL_Window* window;
SDL_GLContext gl_context;
int should_close;

/* The window's outer bounds */
Bounds window_bounds;

/* Inits the graphics engine */
void InitGraphics()
{
	/* Init SDL */
	SDL_Init(SDL_INIT_VIDEO);
	
	/* Create window */
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	should_close = 0;
	window_bounds = CreateSimpleBounds(0, 0, WIDTH, HEIGHT);
	
	/* Error checking */
	if (window == NULL)
	{
		printf("Unable to create SDL window: %s\n", SDL_GetError());
		exit(1);
	}
	
	/* Init OpenGL */
	gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	
	gladLoadGL();
	glClearColor(0, 0, 0, 1);
	SDL_GL_SetSwapInterval(0);
}

/* Updates the grapics engine's display */
void UpdateGraphics()
{
	/* Poll input events */
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			/* When the window has been closed */
			case SDL_QUIT:
				should_close = 1;
				break;
		}	
	}
}

/* Clears the graphics display to black */
void ClearDisplay()
{
	SDL_GL_SwapWindow(window);
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Returns if the browser should be closed */
int ShouldClose()
{
	return should_close;
}

/* Destroys the graphics engine */
void DestroyGraphics()
{
	/* Destroy the browser window */
	SDL_DestroyWindow(window);
	
	/* Destroy the OpenGL context */
	SDL_GL_DeleteContext(gl_context);
	
	/* Destroy SDL */
	SDL_Quit();
}

/* Draws a solid colour box to the screen */
void DrawBox(Bounds bounds, int colour[3])
{
	Bounds glbounds = ToOpenGL(bounds, window_bounds);

	glBegin(GL_QUADS);
	glColor3f(colour[0]/255.0f, colour[1]/255.0f, colour[2]/255.0f);
	glVertex2f(glbounds.m_x, glbounds.m_y);
	glVertex2f(glbounds.m_x + glbounds.m_width, glbounds.m_y);
	glVertex2f(glbounds.m_x + glbounds.m_width, glbounds.m_y - glbounds.m_height);
	glVertex2f(glbounds.m_x, glbounds.m_y - glbounds.m_height);
	glEnd();
}

