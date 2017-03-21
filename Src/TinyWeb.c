#include <stdio.h>
#include "TinyWeb/HTMLParser.h"
#include "TinyWeb/CSSParser.h"
#include "TinyWeb/RawData.h"
#include "TinyWeb/Graphics.h"
#include <stdlib.h>

int main()
{
	/* Start the graphics engine */
	InitGraphics();
	ClearDisplay();
	
	/* Get the html data */
	char* html = ReadFile("test.html");
	HTMLNode* document = ParseHTML(html);
	
	/* Start the main loop */
	while (!ShouldClose())
	{
		UpdateGraphics();
	}
	
	/* Free the data */
	FreeBranch(document);
	free(html);
	DestroyGraphics();
	return 0;
}

