#include "TinyWeb/HTML5.h"
#include "TinyWeb/Graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define TEXT_SIZE 20

Font font;
void InitFonts()
{
	LoadTexture("font.png");
	font = CreateFont(CreateSimpleBounds(0, 0, 1280, 1280), CreateSimpleBounds(0, 0, 80, 80), 0 ,
		" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ !\"#$%&'[]~+,-./0123456789:,<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_~abcdefghijklmnopqrstuvwxyz{~}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~£");
}

/* Proccess a text HTML tag */
void ProccessText(HTMLNode* node, LayoutNode* layout)
{
	printf("Displaying text '%s'\n", node->m_inner_html);
	
	Bounds bounds = CreateSimpleBounds(0, 0, strlen(node->m_inner_html) * TEXT_SIZE, TEXT_SIZE);
	LayoutNode* layout_node = CreateLayoutNode(bounds, layout);
	AddNode(layout, layout_node);
	
	Bounds text_bounds = layout_node->m_layout_bounds;
	text_bounds.m_width = TEXT_SIZE;
	DrawText(text_bounds, font, node->m_inner_html);
	//DrawBox(layout_node->m_layout_bounds, (int[5]){rand() % 255, rand() % 255, rand() % 255});
}

/* Proccess a button HTML tag */
void ProccessButton(HTMLNode* node, LayoutNode* layout)
{
	printf("Displaying button '%s'\n", node->m_inner_html);
}

/* Proccess a title HTML tag */
void ProccessTitle(HTMLNode* node)
{
	printf("Page title: '%s'\n", node->m_inner_html);
}

/* Converts a HTML tree into render components */
void RenderHTML(HTMLNode* head, LayoutNode* layout)
{
	int is_head = 0;
	if (layout == NULL)
	{
		srand(0);
		is_head = 1;
		layout = CreateLayoutNode(GetWindowBounds(), NULL);
	}

	if (!strcmp(head->m_tag_name, "text"))
		ProccessText(head, layout);
	else if (!strcmp(head->m_tag_name, "title"))
		ProccessTitle(head);
	else if (!strcmp(head->m_tag_name, "button"))
		ProccessButton(head, layout);
	
	/* Proccess all it's children */
	unsigned int i;
	for (i = 0; i < head->m_child_size; i++)
		RenderHTML(head->m_children[i], layout);
	
	if (is_head)
		FreeLayoutBranch(layout);
}

