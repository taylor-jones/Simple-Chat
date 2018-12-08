/**
 * Name: Util.cpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: Util.cpp contains utility function
 *  implementations for use with the chatClient program.
 */


#include "Util.hpp"

    /**
     * Clears the current line in the terminal.
     * @return void
     */
    void clearConsoleLine() {
        cout << "\33[2K\r";
    }


    /**
     * Continuously prompts the user for input using a required length range
     *  and a provided prompt until a valid input has been received.
     * @param minLength - the shortest allowed input length
     * @param maxLength - the longest allowed input length
     * @param prompt - the prompt to display
     * @return
     */
    string getInput(size_t minLength, size_t maxLength, string const &prompt) {
        string input;

        while (input.empty() || input.length() < minLength || input.length() > maxLength) {
            cout << prompt;
            getline(cin, input);
        }

        return input;
    }


    /**
     * Removes (in-place) any trailing carriage returns or newlines from a string
     * @param input - the string to removes endings from.
     * @return
     */
    string removeLineEnding(string input) {
        while (!input.empty() &&
        (input[input.size() - 1] == '\r' || input[input.size() - 1] == '\n')) {
            input.erase(input.size() - 1);
        }

        return input;
    }


    /**
    * Replaces (in-place) all instances of a substring from within another string
    * @param input - the original string
    * @param target - the substring to replace
    * @param replacement - what will be put in place of the target string
    * @return the string after the replacement(s).
    */
    string replaceAll(string &input, string const &target, string const &replacement) {
        size_t index;
        while (!input.empty() && (index = input.find(target)) != string::npos) {
            input = input.replace(index, target.length(), replacement);
        }

        return input;
    }