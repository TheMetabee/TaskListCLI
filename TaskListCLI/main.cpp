// TodoListCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "TaskCLI.h"

#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    std::vector<std::string> argsVec(argv, argv + argc);
    TaskCLI::parseArguments(argsVec);

}

