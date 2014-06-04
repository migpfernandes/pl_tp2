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
#include "xmldata.h"
#include "list.h"
#include "FileInfo.h"

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


NODE* getAtributeValuesByKey(NodePtr xmlnode,char *atribute){
    char* value;
    NODE* res = NULL,*child, *sibling;
    NodePtr aux;
    if (xmlnode) {
        value = getAtributeValue(xmlnode,atribute);
        if (value) res = list_create(value);
        
        aux = getNodeChild(xmlnode);
        child = getAtributeValuesByKey(aux, atribute);
        
        aux = getNodeSibling(xmlnode);
        sibling = getAtributeValuesByKey(aux, atribute);
        
        res = list_concat(res, child);
        res = list_concat(res, sibling);
        
        return res;
    } else {
        return NULL;
    }
}

NODE* getTagNodesByName(NodePtr xmlnode,char *tagName){
    NODE* res = NULL,*child, *sibling;
    NodePtr aux;
    if (xmlnode) {
        if (nodeTagNameIs(xmlnode,tagName)) res = list_create(xmlnode);
        
        aux = getNodeChild(xmlnode);
        child = getTagNodesByName(aux, tagName);
        
        aux = getNodeSibling(xmlnode);
        sibling = getTagNodesByName(aux, tagName);
        
        res = list_concat(res, child);
        res = list_concat(res, sibling);
        
        return res;
    } else {
        return NULL;
    }
}


NODE* filterSelectedNodes(NodePtr xmlfile,NODE* xmlpath){
    NODE* res = list_create(xmlfile);
    NODE* temp;
    XmlPath node;
    
    while ((xmlpath) && (res->data)) {
        temp = NULL;
        node = (XmlPath) xmlpath->data;
        
        /*
        if (node ->isDirectChild) {
            if((((NodePtr)(res ->data))->type == TEXTNODE) || (((NodePtr)(res ->data))->type == EMPTYELEMNODE)){
                
            } else {
                if (temp) {
                    temp = list_insert_after(temp,(((NodePtr) res->data)->val.e->child));
                } else {
                    temp = list_create(((NodePtr) res->data)->val.e->child);
                }
            }
        }
        */
        
        //temp = list_create(NULL);
        
        if (node->isDirectChild){
            
            if (node->slashPrefixNo==1) {
                if (node->isAtrib) {
                    
                } else {
                    
                }
            } else if (node->slashPrefixNo==2) {
        
            }
        } else {
            if (node->slashPrefixNo==0) {
                //Só acontece no primeiro nó
                if (node->isAtrib) {
                    //Processa atributos
                    char *value;
                    while (res) {
                        value = getAtributeValue((NodePtr)res->data, node->name);
                        if (value) {
                            temp = list_insert_beginning(temp, value);
                        }
                        res = res->next;
                    }
                    return temp;
                } else {
                    //Processa nós
                    NodePtr child;
                    while (res) {
                        child = getNodeChild((NodePtr) res->data);
                        while (child) {
                            if (nodeTagNameIs(child,node->name)) {
                                temp = list_insert_beginning(temp, child);
                            }
                            child = getNodeSibling(child);
                        }
                        res = res->next;
                    }
                }
                
                
            } else if (node->slashPrefixNo==1){
                if (node->isAtrib) {
                    //Processa atributos
                    char *value;
                    NodePtr child;
                    while (res) {
                        child = getNodeChild((NodePtr) res->data);
                        while (child) {
                            value = getAtributeValue(child,node->name);
                            if (value) {
                                temp = list_insert_beginning(temp, value);
                            }
                            child = getNodeSibling(child);
                        }
                        res = res->next;
                    }
                    return temp;
                } else {
                    //Processa nós
                    NodePtr child;
                    while (res) {
                        child = getNodeChild((NodePtr) res->data);
                        while (child) {
                            if (nodeTagNameIs(child,node->name)) {
                                temp = list_insert_beginning(temp, child);
                            }
                            child = getNodeSibling(child);
                        }
                        res = res->next;
                    }
                }
                
                
            } else if (node->slashPrefixNo==2) {
                if (node->isAtrib) {
                    //Processa atributos
                    while (res) {
                        temp = list_concat(temp,getAtributeValuesByKey(res->data,node->name));
                        res = res->next;
                    }
                    return temp;
                } else {
                    //Processa nós
                    while (res) {
                        temp = list_concat(temp,getTagNodesByName(res->data,node->name));
                        res = res->next;
                    }
                }
            }
        }
        
        
        /*
        char* name;
        NODE* filters;
        int isAtrib;
        int slashPrefixNo;
        int isDirectChild;
        */
        
        
        res = temp;
        xmlpath = xmlpath -> next;
    }
    
    return res;
}

void printFilteredNodes(FileInfo fileinfo,NODE* xmlpath){
    NODE* res;
    
    printf("==========Ficheiro %s \"%s\"==========\n",fileinfo->Id,fileinfo->filename);
    res = filterSelectedNodes(fileinfo->ficheiroXml, xmlpath);
    if (res) {
        printf("Número de nós selecionados: %d\n",list_length(res));
        showNodeXML((NodePtr) res->data);
    } else {
        printf("A query ao ficheiro não devolveu resultados.");
    }
}

void printFilteredNodesForFile(NODE* files, NODE* fileList,NODE* xmlpath){
    NODE* aux;
    FileInfo fileinfo;
    
    //Se a fileList for nula, é porque recebeu um *
    if (!fileList) {
        aux = files;
        while (aux) {
            fileinfo = (FileInfo) aux->data;
            printFilteredNodes(fileinfo,xmlpath);
            aux = aux->next;
        }
    } else {
        aux = fileList;
        while (aux) {
            fileinfo = findFile(files, (char*) aux->data);
            printFilteredNodes(fileinfo,xmlpath);
            aux = aux->next;
        }
    }
}