#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>
#include <unordered_map>
using namespace std;

class Options
{
private:
    unordered_map<char, string> opts;

public:
    Options();
    ~Options();
    
};

Options::Options()
{
    opts['Q'] = "Quit";
    opts['B'] = "Display Board";
    opts['M'] = "Make A Move";
}

Options::~Options()
{
    opts.clear();
}

#endif