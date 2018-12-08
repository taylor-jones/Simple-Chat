This is a simple client-server chat program that runs in the console and makes use of the sockets API.

# Compiling
- The chat server is implemented in Java.
- The chat client is implemented in C++.

There are 3 total makefiles in the project files:
- One in the root directory
- One in the Server directory
- One in the Client directory

The one in the root directory is setup so that you only need to run 
```
make
```
 to compile both the Server & Client or

```
make clean
``` 
to delete the *.o files from Client and *.class files from Server.



<br>

# Running
## Chat Server
Once compiled, you can run the pre-made "chatserve" file in the root directory, using the following command:
```
./chatserve <port#>
```

If the script above gives you any trouble, then executing the following commands from the project's root directory will begin running the Chat Server:
```
cd Server
java ChatServer <port#>
```

## Chat Client
Likewise, there's a pre-made "chatclient" file in the root directory, which can be run using the following command:
```
./chatclient <server-hostname> <port#>
```

Again, if this script gives you trouble, executing the following commands from the project's root directory will begin running the Chat Client:
```
cd Client
./ChatClient <server-hostname> <port#>
```



<br>

# Program Flow
The Chat Server starts and waits on the specified port. Once a Chat Client connects on that port, Chat Server accepts the connection and creates a new thread for the conversation with this Client. The Chat Client is prompted to specify a handle (Note: the Chat Server's handle is hard-coded). 

Then, the Chat Server & Chat Client quietly exchange handles. This is for the purposes of showing connect/disconnect messages that reference each other's names. Both will still send their own handle prefix whenever messages are sent.

The conversation continues on for as long as desired. 

If, at any point, either the Client or Server quits, both the Server and Client acknowledge the end of the conversation, and the Chat Server closes the thread that was created for that Client, and just continues listening on the port. The Chat Client's program ends.

If, at any point, the Chat Server receives a SIGINT, it loops through all Client connections, makes sure each of them is closed, and then gracefully quits after printing a closing message. In this event, the \quit message is automatically sent to the Chat Client to provoke the end-of-chat.

If, at any point, the Chat Client receives a SIGINT, it closes the connection with the Server and the \quit message is automatically sent to the Chat Server to provoke the end-of-chat. The Chat Server continues listening on the port.




<br>

# Additional Notes
* The Chat Server is multi-threaded, and can accept any number of connections, since it always opens a new thread for any new Client. However, if multiple conversations are going on at once, there's no real indication of who the Server is sending to, but each Client can send and receive messages with the Chat Server at the same time.
