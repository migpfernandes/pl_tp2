//
//  FileInfo.h
//  XML Workbench
//
//  Created by Miguel Fernandes on 27/05/14.
//  Copyright (c) 2014 UniversidadeMinho. All rights reserved.
//

#ifndef XML_Workbench_FileInfo_h
#define XML_Workbench_FileInfo_h

#include "xmldata.h"
#include "list.h"

typedef struct sFileInfo{
    char *Id;
    char *filename;
    NodePtr ficheiroXml;
} *FileInfo,FileInfoNode;

FileInfo createFileInfo(char *Id,char *filename,NodePtr ficheiroXml);
NODE* addFile(NODE* list,FileInfo ficheiro);
void showFile(NODE* list,char* Id);
void listFiles(NODE* list);
void destructList(NODE* list);
FileInfo findFile(NODE* list,char *Id);

#endif
