/**
 * Name: ChatClient.cpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: ChatClient.cpp is the class implementation
 *  file for the ChatClient class. This file contains definitions
 *  for the member functions of the ChatClient class.
 */


#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include "ChatClient.hpp"
#include "Util.hpp"


/**
 * Default constructor
 */
ChatClient::ChatClient() {
    this->socket = 0;
    this->isChatting = false;
}


/**
 * Receives the established socket.
 * @param socket - the server socket connection
 */
ChatClient::ChatClient(int socket) {
    this->socket = socket;
    this->isChatting = false;
}


/**
 * Prompts the user for a valid client handle, until one is received.
 * @return string - the client handle name
 */
string ChatClient::fetchClientHandle() {
    return getInput(1, 10, "Please enter a handle (1 word, 1-10 characters): ");
}


/**
 * Fetches the client handle, then initiates contact with the server
 * by exchanging handles and triggering the beginning of the chat conversation.
 * @return void
 */
void ChatClient::start() {
    this->clientHandle = this->fetchClientHandle();
    this->clientPrefix = this->clientHandle + "> ";

    sendMessage(this->clientHandle + '\n');
    this->serverHandle = removeLineEnding(this->getServerMessage());
    cout << "You joined a chat with " << this->serverHandle << endl;
    this->chat();
}


/**
 * Begins the chat dialogue between the client & server,
 * which continues until either the client or server quits.
 * @return void
 */
void ChatClient::chat() {
    string message;
    this->isChatting = true;

    while (this->isChatting) {
        // get & send the client message. if the client quit, stop the chat.
        sendMessage(message = getClientMessage());
        if (senderDidQuit(message)) {
            this->stop(false);
        }

        if (this->isChatting) {
            // get & read the server message. if the server quit, stop the chat.
            message = getServerMessage();
            clearConsoleLine();
            if (senderDidQuit(message)) {
                cout << this->serverHandle << " has quit the chat." << endl;
                this->stop(false);
            } else {
                printMessage(message);
            }
        }
    }

    // Once no longer isChatting, make sure to stop the conversation.
    this->stop(false);
}


/**
 * Displays the client's handle prompt in the console and returns any
 * message that the client provides (with the client handle prefixed).
 * @return string - the keyboard input
 */
string ChatClient::getClientMessage() {
    string message;
    cout << this->clientPrefix;
    getline(cin, message);
    message = this->clientPrefix + message + '\n';
    return message;
}


/**
 * Receives and returns the incoming server message.
 * @return string - the processed server message.
 */
string ChatClient::getServerMessage() {
    const int BUFFER_SIZE = 2048;
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);  // clear the buffer to avoid garbage input.

    if ((recv(this->socket, buffer, sizeof(buffer), 0) < 0) && this->isChatting) {
        perror("Failed to receive server message.\n");
    }

    return buffer;
}


/**
 * Stops the conversation and closes the socket. If the stop
 *  was caused by a SIGINT, then the \quit message is relayed
 *  to the client, so that the client knows the server is no
 *  longer part of the conversation.
 * @param isSigInt - bool - if true, the stop call was the
 *  result of a SIGINT. Otherwise the stop was called because
 *  of a \quit messasge.
 * @return void
 */
void ChatClient::stop(bool isSigInt) {
    if (this->isChatting) {
        // if called due to SIGINT, then send the QUIT message to
        // the server to indicate that the client is not longer present.
        if (isSigInt) sendMessage(this->QUIT_MESSAGE);
        clearConsoleLine();
        cout << "Conversation with " << this->serverHandle << " ended. Goodbye." << endl;
        this->isChatting = false;
        close(socket);
    }
}


/**
 * Checks if the content of a message includes the QUIT_MESSAGE.
 * @param input - the sender's message
 * @return bool - true if the message includes \quit, false if not.
 */
bool ChatClient::senderDidQuit(string const &input) {
    return input.find(this->QUIT_MESSAGE) != string::npos;
}


/**
 * Prints a sanitized version of a message to the console
 * after removing and instances of \quit and normalizing
 * any trailing carriage returns or line feeds.
 * @param message - the message to print
 * @return void
 */
void ChatClient::printMessage(string &message) {
    message = replaceAll(message, QUIT_MESSAGE, "");
    cout << removeLineEnding(message) << endl;
}


/**
 * Converts the string message to a c string and then
 * continuously loops until the entire message has been sent
 * using the socket connection.
 * @param message - the message to send.
 * @return void
 */
void ChatClient::sendMessage(string const &message) {
    char* buffer = (char*)message.c_str();
    const size_t BUFFER_SIZE = strlen(buffer);
    size_t sent = 0;

    while(sent < BUFFER_SIZE) {
        sent += write(this->socket, buffer, BUFFER_SIZE);
    }
}


/**
 * Setter function to set the chat client socket.
 * @param socket
 */
void ChatClient::setSocket(int socket) {
    this->socket = socket;
}


