/*
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
//FILE *outFile_p;
int main(int argc,char *argv[])
{
	if(argc<3)
	{
   printf("Please specify the input file & output file\n");
   exit(0);
  }
 FILE *fp=fopen(argv[1],"r");
 if(!fp)
 {
  printf("couldn't open file for reading\n");
  exit(0);
 }

//  outFile_p=fopen(argv[2],"w");
//  if(!outFile_p)
//  {
//   printf("couldn't open temp for writting\n");
//   exit(0);
//  }

  yyin=fp;
	//yyout = outFile_p;
	//yyparse();
	teste();
 fclose(fp);
	//fclose(outFile_p);
	return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include "xmldata.h"
#include "FileInfo.h"
#include "xmlpath.h"

#include <unistd.h>
#include <errno.h>

void teste();

int main(int argc,char *argv[])
{
    NodePtr node2 = consNodefromText(consTextNode("teste", NULL));
    NodePtr node5 = consNodefromElem(consElemNode("teste5", NULL, NULL, node2));
    NodePtr node1 = consNodefromElem(consElemNode("teste2", NULL, NULL, node5));

    NodePtr node10 = consNodefromText(consTextNode("testexfd", NULL));
    NodePtr node8 = consNodefromElem(consElemNode("teste5", NULL, NULL, node10));
    NodePtr node9 = consNodefromElem(consElemNode("teste2", NULL, NULL, node8));
    
    NodePtr node3 = consNodefromEmptyElem(consEmptyElemNode("teste3", NULL, NULL));
    NodePtr node4 = consNodefromEmptyElem(consEmptyElemNode("teste4", NULL, NULL));

    node1 = add2NodeList(node1, node9);
    node1 = add2NodeList(node1, node3);
    node1 = add2NodeList(node1, node4);
    
    NodePtr rootNode = consNodefromElem(consElemNode("root", NULL, NULL, node1));
    //NodePtr rootNode = consNodefromElem(consElemNode("root", NULL, NULL, NULL));
    
    //showNodeESIS(rootNode);
    showNodeXML(rootNode);
    
    //teste();
    
    
    XmlPath createXmlNode(char *name, NODE* Filters,int isAtrib,int slashprefixno);
    NODE* addXmlPathNode(NODE* list, XmlPath node);
    
    XmlPath xmlpath = createXmlNode("teste",NULL,0,2);
    
    XmlPath atribNode = createXmlNode("atr2",NULL,0,0);
    XmlPath atribNode2 = createXmlNode("atr3",NULL,1,2);
    NODE* atrib = addXmlPathNode(NULL,atribNode);
    atrib = addXmlPathNode(atrib,atribNode2);

    
    XmlPath atribNode3 = createXmlNode("atr4",NULL,1,2);
    NODE* atrib2 = addXmlPathNode(NULL,atribNode3);
    
    NODE* atribs = list_create(atrib);
    atribs = list_insert_after(atribs, atrib2);
    
    XmlPath xmlpath2 = createXmlNode("atr",atribs,1,1);
    
    NODE* fullpath = addXmlPathNode(NULL,xmlpath);
    fullpath = addXmlPathNode(fullpath,xmlpath2);
    
    printXpathExpression(fullpath);
    
    XmlPath xmlpath5 = createXmlNode("teste2",NULL,0,2);
    XmlPath xmlpath6 = createXmlNode("teste5",NULL,0,1);

    NODE* fullpath2 = addXmlPathNode(NULL,xmlpath5);
    fullpath2 = addXmlPathNode(fullpath2,xmlpath6);

    printXpathExpression(fullpath2);
    
    NODE* res = filterSelectedNodes(rootNode, fullpath2);
    
    while (res) {
        showNodeXML((NodePtr) res->data);
        res = res->next;
    }
    
    XmlPath xmlpath7 = createXmlNode("teste5",NULL,0,2);
    
    NODE* fullpath3 = addXmlPathNode(NULL,xmlpath7);
    
    printXpathExpression(fullpath3);
    
    res = filterSelectedNodes(rootNode, fullpath3);
    
    while (res) {
        showNodeXML((NodePtr) res->data);
        res = res->next;
    }
    
    return 1;
}

void currentPath() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Current working dir: %s\n", cwd);
    else
        perror("getcwd() error");
}



void teste()
{
    FILE* fich;
    
    currentPath();
    
    fich = fopen("xml_examples/simple.xml", "r");
    if(fich) printf("Leu");
    else printf("Não leu");
    
    fclose(fich);
    
    NodePtr node2 = consNodefromText(consTextNode("teste", NULL));
    NodePtr node1 = consNodefromElem(consElemNode("teste2", NULL, NULL, node2));
    
    NodePtr node3 = consNodefromEmptyElem(consEmptyElemNode("teste3", NULL, NULL));
    NodePtr node4 = consNodefromEmptyElem(consEmptyElemNode("teste4", NULL, NULL));
    
    
    node1 = add2NodeList(node1, node3);
    node1 = add2NodeList(node1, node4);
    
    NodePtr rootNode = consNodefromElem(consElemNode("root", NULL, NULL, node1));
    //NodePtr rootNode = consNodefromElem(consElemNode("root", NULL, NULL, NULL));
    
    //showNodeESIS(rootNode);
    //showNodeXML(rootNode);
    
    FileInfo ficheiro = createFileInfo("aa", "aa.xml", rootNode);
    FileInfo ficheiro2 = createFileInfo("cc", "cc.xml", rootNode);
    FileInfo ficheiro3 = createFileInfo("bb", "bb.xml", rootNode);
    
    NODE* list = NULL;
    list =addFile(list, ficheiro);
    list =addFile(list, ficheiro2);
    list =addFile(list, ficheiro3);
    
    listFiles(list);
    printf("\n\n\n");
    showFile(list, "aa");
    
    printf("\n\n\n");
    showFile(list, "bb");
    
    printf("\n\n\n");
    showFile(list, "ee");
    
    destructList(list);
}


