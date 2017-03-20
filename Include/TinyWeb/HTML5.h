#ifndef HTML5
#define HTML5

#include "HTMLParser.h"

#define RENDERABLE \
	/* Store information about the physical bounds */ \
	unsigned int m_width, m_height; \
	unsigned int m_x, m_y; \
	 \
	/* Store the rendering type */ \
	unsigned int m_id;


/* Stores data about a renderable object */
typedef struct Renderable { RENDERABLE } Renderable;

/* Renderable text object */
typedef struct RenderableText
{
	RENDERABLE
	char m_text[80];
} RenderableText;

/* Store data about a web tab */
typedef struct TinyWebTab
{
	/* The renderable components */
	Renderable* m_renderables[80];
	unsigned int m_renderable_size;
	
	/* Data about the tab */
	char m_title[80];
} TinyWebTab;

/* Converts a HTML tree into render components */
void GetRenderTree(HTMLNode* head, TinyWebTab* tab);

#endif

