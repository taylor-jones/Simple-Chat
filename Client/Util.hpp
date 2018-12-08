/**
 * Name: Util.hpp
 * Author: Taylor Jones
 * Date: 10/27/18
 * Description: Util.hpp contains utility function
 *  declarations for use with the chatClient program.
 */

#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;


void clearConsoleLine();

string getInput(size_t minLength, size_t maxLength, string const &prompt);

string removeLineEnding(string input);

string replaceAll(string &input, string const &target, string const &replacement);


#endif //UTIL_HPP
