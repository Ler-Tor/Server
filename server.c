//Server.c
//Ver 1.0


#include <sys/types.h>
#include <sys/socket.h> //Базовые функции сокетов, стркутуры данных
#include <netdb.h> //Функции для преобразования протокольных имен и имен хостов в числовые адреса
#include <arpa/inet.h> //Функции для работы с числовыми IP-адресами
#include <netinet/in.h> //Семейства адресов/протоколов PF_INET (для IPv4) и (PF_INET6 для IPv6). Включают в себя IP-адреса, а также номера портов TCP и UDP

int sock(const char *transport)
{
    
    struct protoent *ppe; // eуказатель на запись с информацией о протоколе
    int s, type; //дескриптор и тип сокета
    
    ppe = getprotobyname(transport); //определение типа сокета
    
    if(strcmp(transport, "udp") == 0) //определение типа сокета
    {
        type = SOCK_DGRAM; //если udp то SOCK_DGRAM
    }
    else
    {
        type = SOCK_STREAM; //если tcp то SOCK_STREAM
    }
    
    s = socket(PF_INET, type, ppe->p_proto);
    
    return (s); // возвращаем дескриптор сокета
}

int listner(int sock, const char *host, const char *port) 
{
    struct hostent *phe;
    struct sock_addr_in *sin;

    memset(&sin, 0, sizeof(sin));

     

}

