//
//  main.c
//  XML Workbench
//
//  Created by Miguel Fernandes on 21/05/14.
//  Copyright (c) 2014 UniversidadeMinho. All rights reserved.
//

#include <stdio.h>
#include "xml.h"

int main(int argc, const char * argv[])
{
    
    Attr a1 = cons_CcList("id", "12");
    printf("%s:'%s'\n",a1->u.d1.s1,a1->u.d1.s2);


    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

