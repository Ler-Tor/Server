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
    
    if (msock < 0)
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

int sock(const char *port, const char *transport, int qlen)
{

}
