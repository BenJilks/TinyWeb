#include "CSSParser.h"

/* Creates a new CSS element */
CSSElement CreateElement(char name[80], char value[80])
{
	CSSElement element;
	memcpy(element.m_name, name, strlen(name) + 1);
	memcpy(element.m_value, value, strlen(value) + 1);
	return element;
}

/* Creates a new CSS quary */
CSSQuary* CreateQuary(char quary[80], CSSQuary* parent)
{
	CSSQuary* quary = (CSSQuary*)malloc(sizeof(CSSQuary));
	memcpy(quary->m_quary, quary, strlen(quary) + 1);
	quary->m_element_size = 0;
	quary->m_child_size = 0;
	quary->m_parent = parent;
	return quary;
}

/* Parse a CSS quary */
#define SKIP_WHITE_SPACE(css, pos)
CSSQuary* ParseQuary(char* css, unsigned int* pos, CSSQuary* parent)
{
	unsigned int i = 0;
	SKIP_WHITE_SPACE(css, pos);
	if (css[*pos] == '}')
		return;
	
	char name[80];
	while (css[*pos] != ' ' && css[*pos] != ':')
		name[i++] = css[(*pos)++];
	name[i] = '\0';
	i = 0;
	
	SKIP_WHITE_SPACE(css, pos);
	
	/* CSS element */
	if (css[*pos] == ':')
	{
		char value[80];
		while (css[*pos] != ';')
			value[i++] = css[(*pos)++];
		value[i] = '\0';
		i = 0;
		
		CSSElement element = CreateElement(name, value);
		
	}
	
	/* CSS Quary */
	else if (css[*pos] == '{')
	{
		
	}
}

/* Parses CSS code into a list of quarys */
CSSStyleSheet ParseCSS(char* css)
{
	
}