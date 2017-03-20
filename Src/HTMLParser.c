#include "TinyWeb/HTMLParser.h"
#include <stdlib.h>
#include <memory.h>

/* Creates an HTML attribute */
HTMLAtrribute CreateAttribute(char name[80], char value[80])
{
	HTMLAtrribute attribute;
	memcpy(attribute.m_name, name, strlen(name) + 1);
	memcpy(attribute.m_value, value, strlen(value) + 1);
	return attribute;
}

/* Creates a node in a HTML tree */
HTMLNode* CreateNode(char tag_name[80], HTMLNode* parent)
{
	HTMLNode* node = (HTMLNode*)malloc(sizeof(HTMLNode));
	memcpy(node->m_tag_name, tag_name, strlen(tag_name) + 1);
	node->m_attribute_size = 0;
	node->m_child_size = 0;
	node->m_inner_html_size = 0;
	
	node->m_parent = parent;
	return node;
}

/* Frees a branch of a HTML tree */
void FreeBranch(HTMLNode* head)
{
	/* Free all the children in the current node */
	unsigned int i;
	for (i = 0; i < head->m_child_size; i++)
		FreeBranch(head->m_children[i]);
	
	/* Free this current node */
	free(head);
}

/* Parse a name seprated by a space */ 
#define SKIP_WHITE_SPACE(html, pos) while(html[(*pos)] == ' ' || html[(*pos)] == '\n') { (*pos)++; };
void ParseName(char* html, unsigned int* pos, char data[80])
{
	char c;
	unsigned int i = 0;
	
	c = html[(*pos)++];
	while (c != ' ' && c != '>' && c != '=' && c != '/')
	{
		data[i++] = c;
		c = html[(*pos)++];
	}
	(*pos)--;
	
	data[i] = '\0';
}

/* Parse the tag's attributes */
void ParseAttributes(char* html, unsigned int* pos, HTMLNode* node)
{
	SKIP_WHITE_SPACE(html, pos);
	char c = html[*pos];
	if (c == '>' || c == '/')
	{
		(*pos)++;
		return;
	}
	
	char name[80];
	ParseName(html, pos, name);
	
	SKIP_WHITE_SPACE(html, pos); // Skip to the '='
	(*pos)++; // Skip the '='
	SKIP_WHITE_SPACE(html, pos); // Skip to the values
	(*pos)++; // Skip the '"'
	
	char value[80];
	unsigned int i = 0;
	while ((c = html[(*pos)++]) != '"')
		value[i++] = c;
	value[i] = '\0';
	
	HTMLAtrribute attribute = CreateAttribute(name, value);
	node->m_attributes[node->m_attribute_size++] = attribute;
	ParseAttributes(html, pos, node);
}

/* Parse the inner html code */
void ParseInnerHTML(char* html, unsigned int* pos, HTMLNode* parent)
{
	while (*pos < strlen(html))
	{
		char c = html[(*pos)++];
		if (c == '<')
		{
			SKIP_WHITE_SPACE(html, pos);
		
			/* If end tag */
			if (html[(*pos)] == '/')
				break;
			
			/* If start tag */
			char tag_name[80];
			ParseName(html, pos, tag_name);
			
			/* Create new node */	
			HTMLNode* node = CreateNode(tag_name, parent);
			parent->m_children[parent->m_child_size++] = node;
			
			/* Parse the data */
			ParseAttributes(html, pos, node);
			if (html[(*pos) - 1] == '/')
			{
				SKIP_WHITE_SPACE(html, pos);
				(*pos)++; // Skip the '>'
				continue;
			}
			
			ParseInnerHTML(html, pos, node);
			
			/* On tag ended */
			SKIP_WHITE_SPACE(html, pos);
			ParseName(html, pos, tag_name);
			SKIP_WHITE_SPACE(html, pos);
			(*pos)++; // Skip the '>'
			
			continue;
		}
		
		parent->m_inner_html[parent->m_inner_html_size++] = c;
	}
	
	parent->m_inner_html[parent->m_inner_html_size] = '\0';
}

/* Parses HTML text into a HTML tree */
HTMLNode* ParseHTML(char* html)
{
	HTMLNode* document = CreateNode("document", NULL);
	unsigned int pos = 0;
	
	ParseInnerHTML(html, &pos, document);
	return document;
}
