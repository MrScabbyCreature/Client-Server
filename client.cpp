#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

using namespace std;

#define PORT 45000

int main(){

    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    unsigned long num;
    // string send_name;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        std::cout << "[-]Error in connection.\n";
        exit(1);
    }
    std::cout << "[+]Client Socket is created.\n";

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("10.3.61.15");

    // cout << htons(PORT) << " " << serverAddr.sin_addr.s_addr << endl;

    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(ret < 0){
        std::cout << "[-]Error in connection.\n";
        exit(1);
    }
    std::cout << "[+]Connected to Server.\n";

    while(1){
        std::cout << "Send: " ;
        std::cin >> num;
        unsigned long network_compatible_number = htonl(num);
        send(clientSocket, (void*)&network_compatible_number, sizeof(network_compatible_number), 0);

        recv(clientSocket, (void*)&network_compatible_number, sizeof(network_compatible_number), 0);
        num = ntohl(network_compatible_number);
        std::cout << "Server: " << num << endl;
    }

    return 0;
}
