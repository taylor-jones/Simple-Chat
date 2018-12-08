/**
 * Name: main.cpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: This program implements a client program
 *  for a simple client-server chat application.
 *
 * Sources: The following sources were especially helpful in my implementation of the chat client:
 *  CS344 Operating Systems - Block 4 - Network Clients
 *  https://www.youtube.com/watch?v=1EUJboWF-tc&t=0s&index=3&list=PL-N9CTl1CH83XHo09FC6pRaZEjaQHkSQh
 *
 *  Edonix Learning Solutions - Socket Programming Tutorial
 *  https://www.youtube.com/watch?v=LtXEMwSG5-8
 *
 *  Beej's Guide to Netowrk Programming
 *  https://beej.us/guide/bgnet/html/multi/index.html
 *
 *  GeeksForGeeks - Socket Programming in C/C++
 *  https://www.geeksforgeeks.org/socket-programming-cc/
 */

#include <iostream>
#include <functional>
#include <signal.h>

#include "SocketClient.hpp"


/**
 * This function allows for binding c++ class members as
 * c signal handlers. This means we can pass a SIGINT into
 * a SocketClient member function, which will then trigger
 * a disconnect on the Chat Client.
 *
 * @note The idea for this concept was found here:
 * http://matetelki.com/blog/?p=636
 */
std::function<void(int)> disconnectWrapper;
void disconnectHandler(int sig) {
    disconnectWrapper(sig);
}


/**
 * Program entry. Accepts the two arguments and assigns them to
 *  the host and port values, then creates and initializes the Socket Client.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments.\nPlease use the format: ./chatClient [hostname] [port]" << std::endl;
        exit(1);
    }

    // Grab the host & port from the command arguments
    char* host = argv[1];
    int port = atoi(argv[2]);

    // Initialize the socket client.
    SocketClient socketClient(host, port);

    // watch for SIGINT. If one occurs, call the disconnectWrapper
    // to pass the signal into the socket client, which will trigger
    // a disconnect from the chat client.
    disconnectWrapper = std::bind(&SocketClient::disconnect, &socketClient);
    struct sigaction signalHandler;
    signalHandler.sa_handler = disconnectHandler;
    sigemptyset(&signalHandler.sa_mask);
    signalHandler.sa_flags = 0;
    sigaction(SIGINT, &signalHandler, NULL);

    // Start the socket client.
    socketClient.start();

    return 0;
}