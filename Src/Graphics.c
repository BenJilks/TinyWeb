#include "TinyWeb/Graphics.h"
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

/* Define some consts */
#define TITLE "TinyWeb"
#define WIDTH 800
#define HEIGHT 600

/* The SDL window */
SDL_Window* window;
SDL_GLContext gl_context;
int should_close;
int has_resized;

/* The textures that are in use */
GLuint textures[80];
unsigned int texture_size;

/* The window's outer bounds */
Bounds window_bounds;

/* Creates a new font */
Font CreateFont(Bounds font_bounds, Bounds char_bounds, unsigned int font_id, char char_data[255])
{
	Font font;
	font.m_font_bounds = font_bounds;
	font.m_char_bounds = char_bounds;
	font.m_font_id = font_id;
	memcpy(font.m_char_data, char_data, strlen(char_data) + 1);
	
	font.m_char_width = char_bounds.m_width / font_bounds.m_width;
	font.m_char_height = char_bounds.m_height / font_bounds.m_height;
	return font;
}

/* Inits the graphics engine */
void InitGraphics()
{
	/* Init SDL */
	SDL_Init(SDL_INIT_VIDEO);
	
	/* Create window */
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
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
	texture_size = 0;
	
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/* Loads a new texture */
void LoadTexture(char* file_path)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	int width, height, comp;
	char* image_data = stbi_load(file_path, &width, &height, &comp, 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	textures[texture_size++] = texture;
	
	free(image_data);
}

/* Updates the grapics engine's display */
void UpdateGraphics()
{
	has_resized = 0;

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
			
			/* When the window has been resized */
			case SDL_WINDOWEVENT:
			{
				switch (event.window.event)	
				{
					case SDL_WINDOWEVENT_RESIZED:
					{
						int w, h;
						SDL_GetWindowSize(window, &w, &h);
						
						window_bounds = CreateSimpleBounds(0, 0, w, h);
						glViewport(0, 0, w, h);
						has_resized = 1;
						break;
					}
				}
			}
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

/* Returns if the window has just been resized */
int HasResized()
{
	return has_resized;
}

/* Returns the window's layout bounds */
Bounds GetWindowBounds()
{
	return window_bounds;
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
	
	glTexCoord2i(0, 0);
	glVertex2f(glbounds.m_x, glbounds.m_y);
	
	glTexCoord2i(1, 0);
	glVertex2f(glbounds.m_x + glbounds.m_width, glbounds.m_y);
	
	glTexCoord2i(1, 1);
	glVertex2f(glbounds.m_x + glbounds.m_width, glbounds.m_y - glbounds.m_height);
	
	glTexCoord2i(0, 1);
	glVertex2f(glbounds.m_x, glbounds.m_y - glbounds.m_height);
	glEnd();
}

/* Draws a textured box to the screen */
void DrawTexturedBox(Bounds bounds, unsigned int texture_id)
{
	glBindTexture(GL_TEXTURE_2D, textures[texture_id]);
	DrawBox(bounds, (int[3]){255, 255, 255});
	glBindTexture(GL_TEXTURE_2D, 0);
}

/* Draws a charictor to the screen */
void DrawChar(Bounds bounds, Font font, char c)
{
	unsigned int index = strchr(font.m_char_data, c) - font.m_char_data;

	float gl_char_x = (index % 16) * font.m_char_width;
	float gl_char_y = floor(index / 16) * font.m_char_height;
	glBindTexture(GL_TEXTURE_2D, textures[font.m_font_id]);

	Bounds glbounds = ToOpenGL(bounds, window_bounds);
	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);

	glTexCoord2f(gl_char_x, gl_char_y);
	glVertex2f(glbounds.m_x, glbounds.m_y);
	
	glTexCoord2f(gl_char_x + font.m_char_width, gl_char_y);
	glVertex2f(glbounds.m_x + glbounds.m_width, glbounds.m_y);
	
	glTexCoord2f(gl_char_x + font.m_char_width, gl_char_y + font.m_char_height);
	glVertex2f(glbounds.m_x + glbounds.m_width, glbounds.m_y - glbounds.m_height);
	
	glTexCoord2f(gl_char_x, gl_char_y + font.m_char_height);
	glVertex2f(glbounds.m_x, glbounds.m_y - glbounds.m_height);	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

/* Draws text to the screen */
void DrawText(Bounds bounds, Font font, char text[80])
{
	unsigned int length = strlen(text);
	unsigned int i;
	for (i = 0; i < length; i++)
	{
		DrawChar(CreateSimpleBounds(bounds.m_x + (i * bounds.m_width), bounds.m_y, bounds.m_width, bounds.m_height), font, text[i]);
	}
}

