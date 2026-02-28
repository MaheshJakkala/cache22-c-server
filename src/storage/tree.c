#include "tree.h"

Tree root={
    .n={
        .tag=(TagRoot | TagNode),
        .north=(Tree *)&root,
        .west=0,
        .east=0,
        .path="/"
    }
};
void zero(int8*str,int16 size)
{
    int8* p;
    int16 n;

    for(n=0,p=str;n<size;p++,n++)
    {
        *p=0;
    }
    return;
}
Leaf*find_last_linear(Node*parent){
    Leaf*l;
    errno=NoError;
    assert(parent);
    if(!parent->east) returr(NoError);
    for(l=parent->east;l->east;l=l->east);
    assert(l);
    return l;
}

Leaf* create_leaf(Node* parent,int8* key,int8* value,int16 count)
{
    Leaf*l,*new;
    int16 size;

    assert(parent);
    l=find_last(parent);

     size=sizeof(struct s_leaf);
    new=(Leaf*)malloc(size);
    assert(new);
    
   // new=!l?()
   if(!l)
        parent->east=new;
    else 
        l->east=new;

   zero((int8*)new,size);
    new->tag=TagLeaf;
    new->west=(!l) ? 
        (Tree*)parent:
        (Tree*)l;

   // new->east=null;
    strncpy((char*)new->key,(char*)key,127);
    new->value=(int8* )malloc(count);
    zero(new->value,count);
    assert(new->value);
    strncpy((char* )new->value,(char*)value,count);
    new->size=count;
    return new;
    
}
Node* create_node(Node* parent,int8 * path)
{
    Node*n;
    int16 size;
    errno=NoError;
    assert(parent);
    size=sizeof(struct s_node);
    n=(Node*)malloc((int)size);

    zero((int8*)n,size);
    parent->west=n;
    n->tag=TagNode;
    n->east=0;
    n->north=parent;
    strncpy((char*)n->path,(char*)path,255);
    return n;

}
int main()
{
    Node*n,*n2;
    Leaf*l1,*l2;
    int8*key,*value;
    int16 size;

    n=create_node((Node*)&root,(int8*)"/users");
    assert(n);
    n2=create_node(n,(int8* )"/users/login");
    assert(n2);

    key=(int8*)"mahesh";
    value=(int8*)"abc312aa";
    size=(int16 )strlen((char*)value);
    l1=create_leaf(n2,key,value,size);  
    assert(l1);
   // l2=create_leaf(n2,key,value,size);
   // assert(l2);
    //l2->key="mahesh";
   // l2->value="abc312aa";
    printf(" %s \n",l1->value);



    key=(int8*)"mahi";
    value=(int8*)"kkkk213";
    size=(int16 )strlen((char*)value);
    l2=create_leaf(n2,key,value,size);
    assert(l2);
        
    printf("%s \n",l2->key);
     printf("%p %p \n",n,n2);


    free(n);
    free(n2);
    free(l1->value);
    free(l1);
    free(l2->value);
    free(l2);
    return 0;
}