#include <stdio.h>
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

    int sockfd, new_socket;
    struct sockaddr_in serverAddr;
    int serverlen = sizeof(serverAddr);
    unsigned long num;
    // string send_name;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        std::cout << "Couldn't create socket.\n";
        exit(1);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("10.3.61.15");

    if (bind(sockfd, (struct sockaddr*)&serverAddr, serverlen)<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(sockfd, (struct sockaddr*)&serverAddr, (socklen_t*)&serverlen))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    while(1){
        read(new_socket , (void*)&num, sizeof(num));
        num = ntohl(num);
        num += 5;
        std::cout << "num returned = " << num << endl;
        num = htonl(num);
        send(new_socket , (void*)&num, sizeof(num) , 0 );
    }
    return 0;
}
