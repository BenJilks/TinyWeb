#ifndef GRAPHICS
#define GRAPHICS

#include "Layout.h"

typedef struct Font
{
	Bounds m_font_bounds;
	Bounds m_char_bounds;
	
	float m_char_width;
	float m_char_height;
	unsigned int m_font_id;
	char m_char_data[255];
} Font;

/* Creates a new font */
Font CreateFont(Bounds font_bounds, Bounds char_bounds, unsigned int font_id, char char_data[255]);

/* Inits the graphics engine */
void InitGraphics();

/* Updates the grapics engine's display */
void UpdateGraphics();

/* Clears the graphics display to black */
void ClearDisplay();

/* Returns if the browser should be closed */
int ShouldClose();

/* Returns if the window has just been resized */
int HasResized();

/* Returns the window's layout bounds */
Bounds GetWindowBounds();

/* Destroys the graphics engine */
void DestroyGraphics();

/* Loads a new texture */
void LoadTexture(char* file_path);

/* Drawing functions */

/* Draws a solid colour box to the screen */
void DrawBox(Bounds bounds, int colour[3]);

/* Draws a textured box to the screen */
void DrawTexturedBox(Bounds bounds, unsigned int texture_id);

/* Draws a charictor to the screen */
void DrawChar(Bounds bounds, Font font, char c);

/* Draws text to the screen */
void DrawText(Bounds bounds, Font font, char text[80]);

#endif

