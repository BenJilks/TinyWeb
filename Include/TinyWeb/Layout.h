#ifndef LAYOUT
#define LAYOUT

/* Stores data about an elements physical position */
typedef struct Bounds
{
	/* Positions */
	float m_x, m_y;
	float m_width, m_height;
	
	/* Margins */
	float m_margin_top, m_margin_bottom;
	float m_margin_left, m_margin_right;
} Bounds;

/* Creates a simple layout bound */
Bounds CreateSimpleBounds(float x, float y, float width, float height);

/* Creates a full layout bound */
Bounds CreateBounds(float x, float y, float width, float height, 
	float margin_top, float margin_bottom, float margin_left, float margin_right);

/* Converts a pixel layout into OpenGL layout bounds */
Bounds ToOpenGL(Bounds bounds, Bounds window);

#endif
