//tree.c
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


Leaf*find_leaf_linear(int8*path,int8*key)
{
    Leaf*ret,*l;
    Node*n;
    n=find_node(path);
    if(!n) return (Leaf*)0;
    for(ret=(Leaf*)0,l=n->east;l;l=l->east)
    {
        if(!strcmp((char*)l->key,(char*)key))
        {
            ret=l;
            break;
        }
    }
    return ret;
}
int8*lookup_linear(int8*path,int8*key)
{
    Leaf*p;
    p=find_leaf(path,key);
   // if(p)
   //    return p->value;
    //return (int8*)0;
    return (p) ?
        p->value:
        (int8*)0;
}
Node* find_node_linear(int8* path)
{
    Node*p;
    Node*ret;
    for(ret=(Node*)0,p=(Node*)&root;p;p=p->west)
    {
        if(!strcmp((char*)p->path,(char*)path))
        {
            ret=p;
            break;
        }
    }
    return ret;
}
int8* indent(int8 n)
{
    int16 i;
    static int8 buff[256];
    int8*p;

    if (n <= 0) n = 1;
if (n >= 120) n = 119;

  //  assert((n>0 && n<120));
    zero(buff,256);
    for(i=0,p=buff;i<n;i++,p+=2)
    {
        strncpy((char*)p,"  ",2);
    }
    return buff;
}
void print_tree(int fd,Tree*_root)
{
    int8 indentation;
    int16 size;
    int8 buff[256];
    Node* n;
    Leaf* l,*last;

    indentation=0;
    for(n=(Node*)_root;n;n=n->west)
    {
        Print(indent(++indentation));
        Print(n->path);
        Print("\n");
        
        if(n->east)
        {
            last=find_last(n);
            if(last)
                 for(l=last;(Node*)l->west!=n;l=(Leaf*)l->west)
                 {
                    
                     Print(indent(++indentation));
                    Print(n->path);
                    Print("/");
                    Print(l->key);
                    Print("->");
                    write(fd,(char*)l->value,(int)l->size);
                    Print("\n");
                 }
        }
    }
    return ;
}
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
    if(!parent->east) return(Leaf*)0;
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
        l;

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
Tree* example_tree()
{
    int8 c;
    Node *n,*p;
    int8 path[256];
    int32 x;

    zero(path,256);
    x=0;
    for(n=(Node*)&root,c='a';c<='z';c++)
    {
        x=(int32)strlen((char *)path);
        *(path+(x++))='/';
        *(path+x)=c;
        //printf("%s\n",(path));

        p=n;
        n=create_node(p,path);
      

    }
    return (Tree*)&root;
}
int8* example_path(int8 path)
{
    int32 x;
    static int8 buff[256];
    int8 c;

    zero(buff,256);
    for(c='a';c<=path;c++)
    {
        x=(int32)strlen((char*)buff);
        *(buff+x++)='/';
        *(buff + x)=c;
    }

    return buff;
}
int8* example_duplicate(int8* str)
{
    int16 n,x;
    static int8 buff[256];

    zero(buff,256);
    strncpy((char*)buff,(char*)str,255);
    n=(int16)strlen((char*)buff);
    x=(n*2);
    if(x> 254)
        return buff;
    else
        strncpy((char*)buff+n,strdup((char*)buff),255);
        //strncpy((char*)buff+n, (char*)buff, 255 - n);
    return buff;
}
int32* example_leaves()
{

    FILE *fd;
    int32 x,y;
     int8 buff[256];
    int8 *path,*val;
    Node*n;

    //fd=open(ExampleFile, O_RDONLY);
    fd=fopen(ExampleFile,"r");
    assert(fd);

    zero(buff,256);
    y=0;

    while(fgets((char*)buff,255,fd))
    {
        x=(int32)strlen((char*)buff);
        *(buff+x-1)=0;
        path=example_path(*buff);
        n=find_node(path);
        
        if(!n)
        {
            zero(buff,256);
            continue;
        }

        val=example_duplicate(buff);

        //int8 key_copy[256];
    //strncpy((char*)key_copy, (char*)buff, 255);
   // char *copy_buff = strdup((char*)buff); // Make a temp copy just for printing
      /*  printf("\n");
        printf("node='%s'\n",n->path);
        //printf("buff='%s'\n",buff);
        printf("buff='%s' (%p)\n",buff,buff);

       //printf("buff='%s'\n", key_copy);
        printf("val='%s'\n",val);
        printf("len='%d'\n",(int16)strlen((char*)val));
        printf("\n");
        */
        
       // create_leaf(n,buff,val,(int16)strlen((char*)val));
      // create_leaf(n, key_copy, val, (int16)strlen((char*)val));
     // create_leaf(n, strdup((char*)buff), strdup((char*)val), strlen((char*)val));
     create_leaf(n, buff, val, (int16)strlen((char*)val));


        y++;
        zero(buff,256);
    }
    fclose(fd);
    return y;
}

int main()
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
    return 0;
}