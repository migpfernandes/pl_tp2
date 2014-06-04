//
//  xmlpath.c
//  XML Workbench
//
//  Created by Miguel Fernandes on 03/06/14.
//  Copyright (c) 2014 UniversidadeMinho. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmlpath.h"


XmlPath createXmlNode(char *name, NODE* Filters,int isAtrib,int slashprefixno){
    XmlPath node = (void*) malloc(sizeof(XmlPathNode));
    
    node->name = strdup(name);
    node->filters = Filters;
    node->isAtrib = isAtrib;
    node->slashPrefixNo = slashprefixno;
    
    return node;
}

NODE* addXmlPathNode(NODE* list, XmlPath node){
    if (list) {
        return list_insert_after(list, (void *) node);
    } else {
        return list_create((void *) node);
    }
}

void setDirectChild(NODE* list,int directChild){
    ((XmlPath) list->data)->isDirectChild = directChild;
}

int printPathNode(void* node);

int printAtrib(void *node){
    printf("[");
    
    list_foreach(node, printPathNode);
    
    printf("]");
    return 0;
}

int printPathNode(void* node){
    XmlPath no = (XmlPath) node;
    if (no->isDirectChild) printf(".");
    if (no->slashPrefixNo==1) printf("/");
    if (no->slashPrefixNo==2) printf("//");
    if (no->isAtrib) printf("@");
    printf("%s",no->name);

    list_foreach(no->filters, printAtrib);
    
    return 0;
}

void printXpathExpression(NODE *list){
    list_foreach(list, printPathNode);
    printf("\n");
}
