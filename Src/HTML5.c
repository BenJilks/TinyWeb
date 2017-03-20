#include "TinyWeb/HTML5.h"
#include <stdlib.h>
#include <memory.h>

/* Proccess a text HTML tag */
Renderable* ProccessText(HTMLNode* node, TinyWebTab* tab)
{
	RenderableText* text = (RenderableText*)malloc(sizeof(RenderableText));
	memcpy(text->m_text, node->m_inner_html, strlen(node->m_inner_html) + 1);
	return (Renderable*)text;
}

/* Proccess a title HTML tag */
void ProccessTitle(HTMLNode* node, TinyWebTab* tab)
{
	memcpy(tab->m_title, node->m_inner_html, strlen(node->m_inner_html) + 1);
}

/* Converts a HTML tree into render components */
void GetRenderTree(HTMLNode* head, TinyWebTab* tab)
{
	Renderable* renderable;
	if (!strcmp(head->m_tag_name, "text"))
		renderable = ProccessText(head, tab);
	else if (!strcmp(head->m_tag_name, "title"))
		ProccessTitle(head, tab);
	tab->m_renderables[tab->m_renderable_size++] = renderable;
	
	/* Proccess all it's children */
	unsigned int i;
	for (i = 0; i < head->m_child_size; i++)
		GetRenderTree(head->m_children[i], tab);
}

