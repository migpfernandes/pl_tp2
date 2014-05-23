/* -----------------------------------
 * Production Selectors
 * -----------------------------------
 */

#define PScons_Tag  2000

#define PScons_ElemList  2001
#define PScons_ElemList_Elem  2002

#define PScons_Elem_Texto  2003
#define PScons_Elem_Reservada  2004
#define PScons_Elem_SimpleTag  2005

#define PScons_AttrList  2006
#define PScons_AttrList_NIL  2007

#define PScons_Atribs  2008

/* -----------------------------------
 * Abstract Data Types Definition
 * -----------------------------------
 */

/* To avoid dependencies, waiting for a cleaner solution...*/

/* --- dummy Tag ---*/
struct sTag;
typedef struct sTag *Tag;

/* --- dummy ElemList ---*/
struct sElemList;
typedef struct sElemList *ElemList;

/* --- dummy Elem ---*/
struct sElem;
typedef struct sElem *Elem;

/* --- dummy AttrList ---*/
struct sAttrList;
typedef struct sAttrList *AttrList;

/* --- dummy Attr ---*/
struct sAttr;
typedef struct sAttr *Attr;

/* Now the types definition...*/

/* --- Tag ---*/
struct sTag 
{ int flag;
  union {  
    struct {
        char * s1;
        AttrList s2;
        ElemList s3;
      } d1;

  } u;
};

/* --- ElemList ---*/
struct sElemList 
{ int flag;
  union {  
    struct {
        ElemList s1;
        Elem s2;
      } d1;
    struct {
        Elem s1;
      } d2;

  } u;
};

/* --- Elem ---*/
struct sElem 
{ int flag;
  union {  
    struct {
        char * s1;
      } d1;
    struct {
        char * s1;
      } d2;
    struct {
        char * s1;
        AttrList s2;
      } d3;

  } u;
};

/* --- AttrList ---*/
struct sAttrList 
{ int flag;
  union {  
    struct {
        AttrList s1;
        Attr s2;
      } d1;
    struct {
      } d2;

  } u;
};

/* --- Attr ---*/
struct sAttr 
{ int flag;
  union {  
    struct {
        char * s1;
        char * s2;
      } d1;

  } u;
};

/* -----------------------------------
 * Constructor Function Signatures
 * -----------------------------------
 */

Tag  cons_Tag( char * a1, AttrList a2, ElemList a3);

ElemList  cons_ElemList( ElemList a1, Elem a2);
ElemList  cons_ElemList_Elem( Elem a1);

Elem  cons_Elem_Texto( char * a1);
Elem  cons_Elem_Reservada( char * a1);
Elem  cons_Elem_SimpleTag( char * a1, AttrList a2);

AttrList  cons_AttrList( AttrList a1, Attr a2);
AttrList  cons_AttrList_NIL();

Attr  cons_Atribs( char * a1, char * a2);

