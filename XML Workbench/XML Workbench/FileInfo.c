//
//  FileInfo.c
//  XML Workbench
//
//  Created by Miguel Fernandes on 27/05/14.
//  Copyright (c) 2014 UniversidadeMinho. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileInfo.h"

/**
 * Função auxiliar utilizada para encontrar Files numa lista por ID
 */
int findID(void *list, void *Id)
{
	return strcmp(((FileInfo) list)->Id, (char*)Id)?0:1;
}

int printNode(FileInfo info){
    printf("%s\t\t%s\n",info->Id,info->filename);
    return 0;
};

/**
 * Gera um FileInfo e devolve um apontador para a estrutura.
 * @param id Identificador do ficheiro
 * @param filename Nome do ficheiro
 * @param ficheiroXml Apontador para a representação em memória do ficheiro XML
 */
FileInfo createFileInfo(char *ID,char *filename,NodePtr ficheiroXml){
    FileInfo res = (void*) malloc(sizeof(FileInfoNode));
    
    res->Id = strdup(ID);
    res->filename = strdup(filename);
    res->ficheiroXml = ficheiroXml;
    
    return res;
};

/**
 * Comparer utilizado para ordenar a lista de ficheiros por id.
 */
int fileInfoComparer(void* node1,void* node2){
	return strcmp(((FileInfo) node1)->Id,((FileInfo) node2)->Id);
}

/**
 * Adiciona um ficheiro à lista de ficheiros conhecidos e retorna a nova lista
 * @param id Identificador do ficheiro
 * @param filename Nome do ficheiro
 */
NODE* addFile(NODE* list,FileInfo ficheiro){
    return list_insert_sorted(list,ficheiro,fileInfoComparer);
};


/**
 * Caso encontre o ficheiro carregado, mostra-o na consola
 * @param list Lista de ficheiro carregados
 * @param id Id do ficheiro a mostrar
 */
void showFile(NODE* list,char* Id){
    FileInfo file = findFile(list,Id);
    if(file){
        printf("Ficheiro ID:\"%s\" NAME:\"%s\"\n",file->Id,file->filename);
        showNodeXML(file->ficheiroXml);
    } else {
        printf("Ficheiro não encontrado.\n");
    }
};

/**
 * Imprime uma lista de todos os ficheiros carregados na base de dados
 * @param list Lista de ficheiro carregados
 */
void listFiles(NODE* list){
    if (list) {
        printf("Ficheiros:\nID\t\tNAME\n");
        printf("-----------------------------\n");
        list_foreach(list,(void*) printNode);
    } else {
        printf("Não existem ficheiros para listar.\n");
    }
};

/**
 * Destroi toda a lista e desaloca a memória
 * @param list Lista de ficheiro carregados
 */
void destructList(NODE* list){
    list_destruct(list);
}

FileInfo findFile(NODE* list,char *Id){
    NODE* match =list_find((NODE*) list,findID ,Id);
    
    if (match){
        return (FileInfo) match->data;
    } else {
        return NULL;
    }
}
