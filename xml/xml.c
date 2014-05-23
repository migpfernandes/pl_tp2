/* -----------------------------------
 * Constructor Function Implementations
 * -----------------------------------
 */

Tag  cons_Tag( char * a1, AttrList a2, ElemList a3)
{
    Tag aux0;

  aux0 = (Tag) malloc(sizeof(struct sTag));
  aux0->flag = PScons_Tag;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  aux0->u.d1.s3 = a3;
  return(aux0);
}


ElemList  cons_ElemList( ElemList a1, Elem a2)
{
    ElemList aux0;

  aux0 = (ElemList) malloc(sizeof(struct sElemList));
  aux0->flag = PScons_ElemList;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}

ElemList  cons_ElemList_Elem( Elem a1)
{
    ElemList aux0;

  aux0 = (ElemList) malloc(sizeof(struct sElemList));
  aux0->flag = PScons_ElemList_Elem;
  aux0->u.d2.s1 = a1;
  return(aux0);
}


Elem  cons_Elem_Texto( char * a1)
{
    Elem aux0;

  aux0 = (Elem) malloc(sizeof(struct sElem));
  aux0->flag = PScons_Elem_Texto;
  aux0->u.d1.s1 = a1;
  return(aux0);
}

Elem  cons_Elem_Reservada( char * a1)
{
    Elem aux0;

  aux0 = (Elem) malloc(sizeof(struct sElem));
  aux0->flag = PScons_Elem_Reservada;
  aux0->u.d2.s1 = a1;
  return(aux0);
}

Elem  cons_Elem_SimpleTag( char * a1, AttrList a2)
{
    Elem aux0;

  aux0 = (Elem) malloc(sizeof(struct sElem));
  aux0->flag = PScons_Elem_SimpleTag;
  aux0->u.d3.s1 = a1;
  aux0->u.d3.s2 = a2;
  return(aux0);
}


AttrList  cons_AttrList( AttrList a1, Attr a2)
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


Attr  cons_Atribs( char * a1, char * a2)
{
    Attr aux0;

  aux0 = (Attr) malloc(sizeof(struct sAttr));
  aux0->flag = PScons_Atribs;
  aux0->u.d1.s1 = a1;
  aux0->u.d1.s2 = a2;
  return(aux0);
}


