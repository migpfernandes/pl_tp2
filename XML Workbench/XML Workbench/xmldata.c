
/* -----------------------------
   Module xml.c
      2008-05-15: created by jcr
   -----------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "xmldata.h"

AttrList consAttrList( char *n, char *v, AttrList l )
{
  AttrList aux;

  aux = (AttrList)malloc(sizeof(Attr));
  aux->name = n;
  aux->value = v;
  aux->next = l;

  return aux;
}


void showAttrList( AttrList l )
{
  if(l)
    {
      printf("A%s   %s\n",l->name,l->value);
      showAttrList(l->next);
    }
}

void showAttrListXML( AttrList l )
{
    if(l)
    {
        printf(" %s=\"%s\"",l->name,l->value);
        showAttrListXML(l->next);
    }
}


AttrList add2AttrList( AttrList l1, AttrList l2)
{
  l2->next = l1;
  return l2;
}
 
NodePtr consNodefromText( TextNodePtr n )
{
  NodePtr aux;

  aux = (NodePtr)malloc(sizeof(Node));
  aux->type = TEXTNODE;
  aux->val.t = n;
  return aux;
}

NodePtr consNodefromElem( ElemNodePtr n )
{
  NodePtr aux;

  aux = (NodePtr)malloc(sizeof(Node));
  aux->type = ELEMNODE;
  aux->val.e = n;
  return aux;
}

NodePtr consNodefromEmptyElem( EmptyElemNodePtr n )
{
  NodePtr aux;

  aux = (NodePtr)malloc(sizeof(Node));
  aux->type = EMPTYELEMNODE;
  aux->val.ee = n;
  return aux;
}


void    showNodeESIS( NodePtr node )
{
  switch(node->type)
  {
    case TEXTNODE : printf("-%s\n",node->val.t->contents);
                    if(node->val.t->sibling)
                      showNodeESIS(node->val.t->sibling);
                    break;
    case ELEMNODE : printf("(%s\n",node->val.e->name);
                    showAttrList(node->val.e->attrs);
                    if(node->val.e->child)
                      showNodeESIS(node->val.e->child);
                    printf(")%s\n",node->val.e->name);
                    if(node->val.e->sibling)
                      showNodeESIS(node->val.e->sibling);
                    break;
          
    case EMPTYELEMNODE : printf("(%s\n",node->val.ee->name);
                    showAttrList(node->val.ee->attrs);
                    printf(")%s\n",node->val.ee->name);
                    if(node->val.ee->sibling)
                      showNodeESIS(node->val.ee->sibling);
  }
}

void    showNodeXMLAux(NodePtr node, char *indentation)
{
    char newindentation[80];
    strcpy(newindentation, indentation);
    strcat(newindentation, "\t");
    
    switch(node->type)
    {
        case TEXTNODE :
            printf("%s",node->val.t->contents);
            if(node->val.t->sibling)
                showNodeXMLAux(node->val.t->sibling,indentation);
            break;
            
        case ELEMNODE :
            printf("\n%s<%s",indentation,node->val.e->name);
            showAttrListXML(node->val.e->attrs);
            printf(">");
            if(node->val.e->child){
                showNodeXMLAux(node->val.e->child,newindentation);
                if(node->val.e->child->type == TEXTNODE)
                    printf("</%s>",node->val.e->name);
                else
                    printf("\n%s</%s>",indentation,node->val.e->name);
            } else {
                printf("</%s>",node->val.e->name);
            }
            
            if(node->val.e->sibling)
                showNodeXMLAux(node->val.e->sibling,indentation);
            break;
            
        case EMPTYELEMNODE :
            printf("\n%s<%s",indentation,node->val.ee->name);
            showAttrListXML(node->val.ee->attrs);
            printf("/>");
            if(node->val.ee->sibling)
                showNodeXMLAux(node->val.ee->sibling,indentation);
            break;
    }
}

void    showNodeXML(NodePtr node)
{
    char indentation[10] = "\t";
    switch(node->type)
    {
        case TEXTNODE :
            printf("%s",node->val.t->contents);
            if(node->val.t->sibling)
                showNodeXMLAux(node->val.t->sibling,"");
            break;
            
        case ELEMNODE :
            printf("<%s",node->val.e->name);
            showAttrListXML(node->val.e->attrs);
            printf(">");
            if(node->val.e->child){
                showNodeXMLAux(node->val.e->child,indentation);
                if(node->val.e->child->type == TEXTNODE)
                    printf("</%s>",node->val.e->name);
                else
                    printf("\n</%s>",node->val.e->name);
            } else {
                printf("</%s>",node->val.e->name);
            }
            
            if(node->val.e->sibling)
                showNodeXMLAux(node->val.e->sibling,indentation);
            break;
            
        case EMPTYELEMNODE :
            printf("<%s",node->val.ee->name);
            showAttrListXML(node->val.ee->attrs);
            printf("/>");
            if(node->val.ee->sibling)
                showNodeXMLAux(node->val.ee->sibling,indentation);
            break;
    }
    printf("\n");
}

NodePtr add2NodeList( NodePtr nl, NodePtr node )
{
  if(nl)
  {
    switch(nl->type)
    {
      case TEXTNODE : nl->val.t->sibling = add2NodeList(nl->val.t->sibling,node);
                      break;
      case ELEMNODE : nl->val.e->sibling = add2NodeList(nl->val.e->sibling,node);
   					  break;
      case EMPTYELEMNODE : nl->val.ee->sibling = add2NodeList(nl->val.ee->sibling,node);
	}
    return nl;
  }
  else
    return node;
}


ElemNodePtr consElemNode( char * name, AttrList attrlist, NodePtr s, NodePtr c )
{
  ElemNodePtr aux;

  aux = (ElemNodePtr)malloc(sizeof(ElemNode));
  aux->name = strdup(name);
  aux->attrs = attrlist;
  aux->sibling = s;
  aux->child = c;

  return aux;
}


EmptyElemNodePtr consEmptyElemNode( char * name, AttrList attrlist, NodePtr s)
{
  EmptyElemNodePtr aux;

  aux = (EmptyElemNodePtr)malloc(sizeof(EmptyElemNode));
  aux->name = strdup(name);
  aux->attrs = attrlist;
  aux->sibling = s;

  return aux;
}

TextNodePtr consTextNode( char *c, NodePtr s )
{
  TextNodePtr aux;

  aux = (TextNodePtr)malloc(sizeof(TextNode));
  aux->contents = strdup(c);
  aux->sibling = s;

  return aux;
}

