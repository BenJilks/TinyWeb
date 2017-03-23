#ifndef GRAPHICS
#define GRAPHICS

#include "Layout.h"

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

/* Drawing functions */

/* Draws a solid colour box to the screen */
void DrawBox(Bounds bounds, int colour[3]);

/* Draws a textured box to the screen */
void DrawTexturedBox(Bounds bounds);

/* Draws text to the screen */
void DrawText(Bounds bounds, char text[80]);

#endif

