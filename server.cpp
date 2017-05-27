#include <iostream>
#include <memory>
#include <cstdlib>
#include <exception>
#include <cstring>

#ifdef __linux__
	#include <sys/socket.h> 
	#include <netinet/tcp.h>   
	#include <netinet/ip.h> 
	#include <netinet/in.h>
	#include <arpa/inet.h>
#else
	#error This program must be compiled using Linux
#endif

using namespace std;

int m_Socket;

int main()
{
	struct sockaddr_in server , client;
	int socket_desc , client_sock , c , read_size;
    	char client_message[2000];
	m_Socket = socket(PF_INET, SOCK_STREAM, 0);
			
	if( m_Socket == -1){
		std::cerr << "Socket creation failed." << std::endl;
		std::exit(EXIT_FAILURE);
	}
			
	else{
		std::cout << "Raw Socket created." << std::endl;
	}
	
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = inet_addr("192.168.0.13");
    	server.sin_port = htons( 27015 );
    	
	bind(m_Socket,(struct sockaddr *)&server , sizeof(server));
			
	listen(m_Socket , 3);
	
	c = sizeof(struct sockaddr_in);
     
    	//accept connection from an incoming client
    	client_sock = accept(m_Socket, (struct sockaddr *)&client, (socklen_t*)&c);
    	if (client_sock < 0)
    	{
        	perror("accept failed");
        	return 1;
    	}
    	puts("Connection accepted");
    	
    	read_size = recv(client_sock , client_message , 2000 , 0);
    	
    	std::cout << client_message << std::endl;
	
	return 0;
}
















