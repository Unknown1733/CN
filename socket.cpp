//Code A : TCP

//Server.cpp

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>


int main() 
{
    int serverSocket, clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    addr_size = sizeof(serverStorage);
    clientSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

    strcpy(buffer, "Hello from server!");
    send(clientSocket, buffer, 1024, 0);

    return 0;
}	


//Client.cpp

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>


int main() 
{
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    recv(clientSocket, buffer, 1024, 0);
    std::cout << "Data received: " << buffer << std::endl;+

    return 0;
}





//Code B: UDP

//Server.cpp

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>


int main() 
{
    int udpSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr);

    recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *) &clientAddr, &addr_len);
    std::cout << "Received data: " << buffer << std::endl;

    const char* response = "Hello from UDP server!";
    sendto(udpSocket, response, strlen(response), 0, (struct sockaddr*) &clientAddr, addr_len);

    return 0;
}	


//Client.cpp

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>


int main() 
{
    int udpSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_len = sizeof(serverAddr);

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    const char* message = "Hello from UDP client!";
    sendto(udpSocket, message, strlen(message), 0, (struct sockaddr*) &serverAddr, addr_len);

    recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *) &serverAddr, &addr_len);
    std::cout << "Received data: " << buffer << std::endl;

    return 0;
}
