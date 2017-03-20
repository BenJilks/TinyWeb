#ifndef HTMLPARSER
#define HTMLPARSER

/* An HTML attribute */
typedef struct HTMLAttribute
{
	char m_name[80];
	char m_value[80];
} HTMLAttribute;

/* A node in a HTML tree */
typedef struct HTMLNode
{
	/* HTML data */
	char m_tag_name[80];
	HTMLAttribute m_attributes[80];
	unsigned int m_attribute_size;
	
	/* Inner HTML data */
	char m_inner_html[1028 * 4];
	unsigned int m_inner_html_size;
	
	/* Tree data */
	struct HTMLNode* m_parent;
	struct HTMLNode* m_children[80];
	unsigned int m_child_size;
} HTMLNode;

/* Creates an HTML attribute */
HTMLAttribute CreateAttribute(char name[80], char value[80]);

/* Creates a node in a HTML tree */
HTMLNode* CreateNode(char tag_name[80], HTMLNode* parent);

/* Frees a branch of a HTML tree */
void FreeBranch(HTMLNode* head);

/* Parses HTML text into a HTML tree */
HTMLNode* ParseHTML(char* html);

/* Gets an attribute by its name */
HTMLAttribute GetAttributeById(HTMLNode* node, char name[80]);

#endif

