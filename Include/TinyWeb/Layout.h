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

/* Stores a node in a layout tree */
typedef struct LayoutNode
{
	/* Data about the postion of this node */
	struct LayoutNode* m_parent;
	struct LayoutNode* m_children[80];
	unsigned int m_child_size;
	
	/* Store the bound info */
	Bounds m_layout_bounds;
	unsigned int m_max_x, m_max_y;
	unsigned int m_curr_x, m_curr_y;
} LayoutNode;

/* Creates a new layout node */
LayoutNode* CreateLayoutNode(Bounds bounds, LayoutNode* parent);

/* Frees a branch in a layout */
void FreeLayoutBranch(LayoutNode* node);

/* Adds a layout node to anouther and calculates the location */
void AddNode(LayoutNode* parent, LayoutNode* node);

/* Creates a simple layout bound */
Bounds CreateSimpleBounds(float x, float y, float width, float height);

/* Creates a full layout bound */
Bounds CreateBounds(float x, float y, float width, float height, 
	float margin_top, float margin_bottom, float margin_left, float margin_right);

/* Converts a pixel layout into OpenGL layout bounds */
Bounds ToOpenGL(Bounds bounds, Bounds window);

#endif

