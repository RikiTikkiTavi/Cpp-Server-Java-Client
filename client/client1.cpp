//
// Created by root on 29/07/18.
//

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <thread>
#include <iostream>

using namespace std;

void error(const char *msg) {
    perror(msg);
    exit(0);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
// argc -> Argument count = the number of strings pointed to by argv
// argv -> Argument vector

int connect(int argc, char *argv[]) {
    int sockfd, portno;
    // sockaddr_in -> Structure describing a generic socket address.
    struct sockaddr_in serv_addr{};
    /*
      The hostent structure is used by functions to store information about a given host, such as host name,
      IPv4 address, and so forth
     */
    struct hostent *server;

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port name\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == nullptr) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
          (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    return sockfd;
}

void sendWork(int sockfd) {
    char buffer[256];
    int n;
    bzero(buffer, 256);
    cout << "Enter name: ";
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    cout << "Enter sendTo: ";
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error("ERROR writing to socket");
    while (true) {
        bzero(buffer, 256);
        cout << "> ";
        fgets(buffer, 255, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("ERROR writing to socket");
    }
}


void receiveWork(int sockfd) {
    char buffer[256];
    int n;

    while (true) {
        bzero(buffer, 256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        cout << "< " << buffer << std::endl;
    }
}

int main(int argc, char *argv[]) {
    int sockfd = connect(argc, argv);

    thread send_thread(sendWork, sockfd);
    thread receive_thread(receiveWork, sockfd);

    send_thread.join();
    receive_thread.join();

    close(sockfd);
    return 0;
}

#pragma clang diagnostic pop