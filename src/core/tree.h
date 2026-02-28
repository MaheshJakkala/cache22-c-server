//tree.h
#define _GNU_SCORE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<errno.h>
#define TagRoot 1 /*00 01*/
#define TagLeaf 4 //00 10
#define TagNode 2 //01 00
#define NoError 0

typedef void*Nullptr;
Nullptr nullptr=0;

#define ExampleFile "wl.txt"
#define find_last(x)     find_last_linear(x)
#define find_node(x)     find_node_linear(x)
#define lookup(x,y)      lookup_linear(x,y)
#define find_leaf(x,y)   find_leaf_linear(x,y)
#define returr(x) \
    errno=(x); \
    return nullptr
#define Print(x) \
    zero(buff,256); \
    strncpy((char*)buff,(char*)x,255);\
    size = (int16)strlen((char*)buff); \
    if(size)\
        write(fd,(char*)buff, size); \

   // return x
typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef unsigned char Tag;
//(__builtin_types_compatible_p(__typeof__(x), char*) ? (char*)x : "INVALID")



/*
#define Print(x)\
    zero(buff,256);\
    strncpy((char*)buff,(char*)x,255);\
    size=(int16)strlen((char*)buff);\
    if(size)\
        write(fd,(char*)buff,size)
*/          
struct s_node
{
    struct s_node*north;
    struct s_node*west;
    struct s_leaf*east;
    int8 path[256];
    Tag tag;
};
typedef struct s_node Node;
struct s_leaf
{
    Tag tag;
    union u_tree*west;
    struct s_leaf*east;
    int8 key[128];
    int8 *value;
    int16 size;

};
typedef struct s_leaf Leaf;
union u_tree
{
    Node n;
    Leaf l;
};

typedef union u_tree Tree;

Node*find_node_linear(int8*);
int8*lookup_linear(int8*,int8*);
Leaf*find_leaf_linear(int8*,int8*);
void print_tree(int,Tree*);
int8*indent(int8);
void zero(int8*,int16);
Leaf*find_last_linear(Node*);
Leaf*create_leaf(Node*,int8*,int8*,int16);
Node*create_node(Node*,int8*);
 Tree*example_tree();
 int32* example_leaves();
 int8* example_path(int8);
 int8* example_duplicate(int8*);
int main(void);
