/**
 * Name: SocketClient.cpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: SocketClient.cpp is the class implementation
 *  file for the SocketClient class. This file contains definitions
 *  for the member functions of the SocketClient class.
 */


#include <arpa/inet.h>
#include <cstring>
#include "SocketClient.hpp"



/**
 * Initializes the socket client's host & port, triggers getting a socket
 *  connection, and sets the chat client's socket.
 * @param host - the server's hostname
 * @param port - the server's port
 */
SocketClient::SocketClient(char *host, int port) {
    this->host = host;
    this->port = port;
    this->sock = getConnection();
    this->client.setSocket(sock);
}


/**
 * Starts the chat client.
 */
void SocketClient::start() {
    this->client.start();
}


/**
 * Stops the chat client, passing through the SIGINT flag,
 * which alerts the chat client that it needs to send a quit
 * message to the server.
 */
void SocketClient::disconnect() {
    this->client.stop(true);
}


/**
 * Builds and returns the socket connection to the server.
 * @return int - the socket connection.
 */
int SocketClient::getConnection() {
    // Specify the server connection.
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->port);
    serverAddress.sin_addr.s_addr = inet_addr(this->host);

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed: socket()");
        exit(1);
    }

    // Test the validity of the host
    if (inet_pton(AF_INET, this->host, &serverAddress.sin_addr) <= 0) {
        perror("Invalid host address: inet_pton()");
        exit(1);
    }

    // Connect to the server.
    if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Socket connection failed: connect()");
        exit(1);
    }

    return sock;
}

