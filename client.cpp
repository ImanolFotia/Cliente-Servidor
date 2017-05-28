#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef unsigned short U16;

struct OPCODE
{
    U16 opcode;
    U16 A;
    U16 B;
};

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];

    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("192.168.0.13");
    server.sin_family = AF_INET;
    server.sin_port = htons( 27015 );

    //Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");

    ifstream inFile("program.csc", ios::binary);

    std::vector<OPCODE> vector_opcodes;


    U16* buffer = new U16[3];

    do
    {
        OPCODE tmpOP;
        inFile.read((char*)&buffer[0], sizeof(U16) * 3);

        tmpOP.opcode = buffer[0];
        tmpOP.A = buffer[1];
        tmpOP.B = buffer[2];

        vector_opcodes.push_back(tmpOP);
        cout << "vuelta" << endl;
    } while(!inFile.eof());

    int *cant = new int((vector_opcodes.size()-1) * 3);
    send(sock, cant, sizeof(int), 0);

    U16 *currOpcode = new U16[3];


    for(int i = 0; i < vector_opcodes.size()-1; i++){
        send(sock, &vector_opcodes[i].opcode, sizeof(U16), 0);
        send(sock, &vector_opcodes[i].A, sizeof(U16), 0);
        send(sock, &vector_opcodes[i].B, sizeof(U16), 0);
    }


    delete[] currOpcode;

    shutdown(sock, 1);

    return 0;
}
