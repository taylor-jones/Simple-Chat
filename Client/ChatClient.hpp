/**
 * Name: ChatClient.cpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: ChatClient.cpp is the class specification
 *  file for the ChatClient class. This file contains declarations
 *  for the member functions of the ChatClient class.
 */

#ifndef CHATCLIENT_HPP
#define CHATCLIENT_HPP

#include <string>

using std::string;


class ChatClient {
 private:
  const string QUIT_MESSAGE = "\\quit\n";
  int socket;
  bool isChatting;
  string serverHandle;
  string clientHandle;
  string clientPrefix;

  string fetchClientHandle();
  void chat();
  string getClientMessage();
  string getServerMessage();
  bool senderDidQuit(string const &input);
  void sendMessage(string const &message);
  void printMessage(string &message);

 public:
  ChatClient();
  explicit ChatClient(int socket);
  void start();
  void stop(bool isSigInt);
  void setSocket(int socket);
};


#endif //CHATCLIENT_HPP
