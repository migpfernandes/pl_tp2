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

int main(int argc,char *argv[])
{
    NodePtr node2 = consNodefromText(consTextNode("teste", NULL));
    NodePtr node1 = consNodefromElem(consElemNode("teste2", NULL, NULL, node2));

    NodePtr node3 = consNodefromEmptyElem(consEmptyElemNode("teste3", NULL, NULL));
    NodePtr node4 = consNodefromEmptyElem(consEmptyElemNode("teste4", NULL, NULL));

    
    node1 = add2NodeList(node1, node3);
    node1 = add2NodeList(node1, node4);
    
    NodePtr rootNode = consNodefromElem(consElemNode("root", NULL, NULL, node1));
    //NodePtr rootNode = consNodefromElem(consElemNode("root", NULL, NULL, NULL));
    
    //showNodeESIS(rootNode);
    showNodeXML(rootNode);
    
    return 1;
}
