/* -----------------------------
   Module xmldata.h
      2008-05-06: created by jcr
   -----------------------------
*/

#ifndef _XMLDATA
#define _XMLDATA

/* ---- Data Types ---- */
#define TEXTNODE 1001
#define ELEMNODE 1002
#define EMPTYELEMNODE 1003

/* -- Dummy Declarations -- */
struct sTextNode;
typedef struct sTextNode *TextNodePtr, TextNode;
struct sElemNode;
typedef struct sElemNode *ElemNodePtr, ElemNode;
struct sEmptyElemNode;
typedef struct sEmptyElemNode *EmptyElemNodePtr, EmptyElemNode;
/* ------------------------ */

/* ---- Attributes ---- */

typedef struct sAttrList
  {
    char *name;
    char *value;
    struct sAttrList *next;
  } Attr, *AttrList;

AttrList consAttrList( char *n, char *v, AttrList l );
void showAttrList( AttrList l );
AttrList add2AttrList( AttrList l1, AttrList l2);
 
/* ---- Element Nodes ---- */
typedef union
  {
    TextNodePtr t;
    ElemNodePtr e;  
    EmptyElemNodePtr ee;  
  } uNode;

typedef struct sNode
  {
    int type;
    uNode val;
  } Node, *NodePtr;

NodePtr consNodefromText( TextNodePtr n );
NodePtr consNodefromElem( ElemNodePtr n );
NodePtr consNodefromEmptyElem( EmptyElemNodePtr n );
void    showNodeESIS( NodePtr node );
void    showNodeXML(NodePtr node);
NodePtr add2NodeList( NodePtr nl, NodePtr node );
NodePtr getNodeChild(NodePtr np);
NodePtr getNodeSibling(NodePtr nl);
int nodeTagNameIs(NodePtr nl,char* name);

struct sTextNode
  {
    char * contents;
    NodePtr sibling;
  };
TextNodePtr consTextNode( char *c, NodePtr s );

struct sElemNode
  {
    char *name;
    AttrList attrs;
    NodePtr sibling;
    NodePtr child;
  };
ElemNodePtr consElemNode( char * name, AttrList attrlist, NodePtr s, NodePtr c );
char* getAtributeValue(NodePtr node, char *key);
int containsAtribute(NodePtr node, char *key);

struct sEmptyElemNode
  {
    char *name;
    AttrList attrs;
    NodePtr sibling;
  };
EmptyElemNodePtr consEmptyElemNode( char * name, AttrList attrlist, NodePtr s);

#endif
