#ifndef GRAPHICS
#define GRAPHICS

/* Inits the graphics engine */
void InitGraphics();

/* Updates the grapics engine's display */
void UpdateGraphics();

/* Clears the graphics display to black */
void ClearDisplay();

/* Returns if the browser should be closed */
int ShouldClose();

/* Destroys the graphics engine */
void DestroyGraphics();

#endif
