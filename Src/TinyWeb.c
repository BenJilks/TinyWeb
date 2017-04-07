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
	
	/* Load the font texture */
	InitFonts();
	
	/* Get the html data */
	char* html = ReadFile("test.html");
	HTMLNode* document = ParseHTML(html);
	
	ClearDisplay();
	RenderHTML(document, NULL);
	ClearDisplay();
	
	/* Start the main loop */
	while (!ShouldClose())
	{
		UpdateGraphics();
		
		if (HasResized())
		{
			RenderHTML(document, NULL);
			ClearDisplay();
		}
	}
	
	/* Free the data */
	FreeBranch(document);
	free(html);
	DestroyGraphics();
	
	//FreeLayoutBranch(layout_tree);
	return 0;
}

