#include "TinyWeb/HTML5.h"
#include "TinyWeb/CSSParser.h"
#include "TinyWeb/Graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define TEXT_SIZE 12

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
	HTMLAttribute style_attr = GetAttributeById(node, "style");
	
	CSSQuary* css = ParseCSS(style_attr.m_value);
	Style style = CreateStyle(css);
	
	Bounds bounds = CreateSimpleBounds(0, 0, strlen(node->m_inner_html) * style.m_font_size, style.m_font_size);
	LayoutNode* layout_node = CreateLayoutNode(bounds, layout);
	AddNode(layout, layout_node);
	
	Bounds text_bounds = layout_node->m_layout_bounds;
	text_bounds.m_width = style.m_font_size;
	DrawText(text_bounds, font, node->m_inner_html, style.m_colour);
}

/* Proccess a button HTML tag */
void ProccessButton(HTMLNode* node, LayoutNode* layout)
{
	printf("Displaying button '%s'\n", node->m_inner_html);
	
	HTMLAttribute style_attr = GetAttributeById(node, "style");
	
	CSSQuary* css = ParseCSS(style_attr.m_value);
	Style style = CreateStyle(css);
	
	Bounds bounds = CreateSimpleBounds(0, 0, (strlen(node->m_inner_html) * style.m_font_size) + 10, style.m_font_size + 10);
	LayoutNode* layout_node = CreateLayoutNode(bounds, layout);
	AddNode(layout, layout_node);
	
	Bounds text_bounds = layout_node->m_layout_bounds;
	text_bounds.m_x += 5; text_bounds.m_y += 5;
	text_bounds.m_width = style.m_font_size;
	text_bounds.m_height = style.m_font_size;
	
	DrawBox(layout_node->m_layout_bounds, (int[3]){200, 200, 200});
	DrawText(text_bounds, font, node->m_inner_html, style.m_colour);
}

/* Proccess an input tag */
void ProccessInput(HTMLNode* node, LayoutNode* layout)
{
	printf("Displaying input tag\n");
	
	Bounds bounds = CreateSimpleBounds(0, 0, 200, 20);
	LayoutNode* layout_node = CreateLayoutNode(bounds, layout);
	AddNode(layout, layout_node);
	
	DrawBox(layout_node->m_layout_bounds, (int[3]){200, 200, 200});
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
	else if (!strcmp(head->m_tag_name, "input"))
		ProccessInput(head, layout);
	
	/* Proccess all it's children */
	unsigned int i;
	for (i = 0; i < head->m_child_size; i++)
		RenderHTML(head->m_children[i], layout);
	
	if (is_head)
		FreeLayoutBranch(layout);
}

