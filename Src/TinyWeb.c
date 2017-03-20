#include <stdio.h>
#include "TinyWeb/HTMLParser.h"
#include "TinyWeb/RawData.h"
#include <stdlib.h>

int main()
{
	char* html = ReadFile("test.html");
	HTMLNode* document = ParseHTML(html);
	
	printf("%s\n", document->m_children[0]->m_inner_html);
	FreeBranch(document);
	free(html);
}

