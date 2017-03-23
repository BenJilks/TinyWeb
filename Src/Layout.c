#include "TinyWeb/Layout.h"
#include <stdlib.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

/* Creates a new layout node */
LayoutNode* CreateLayoutNode(Bounds bounds, LayoutNode* parent)
{
	LayoutNode* node = (LayoutNode*)malloc(sizeof(LayoutNode));
	node->m_parent = parent;
	node->m_child_size = 0;
	node->m_layout_bounds = bounds;
	
	node->m_max_x = 0;
	node->m_max_y = 0;
	node->m_curr_x = 0;
	node->m_curr_y = 0;
	return node;
}

/* Adds a layout node to anouther and calculates the location */
void AddNode(LayoutNode* parent, LayoutNode* node)
{
	parent->m_max_x = MAX(parent->m_max_x, parent->m_curr_x + node->m_layout_bounds.m_width);
	parent->m_max_y = MAX(parent->m_max_y, parent->m_curr_y + node->m_layout_bounds.m_height);
	
	if (parent->m_curr_x + node->m_layout_bounds.m_width >= parent->m_layout_bounds.m_width)
	{
		parent->m_curr_x = 0;
		parent->m_curr_y += node->m_layout_bounds.m_height;
	}
	
	node->m_layout_bounds.m_x = parent->m_curr_x;
	node->m_layout_bounds.m_y = parent->m_curr_y;
	parent->m_curr_x += node->m_layout_bounds.m_width;
	parent->m_children[parent->m_child_size++] = node;
}

/* Frees a branch in a layout */
void FreeLayoutBranch(LayoutNode* node)
{
	unsigned int i;
	for (i = 0; i < node->m_child_size; i++)
		FreeLayoutBranch(node->m_children[i]);
	
	free(node);
}

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
	glbounds.m_width = (bounds.m_width / window.m_width) * 2;
	glbounds.m_height = (bounds.m_height / window.m_height) * 2;
	
	return glbounds;
}

