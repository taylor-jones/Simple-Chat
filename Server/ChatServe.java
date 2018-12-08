/*
 * Name: ChatServe
 * Author: Taylor Jones
 * Date: 10/20/18
 * Description: This program acts as the server in a simple
 *  multi-threaded client-server chat application.
 * Sources: The following sources were used in conjunction to learn
 *  how to implement this chat server:
 *
 * Java Multithreaded Socket Server Example
 * https://www.youtube.com/watch?v=k5EATy-wmU4
 *
 * "The Complete Java Master Class" on Udemy.
 *  https://www.udemy.com/java-the-complete-java-developer-course/
 *  The ideas are specifically from the "Java Networking Programming" section.
 */

import java.util.Scanner;


public class ChatServe {
    /**
     * Checks whether the caller provided a valid port number. If so,
     * that port number is used. Otherwise, the user is continuously prompted
     * for a valid port number until the user provides a valid port number.
     *
     * @param input    The original command line argument
     * @param keyboard Scanner to read user input
     * @return int      A valid port number
     */
    private static int validPort(String input, Scanner keyboard) {
        int port = -1;

        // try to use the original input argument as the port, if possible.
        try {
            port = Integer.parseInt(input.trim());

            // otherwise, keep asking until you get a valid port.
        } catch (NumberFormatException e) {
            while (port < 0 || port > 65535) {
                System.out.print("Enter a valid port number (0 - 65535): ");
                input = keyboard.nextLine();

                try {
                    port = Integer.parseInt(input.trim());
                } catch (NumberFormatException f) {
                    port = -1;
                }
            }
        }

        return port;
    }


    /**
     * Determines the argued port number and initializes and runs the SocketServer.
     * @param args The port number to connect to.
     */
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        int port = validPort(args[0], keyboard);
        SocketServer server = new SocketServer(port);
        server.run();
    }
}