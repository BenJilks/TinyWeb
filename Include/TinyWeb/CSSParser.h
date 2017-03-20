#ifndef CSS_PARSER
#define CSS_PARSER

/* Struct storing a CSS element */
typedef struct CSSElement
{
	char m_name[80];
	char m_value[80];
} CSSElement;

/* Struct storing a CSS quary */
typedef struct CSSQuary
{
	char m_quary[80];
	struct CSSQuary* m_parent;
	struct CSSQuary* m_children[80];
	unsigned int m_child_size;
	
	CSSElement m_elements[80];
	unsigned int m_element_size;
} CSSQuary;

/* Creates a new CSS element */
CSSElement CreateElement(char name[80], char value[80]);

/* Creates a new CSS quary */
CSSQuary* CreateQuary(char quary[80], CSSQuary* parent);

/* Parses CSS code into a list of quarys */
CSSQuary* ParseCSS(char* css);

#endif
