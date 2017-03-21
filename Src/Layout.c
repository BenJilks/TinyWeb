#include "TinyWeb/Layout.h"

/* Creates a simple layout bound */
Bounds CreateSimpleBounds(float x, float y, float width, float height)
{
	Bounds bounds;
	bounds.m_x = x;
	bounds.m_y = y;
	bounds.m_width = width;
	bounds.m_height = height;
	return bounds;
}

/* Creates a full layout bound */
Bounds CreateBounds(float x, float y, float width, float height, 
	float margin_top, float margin_bottom, float margin_left, float margin_right)
{
	Bounds bounds;
	bounds.m_x = x;
	bounds.m_y = y;
	bounds.m_width = width;
	bounds.m_height = height;
	bounds.m_margin_top = margin_top;
	bounds.m_margin_bottom = margin_bottom;
	bounds.m_margin_left = margin_left;
	bounds.m_margin_right = margin_right;
	return bounds;
}

/* Converts a pixel layout into OpenGL layout bounds */
Bounds ToOpenGL(Bounds bounds, Bounds window)
{
	Bounds glbounds;
	
	/* Calc position */
	glbounds.m_x = ((bounds.m_x / window.m_width) - 0.5) * 2;
	glbounds.m_y = ((1.0 - (bounds.m_y / window.m_height)) - 0.5) * 2;
	
	/* Calc size */
	glbounds.m_width = bounds.m_width / window.m_width;
	glbounds.m_height = bounds.m_height / window.m_height;
	
	return glbounds;
}
