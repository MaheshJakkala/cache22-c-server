#include "cache22/cache22.h"
#include "core/tree.h"
#include<stdio.h>
#include<stdlib.h>

void main()
{
	   Tree* example;
   int32 x;
   int8 *p;
    example=example_tree();
    x=example_leaves();
    (void)x;
    /*p=lookup((int8*)"/a",(int8*)"aardwolf");
    if(p)
    {
        printf("%s\n",p);
    }
    else printf("no\n");*/
    print_tree(1,example);

    return;
}
