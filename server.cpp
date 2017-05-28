#include <iostream>
#include <memory>
#include <cstdlib>
#include <exception>
#include <cstring>
#include <ctime>
#ifdef __linux__
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#error This program must be compiled using Linux
#endif

typedef unsigned short U16;
const U16 NOP = 0x00;
const U16 ADD = 0x01;
const U16 SUB = 0x02;
const U16 AND = 0x03;
const U16 OR  = 0x04;
const U16 XOR  = 0x05;
const U16 TIME = 0x06;

using namespace std;

int m_Socket;

int ADD_FUNC(int a, int b)
{
    return a+b;
}

int SUB_FUNC(int a, int b)
{
    return a-b;
}

int OR_FUNC(int a, int b)
{
    return a || b;
}

int AND_FUNC(int a, int b)
{
    return a && b;
}

int XOR_FUNC(int a, int b)
{
    return a ^ b;
}

void TIME_FUNC()
{
time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
}

int main()
{
    struct sockaddr_in server, client;
    int socket_desc, client_sock, c, read_size;
    m_Socket = socket(PF_INET, SOCK_STREAM, 0);

    if( m_Socket == -1)
    {
        std::cerr << "Socket creation failed." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    else
    {
        std::cout << "Raw Socket created." << std::endl;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.13");
    server.sin_port = htons( 27015 );

    bind(m_Socket,(struct sockaddr *)&server, sizeof(server));
while(1){
    listen(m_Socket, 3);

    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(m_Socket, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        std::cout << "accept failed" << std::endl;
        return 1;
    }
    std::cout << ("Connection accepted") << std::endl;

    int cantDatos = 0;
    read_size = recv(client_sock, &cantDatos, sizeof(int), 0);

    std::cout << cantDatos << std::endl;

    U16 * datos = new U16[(int)cantDatos];


    for(int i = 0; i < cantDatos; i++){
        recv(client_sock, &datos[i], sizeof(U16), 0);
    }



    for(int i = 0; i < cantDatos; i+=3)
    {
        switch((U16)datos[i])
        {
        case ADD:
            std::cout << "ADD: " << ADD_FUNC((U16)datos[i+1], (U16)datos[i+2]) << std::endl;
            break;
        case SUB:
            std::cout << "SUB: " << SUB_FUNC((U16)datos[i+1], (U16)datos[i+2]) << std::endl;
            break;
        case AND:
            std::cout << "AND: " << AND_FUNC((U16)datos[i+1], (U16)datos[i+2]) << std::endl;
            break;
        case OR:
            std::cout << "OR: " << OR_FUNC((U16)datos[i+1], (U16)datos[i+2]) << std::endl;
            break;
        case XOR:
            std::cout << "XOR: " << XOR_FUNC((U16)datos[i+1], (U16)datos[i+2]) << std::endl;
            break;
        case TIME:
            TIME_FUNC();
            break;
        }
    }
}
    return 0;
}
















