//Server.cpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

int main() 
{
    int serverSocket, clientSocket;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    addr_size = sizeof(serverAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *) &serverAddr, &addr_size);

    recv(clientSocket, buffer, 1024, 0);
    string filename(buffer);
    std::ofstream outputFile(filename, std::ios::out | std::ios::binary);

    int bytesReceived;
    while ((bytesReceived = recv(clientSocket, buffer, 1024, 0)) > 0) {
        outputFile.write(buffer, bytesReceived);
    }

    outputFile.close();
    std::cout << "File received and saved as " << filename << std::endl;
    return 0;
}

//	Client.cpp

#include <iostream>
#include <fstream>
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

    const char* filename = "example.txt";
    send(clientSocket, filename, strlen(filename), 0);

    std::ifstream inputFile(filename, std::ios::in | std::ios::binary);
    if (!inputFile) {
        std::cerr << "File not found." << std::endl;
        return 1;
    }

    while (inputFile.read(buffer, sizeof(buffer))) {
        send(clientSocket, buffer, sizeof(buffer), 0);
    }

    inputFile.close();
    std::cout << "File sent to the server." << std::endl;

    return 0;
}

