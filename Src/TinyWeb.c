#include <stdio.h>
#include "TinyWeb/HTMLParser.h"
#include "TinyWeb/CSSParser.h"
#include "TinyWeb/RawData.h"
#include <stdlib.h>

int main()
{
	char* html = ReadFile("test.html");
	HTMLNode* document = ParseHTML(html);
	
	
	
	FreeBranch(document);
	free(html);
	return 0;
}

