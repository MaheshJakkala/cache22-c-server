//cache22.h
#ifndef CACHE22
#define CACHE22

#define _GNU_SCORE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>
#include<errno.h>

#include<stddef.h>
#include<stdarg.h>
//#include<stdout.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//#define HOST "0.0.0.0"

#define HOST "127.0.0.1"
#define PORT "12049"


typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

struct s_client
{
    int s;
    char ip[16];
    int16 port;
};
typedef struct s_client Client;
typedef int32 (*Callback)(Client*,int8*,int8*);

struct s_cmdhandler
{
    int8* cmd;
    Callback handler;
};

typedef struct s_cmdhandler Cmdhandler;



void zero(int8*,int16);
void childloop(Client*);
void mainloop(int);
int initserver(int16);
int main(int,char**);
#endif