/*
 * Name: ChatRunnable
 * Author: Taylor Jones
 * Date: 10/20/18
 * Description: The ChatRunnable class is responsible for implementing a chat
 *  conversation medium for a client that has initiated contact with the server.
 *  This class will handle receiving and sending messages until either the
 *  client or server quits the conversation.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;


public class ChatRunnable implements Runnable {
    private String QUIT_MESSAGE = "\\quit";
    private Socket clientSocket;
    private String clientHandle;
    private String serverHandle;
    private String serverPrefix;
    private boolean isChatting;

    private PrintWriter out;
    private BufferedReader in;
    private BufferedReader stdIn; 


    /**
     * Class constructor
     * @param clientSocket
     * @param serverHandle
     */
    public ChatRunnable(Socket clientSocket, String serverHandle) {
        this.clientSocket = clientSocket;
        this.serverHandle = serverHandle;
        this.serverPrefix = serverHandle + "> ";
    }


    /**
     * Sets up the input/output buffers and begins the conversation
     * between the server and client, which continues until one of
     * the peers quits.
     */
    public void run() {
        try {
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            stdIn = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(clientSocket.getOutputStream(), true);

            // Exchange handles between the client & server
            exchangeHandles();

            // Begin the dialogue.
            while (isChatting) {
                receiveMessage();

                if (isChatting) {
                    sendMessage();
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            stop(false);
        }
    }


    /**
     * Displays the server's handle as a prefix in the console,
     * and processes/sends the message provided by the server.
     * If the server quit, it displays a message indicating the quit,
     * and then stops the conversation.
     */
    private void sendMessage() {
        String output;
        System.out.print(serverPrefix);

        try {
            output = stdIn.readLine();
            out.println(serverPrefix + output);

            if (senderDidQuit(output)) {
                stop(false);
            }

        } catch (IOException e) {
            e.getMessage();
            isChatting = false;
        }
    }


    /**
     * Receives the message sent from the client. If the client quit,
     *  it displays a message indicating the quit and then stops the conversation.
     */
    private void receiveMessage() {
        String input;

        try {
            if ((input = in.readLine()) != null) {
                System.out.print("\033[1000D"); // Beginning of line
                System.out.print("\033[K"); // Erase line content

                if (!senderDidQuit(input)) {
                    System.out.println(input);
                } else {
                    System.out.println(clientHandle + " quit the chat.");
                    stop(false);
                }
            }
        } catch (IOException e) {
            e.getMessage();
            isChatting = false;
        }
    }


    /**
     * Stops the conversation and closes the socket. If the stop
     *  was caused by a SIGINT, then the \quit message is relayed
     *  to the client, so that the client knows the server is no
     *  longer part of the conversation.
     * @param isSigInt - true if stop called because of a SIGINT, false if not.
     */
    public void stop(boolean isSigInt) {
        try {
            if (isChatting) {
                if (isSigInt) {
                    out.println("\\quit");
                } else {
                    System.out.println("Conversation with " + clientHandle
                    + " ended. Waiting on port " + clientSocket.getLocalPort() + "...");
                }

                this.isChatting = false;
                clientSocket.close();
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }


    /**
     * Accepts the client's handle and sends back the server's handle.
     * Then, prints a message indicating that the client is now chatting,
     * and sets isChatting to true, while enables the back-and-forth conversation.
     */
    private void exchangeHandles() {
        try {
            clientHandle = in.readLine();
            System.out.println(clientHandle + " has joined the chat.");
            out.println(serverHandle);
            isChatting = true;
        } catch (IOException e) {
            e.getMessage();
        }
    }


    /**
     * Helper function to check if a message sender sent the quit message.
     * @param message - the message that was sent.
     * @return boolean - true if the sender quit. false if not.
     */
    private boolean senderDidQuit(String message) {
        return message.contains(QUIT_MESSAGE);
    }

}
