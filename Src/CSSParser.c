#include "TinyWeb/CSSParser.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

/* Creates a new CSS element */
CSSElement CreateElement(char name[80], char value[80])
{
	CSSElement element;
	memcpy(element.m_name, name, strlen(name) + 1);
	memcpy(element.m_value, value, strlen(value) + 1);
	return element;
}

/* Creates a new CSS quary */
CSSQuary* CreateQuary(char quary_str[80], CSSQuary* parent)
{
	CSSQuary* quary = (CSSQuary*)malloc(sizeof(CSSQuary));
	memcpy(quary->m_quary, quary_str, strlen(quary_str) + 1);
	quary->m_element_size = 0;
	quary->m_child_size = 0;
	quary->m_parent = parent;
	return quary;
}

/* Parse a CSS quary */
#define SKIP_WHITE_SPACE(css, pos) while(css[(*pos)] == ' ' || css[(*pos)] == '\n') { (*pos)++; };
CSSQuary* ParseQuary(char* css, unsigned int* pos, CSSQuary* parent)
{
	while (*pos < strlen(css))
	{
		unsigned int i = 0;
		SKIP_WHITE_SPACE(css, pos);
		if (css[*pos] == '}')
			return;
	
		char name[80];
		while (css[*pos] != ':' && css[*pos] != '{')
			name[i++] = css[(*pos)++];
		name[i] = '\0';
		i = 0;
		
		/* CSS element */
		if (css[*pos] == ':')
		{
			char value[80];
			while (css[(*pos)++] != ';')
				value[i++] = css[*pos];
			i--;
			value[i] = '\0';
			i = 0;
		
			CSSElement element = CreateElement(name, value);
			parent->m_elements[parent->m_element_size++] = element;
		}
	
		/* CSS Quary */
		else if (css[*pos] == '{')
		{
			(*pos)++;
			
			/* Read the quary */
			CSSQuary* quary = CreateQuary(name, parent);
			ParseQuary(css, pos, quary);
		
			/* Add quary to parent */
			parent->m_children[parent->m_child_size++] = quary;
			(*pos)++;
		}
	}
}

/* Parses CSS code into a list of quarys */
CSSQuary* ParseCSS(char* css)
{
	CSSQuary* quary = CreateQuary("Stylesheet", NULL);
	unsigned int pos = 0;
	
	ParseQuary(css, &pos, quary);
	return quary;
}

#define COLOUR(r, g, b, a) (int[4]){r, g, b, a}

/* Reads a colour from a CSS style sheet */
#define READCOLOUR(value, colour) \
{ \
	if (!strcmp(value, "white")) memcpy(colour, COLOUR(255, 255, 255, 255), 4*sizeof(int)); \
	else if (!strcmp(value, "black")) memcpy(colour, COLOUR(0, 0, 0, 255), 4*sizeof(int)); \
	else if (!strcmp(value, "red")) memcpy(colour, COLOUR(255, 0, 0, 255), 4*sizeof(int)); \
	else memcpy(colour, COLOUR(0, 0, 0, 0), 4*sizeof(int)); \
}

/* Creates a new style from a CSS quary */
Style CreateStyle(CSSQuary* quary)
{
	Style style;

	/* Set default colours */
	memcpy(style.m_colour, COLOUR(0, 0, 0, 255), 4*sizeof(int));
	memcpy(style.m_background_colour, COLOUR(255, 255, 255, 0), 4*sizeof(int));
	style.m_font_size = 12;
	
	/* Read data */
	unsigned int i;
	for (i = 0; i < quary->m_element_size; i++)
	{
		CSSElement element = quary->m_elements[i];
		if (!strcmp(element.m_name, "color")) READCOLOUR(element.m_value, style.m_colour)
		else if (!strcmp(element.m_name, "bakcground-color")) READCOLOUR(element.m_value, style.m_background_colour)
		else if (!strcmp(element.m_name, "font-size")) style.m_font_size = atof(element.m_value);
	}
	return style;
}



