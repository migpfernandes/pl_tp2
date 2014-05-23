/* -----------------------------------
 * Production Selectors
 * -----------------------------------
 */

#define PScons_Documento  2000

#define PScons_ElemList  2001
#define PScons_ElemList_NIL  2002

#define PScons_Elem_Element  2003
#define PScons_Elem_EMPTY  2004
#define PScons_Elem_Entity  2005

#define PScons_AttrList  2006
#define PScons_AttrList_NIL  2007

#define PScons_CcList  2008

/* -----------------------------------
 * Abstract Data Types Definition
 * -----------------------------------
 */

/* To avoid dependencies, waiting for a cleaner solution...*/

/* --- dummy Documento ---*/
struct sDocumento;
typedef struct sDocumento *Documento;

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

/* --- Documento ---*/
struct sDocumento 
{ int flag;
  union {  
    struct {
        ElemList s1;
      } d1;

  } u;
};

/* --- ElemList ---*/
struct sElemList 
{ int flag;
  union {  
    struct {
        Elem s1;
        ElemList s2;
      } d1;
    struct {
      } d2;

  } u;
};

/* --- Elem ---*/
struct sElem 
{ int flag;
  union {  
    struct {
        char * s1;
        AttrList s2;
        ElemList s3;
        char * s4;
      } d1;
    struct {
        char * s1;
        AttrList s2;
      } d2;
    struct {
        char * s1;
      } d3;

  } u;
};

/* --- AttrList ---*/
struct sAttrList 
{ int flag;
  union {  
    struct {
        Attr s1;
        AttrList s2;
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

Documento  cons_Documento( ElemList a1);

ElemList  cons_ElemList( Elem a1, ElemList a2);
ElemList  cons_ElemList_NIL();

Elem  cons_Elem_Element( char * a1, AttrList a2, ElemList a3, char * a4);
Elem  cons_Elem_EMPTY( char * a1, AttrList a2);
Elem  cons_Elem_Entity( char * a1);

AttrList  cons_AttrList( Attr a1, AttrList a2);
AttrList  cons_AttrList_NIL();

Attr  cons_CcList( char * a1, char * a2);

