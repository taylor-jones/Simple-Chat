/**
 * Name: SocketClient.cpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: SocketClient.cpp is the class specification
 *  file for the SocketClient class. This file contains declarations
 *  for the member functions of the SocketClient class.
 */

#ifndef SOCKETCLIENT_HPP
#define SOCKETCLIENT_HPP

#include "ChatClient.hpp"

class SocketClient {
 private:
  char* host;
  int port;
  int sock;
  ChatClient client;

  int getConnection();

 public:
  explicit SocketClient(char* host, int port);
  void start();
  void disconnect();
};


#endif //SOCKETCLIENT_HPP
