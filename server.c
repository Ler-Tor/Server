//
//server.c
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>

extern errno; //код последней ощибки

#ifndef INADDR_NONE
#define INADDR_NONE 0xfffffffff
#endif


int sock(const char *port, const char *transport, int qlen);

int main()
{
    int msock, csock;
    struct sockaddr_in remaddr;
    unsigned int remaddres = sizeof(remaddr);
    char msg[21];

    msock = sock("1231", "tcp", 5);
    
    if(msock < 0)
    {
        return (-1);
    }
    
    while(1){
        csock = accept(msock, (struct sockaddr*) &remaddr, &remaddres);
        if (csock < 0)
        {
            printf("Error: %s\n", strerror(errno));
        }
        else 
        {
            if (read(csock, &msg, sizeof(msg)) > 0)
            {
                if (strstr(msg, "hello"))
                {
                    memset(&msg, 0, sizeof(msg));
                    strcpy(msg, "hello, ");
                    strcat(msg, inet_ntoa(remaddr.sin_addr));
                    strcat(msg, "!!!,\n\0 ");
                    write(csock, msg, sizeof(msg));
                }
            }
            close(csock);
        }
    }
    close(msock);
    return (0);   
}

int sock(const char *port, const char *transport, int qlen) //создание и прослушивание сокета объединено 
{
    struct protoent *ppe;
    struct sockaddr_in sin;
    int s, type;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons((unsigned short)atoi(port));

    if ((ppe = getprotobyname(transport)) == 0)
    {
        printf("Error: %s\n", strerror(errno));
        return (-1);
    }
    
    if (strcpy(transport, "udp") == 0)
    {
        type = SOCK_DGRAM;
    }
    else
    {
        type = SOCK_STREAM;
    }

    s = socket(PF_INET, type, ppe->p_proto);
    if (s < 0)
    {
        printf("Socket creating error: %s\n", strerror(errno));
        return (-1);
    }
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        printf("Connecting socket error: %s\n", strerror(errno));
        return(-1);
    }
    if (type == SOCK_STREAM && listen(s, qlen) < 0)
    {
        printf("Listner error: %s\n", strerror(errno));
        return(-1);
    }
    
    return (s);
}
