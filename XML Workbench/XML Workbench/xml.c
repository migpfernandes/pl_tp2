#include "xml.h"

/* -----------------------------------
 * Constructor Function Implementations
 * -----------------------------------
 */

Documento  cons_Documento( ElemList a1)
{
    Documento aux0;

  aux0 = (Documento) malloc(sizeof(struct sDocumento));
  aux0->flag = PScons_Documento;
  aux0->u.d1.s1 = a1;
  return(aux0);
}


ElemList  cons_ElemList( Elem a1, ElemList a2)
{
    ElemList aux0;

  aux0 = (ElemList) malloc(sizeof(struct sElemList));
  aux0->flag = PScons_ElemList;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

ElemList  cons_ElemList_NIL()
{
    ElemList aux0;

  aux0 = (ElemList) malloc(sizeof(struct sElemList));
  aux0->flag = PScons_ElemList_NIL;
  return(aux0);
}


Elem  cons_Elem_Element( char * a1, AttrList a2, ElemList a3, char * a4)
{
    Elem aux0;

  aux0 = (Elem) malloc(sizeof(struct sElem));
  aux0->flag = PScons_Elem_Element;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  aux0->u.d1.s3 = a3;
  aux0->u.d1.s4 = a4;
  return(aux0);
}

Elem  cons_Elem_EMPTY( char * a1, AttrList a2)
{
    Elem aux0;

  aux0 = (Elem) malloc(sizeof(struct sElem));
  aux0->flag = PScons_Elem_EMPTY;
  aux0->u.d2.s1 = a1;
  aux0->u.d2.s2 = a2;
  return(aux0);
}

Elem  cons_Elem_Entity( char * a1)
{
    Elem aux0;

  aux0 = (Elem) malloc(sizeof(struct sElem));
  aux0->flag = PScons_Elem_Entity;
  aux0->u.d3.s1 = a1;
  return(aux0);
}


AttrList  cons_AttrList( Attr a1, AttrList a2)
{
    AttrList aux0;

  aux0 = (AttrList) malloc(sizeof(struct sAttrList));
  aux0->flag = PScons_AttrList;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

AttrList  cons_AttrList_NIL()
{
    AttrList aux0;

  aux0 = (AttrList) malloc(sizeof(struct sAttrList));
  aux0->flag = PScons_AttrList_NIL;
  return(aux0);
}


Attr  cons_CcList( char * a1, char * a2)
{
    Attr aux0;

  aux0 = (Attr) malloc(sizeof(struct sAttr));
  aux0->flag = PScons_CcList;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}


