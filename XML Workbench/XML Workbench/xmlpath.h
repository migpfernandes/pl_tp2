//
//  xmlpath.h
//  XML Workbench
//
//  Created by Miguel Fernandes on 03/06/14.
//  Copyright (c) 2014 UniversidadeMinho. All rights reserved.
//

#ifndef XML_Workbench_xmlpath_h
#define XML_Workbench_xmlpath_h

#include "list.h"
#include "xmldata.h"

typedef struct sXmlPath{
    char* name;
    NODE* filters;
    int isAtrib;
    int slashPrefixNo;
    int isDirectChild;
} *XmlPath,XmlPathNode;

XmlPath createXmlNode(char *name, NODE* Filters,int isAtrib,int slashprefixno);
NODE* addXmlPathNode(NODE* list, XmlPath node);
void setDirectChild(NODE* list,int directChild);
void printXpathExpression(NODE *list);

NODE* filterSelectedNodes(NodePtr xmlfile,NODE* xmlpath);
void printFilteredNodesForFile(NODE* files, NODE* fileList,NODE* xmlpath);

#endif