/*
 * Name: SocketServer
 * Author: Taylor Jones
 * Date: 10/20/18
 * Description: The SocketServer class is responsible for creating the
 *  initial socket where the server waits for incoming client requests.
 *  Once received, the SocketServer creates a new instance of ChatRunnable,
 *  which implements the conversation between the client and server.
 */


import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Stack;

public class SocketServer {
    private String SERVER_HANDLE = "Edwin";
    private int port;
    private ServerSocket serverSocket = null;
    private Stack<ChatRunnable> chats = new Stack<>();


    public SocketServer(int port) {
        this.port = port;
    }


    /**
     * Helper function to clear the current console line.
     * https://stackoverflow.com/questions/7522022/how-to-delete-stuff-printed-to-console-by-system-out-println
     */
    private void clearConsoleLine() {
        System.out.print("\033[1000D"); // Beginning of line
        System.out.print("\033[K"); // Erase line content
    }

    /**
     * Creates the base socket connection, and then listens for client
     * connections and triggers a new chat conversation once a
     * connection request is received from a client.
     */
    public void run() {
        // Set up a shutdown hook to handle gracefully ending the program on SIGINT
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            clearConsoleLine();
            System.out.println("Chat server shutting down...");
            for (ChatRunnable chat : chats) {
                chat.stop(true);
            }

            System.out.println("All sockets have been closed. Goodbye.");
        }));


        try {
            serverSocket = new ServerSocket(port);
            System.out.println("Listening on port " + port);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        while(true) {
            try {
                // Accept any new client connection request.
                Socket clientSocket = serverSocket.accept();

                // Create a new chat conversation for each client.
                ChatRunnable chatRun = new ChatRunnable(clientSocket, SERVER_HANDLE);

                // Add each client to the chat stack, so we can keep track
                // of all clients and make sure they're all closed in the
                // event of a SIGINT.
                chats.push(chatRun);

                // Start the conversation with the new client.
                new Thread(chatRun).start();

            } catch (IOException e) {
                System.out.println(e.getMessage());
            }
        }
    }
}
