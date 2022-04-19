// Include Guards
#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using namespace std;

// Print In Color
namespace col
{
    void print(string str, int fore, int back, int option)
    {
        cout << "\033[" << option << ";" << fore << ";" << back << "m" << str << "\033[0m";
    }

    void print(string str, int fore, int option)
    {
        cout << "\033[" << option << ";" << fore << "m" << str << "\033[0m";
    }

    void print(char ch, int fore, int back, int option)
    {
        cout << "\033[" << option << ";" << fore << ";" << back << "m" << ch << "\033[0m";
    }

    void print(char ch, int fore, int option)
    {
        cout << "\033[" << option << ";" << fore << "m" << ch << "\033[0m";
    }
}

#endif