#ifndef HTML5
#define HTML5

#include "HTMLParser.h"
#include "Layout.h"

void InitFonts();

/* Converts a HTML tree into render components */
void RenderHTML(HTMLNode* head, LayoutNode* layout);

#endif

