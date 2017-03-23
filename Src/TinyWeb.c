#include <stdio.h>
#include "TinyWeb/HTMLParser.h"
#include "TinyWeb/CSSParser.h"
#include "TinyWeb/RawData.h"
#include "TinyWeb/Graphics.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	/* Start the graphics engine */
	InitGraphics();
	LayoutNode* layout_tree = CreateLayoutNode(CreateSimpleBounds(0, 0, 800, 600), NULL);
	
	unsigned int i;
	for (i = 0; i < 50; i++)
	{
		LayoutNode* node = CreateLayoutNode(CreateSimpleBounds(0, 0, 50, 50), layout_tree);
		AddNode(layout_tree, node);
		DrawBox(node->m_layout_bounds, (int[3]){rand() % 255, rand() % 255, rand() % 255});
	}
	ClearDisplay();
	
	/* Get the html data */
	char* html = ReadFile("test.html");
	HTMLNode* document = ParseHTML(html);
	
	/* Start the main loop */
	while (!ShouldClose())
	{
		UpdateGraphics();
		
		if (HasResized())
		{
			FreeLayoutBranch(layout_tree);
			layout_tree = CreateLayoutNode(GetWindowBounds(), NULL);
		
			srand(0);
			for (i = 0; i < 50; i++)
			{
				LayoutNode* node = CreateLayoutNode(CreateSimpleBounds(0, 0, 50, 50), layout_tree);
				AddNode(layout_tree, node);
				DrawBox(node->m_layout_bounds, (int[3]){rand() % 255, rand() % 255, rand() % 255});
			}
			ClearDisplay();
		}
	}
	
	/* Free the data */
	FreeBranch(document);
	free(html);
	DestroyGraphics();
	
	FreeLayoutBranch(layout_tree);
	return 0;
}

