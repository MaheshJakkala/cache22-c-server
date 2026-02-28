

//cache22.c
#include "cache22.h"

int32 handle_hello(Client*,int8*,int8*);
bool scontinuation;
bool ccontinuation;

Cmdhandler handlers[]={
    {(int8*)"hello",handle_hello},
    //{(int8*)"hello",handle_hello}
};

Callback getcmd(int8* cmd)
{
    Callback cb;
    int16 n,arrlen;


    if(sizeof(handlers)<16) return 0;
    arrlen=(sizeof(handlers)/16);
    cb=0;
    for(n=0;n<arrlen;n++)
    {
        if(!strcmp((char*)cmd,(char*)handlers[n].cmd))
        {
            cb=handlers[n].handler;
            break;
        }
    }
    return cb;
}

int32 handle_hello(Client*cli,int8*folder,int8*args)
{
    dprintf(cli->s,"hello%s\n");
    return 0;
}
void zero(int8* buf,int16 size)
{
    int8*p;
    int16 n=0;
    for(n=0,p=buf;n<size;n++,p++)
    {
        *p=0;
    }
    return;
}
void childloop(Client* cli)
{
    int8 buff[256];
    int16 n;
    int8* p,*f;
    int8 cmd[256],folder[256],args[256];

    //

//select /Users/jonas
//create /Users/logins
//insert /Users/hello \n sieierjfhfirkir
    zero(buff,256);
   // read(cli->s,(char*)buff,255);
  read(cli->s, (char*)buff, 255);
    /*if (bytes_read <= 0) {
        printf("Client disconnected.\n");
        return;
    }
    dprintf(cli->s, "✅ Command received: %s\n", buff);

    buff[bytes_read] = '\0'; // Null-terminate the received data
    printf("📥 Received command: %s\n", buff); 
*/
    n=(int16)strlen((char*)buff);

    if(n>256) n=256;

    for(p=buff;
        (*p) && (n--)
            && (*p!=' ')
            && (*p!='\n')
            && (*p!='\r');
            p++
        );
    
    

    zero(cmd,255);
    zero(folder,255);
    zero(args,256);

    if(!(*p) || (!n))
    {
        strncpy((char*)cmd,(char*)buff,255);
        goto done;
    }
    else if((*p=='\n') || (*p=='\r'))
    {
        *p=0;
        strncpy((char*)cmd,(char*)buff,255);
        goto done;
        

    }
    else if(*p==' ')
    {
        *p=0;
        strncpy((char*)cmd,(char*)buff,255);
    }
    for(p++,f=p;
        (*p) && (n--)
            && (*p!=' ')
            && (*p!='\n')
            && (*p!='\r');
            p++
        );//for getting folder
    
       // dprintf(" *p value: %s\n", (char*)*p); 
    if(!(*p) && !(n))
    {
        strncpy((char*)folder,(char*)f,255);
        goto done;
    }
    else if((*p)==' ' || *p=='\n' || *p=='\r')
    {
        *p=0;
        strncpy((char*)folder,(char*)f,255);
        

    }

    p++;
    
    if(*p)
    {
        strncpy((char*)args,(char*)p,255);
        dprintf("args:  %s\n", args); 
        for(p=args;
            (*p)&& (*p!='\n')
                &&(*p!='\r');
                p++);
        *p=0;
    }
    done:
        dprintf(cli->s,"cmd:\t%s\n",cmd);
        dprintf(cli->s,"folder:\t%s\n",folder);
        dprintf(cli->s,"args:\t%s\n",args);
    return;
}

void mainloop(int s)
{
    struct sockaddr_in cli;
    int s2;
    char*ip;
    int16 port;
  // int32 len;p
   pid_t pid;
   Client*client;  
   socklen_t len = sizeof(struct s_client);

    s2=accept(s,(struct sockaddr*)&cli,
         (unsigned int*)&len);
    if(s2 < 0)
 {       perror("Accept failed");
        return;
}
    
    port=(int16)htons((int)cli.sin_port);
    ip= inet_ntoa(cli.sin_addr);

    printf("Connection from %s : %d\n",ip,port);

    client=(Client*)malloc(sizeof(struct s_client));
    assert(client);

    zero((int8*)client,sizeof(struct s_client));
    client->s=s2;
    client->port=port;
    strncpy(client->ip,ip,15);

    
    pid=fork();
    if(pid)
    {
        free(client);
        return;
    }
    else
    {
        dprintf(s2,"100 Connected to Cache22 server\n");

        ccontinuation=true;
        while(ccontinuation) 
            childloop(client);

        close(s2);
        free(client);

        return;

    }
   
   // close(s2);
    return;
}
/*int initserver(int16 port){
    struct sockaddr_in sock;
    int s;

    sock.sin_family= AF_INET;
    sock.sin_port=htons((int)port);
    sock.sin_addr.s_addr=inet_addr(HOST);

    s=socket(AF_INET,SOCK_STREAM,0);
    assert(s>0);

 int opt = 1;
 setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    

    errno=0;
    if(bind(s,(struct sockaddr*)&sock,sizeof(sock)))
       { //assert_perror(errno);
        assert(errno == 0);
       }

    errno=0;
    if(!listen(s,20)){ assert(errno == 0);
    //assert_perror(errno);
    }
    printf("Server is listening on %s : %d \n",HOST,port);
    fflush(stdout);
    return s;
}*/
int initserver(int16 port) {
    struct sockaddr_in sock;
    int s, opt = 1;

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);  // Stop if socket creation fails
    }

    // Allow reuse of the address
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Set address and port
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(HOST); 

    // Binding the socket
    if (bind(s, (struct sockaddr*)&sock, sizeof(sock)) < 0) {
        perror("Bind failed");  // This will print the reason if bind fails
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(s, 20) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("✅ Server is listening on %s : %d\n", HOST, port);
    return s;
}


int main(int argc,char* argv[])
{
    char* sport;
    int s;
    int16 port;

    Callback x;

   x= getcmd((int8*)"hello");
    printf("%s\n",(char*)x);
    x=getcmd((int8*)"dkdkdkd");
    printf("%p\n",x);
    return 0;

    if(argc < 2)
    {
        sport=PORT;
    }
    else sport = argv[1];

    port=(int16)atoi(sport);
    s=initserver(port);

    scontinuation=true;
    while(scontinuation)
    {
        mainloop(s);
    }
    printf("Shutting down..");
    close(s);
    return 0;
}