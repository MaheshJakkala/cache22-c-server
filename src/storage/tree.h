
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

#define find_last(x)     find_last_linear(x)
#define returr(x) \
    errno=(x); \
    return nullptr
typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef unsigned char Tag;


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

void zero(int8*,int16);
Leaf*find_last_linear(Node*);
Leaf*create_leaf(Node*,int8*,int8*,int16);
Node*create_node(Node*,int8*);