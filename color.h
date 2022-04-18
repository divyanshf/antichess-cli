// Include Guards
#ifndef COLOR_H
#define COLOR_H

#include <iostream>
using namespace std;

// Print In Color
namespace col
{
    void printInColor(string str, int color, int option)
    {
        cout << "\033[" << option << ";" << color << "m" << str << "\033[0m";
    }

    void printInColor(char ch, int color, int option)
    {
        cout << "\033[" << option << ";" << color << "m" << ch << "\033[0m";
    }
}

#endif