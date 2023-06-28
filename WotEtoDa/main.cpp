// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <iomanip>

#include "FmtGuard.h"
#include "EncodingTable.h"
#include "HuffmanTree.h"
#include "Commander.h"
#include "Commands.h"
#include "Exceptions.h"

void handleCommands(std::istream& in, std::ostream& out);

int main()
{
    try
    {
        handleCommands(std::cin, std::cout);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
        return -1;
    }
    return 0;
}

// НЕ ЗАБУДЬ КОНСТ

void handleCommands(std::istream& in, std::ostream& out)
{
    FmtGuard fmtGuard(out);
    out << std::fixed << std::setprecision(2);
    Commander cmd;
    std::string command;

    while (in >> command)
    {
        if (command == "ENCODE")
        {
            cmd.setCommand(Commands::EncodeNum);
        }
        else if (command == "DECODE")
        {
            cmd.setCommand(Commands::DecodeNum);
        }
        else if (command == "ANALYZE")
        {
            cmd.setCommand(Commands::AnalyzeNum);
        }
        else
        {
            std::cerr << "Unknown command." << std::endl;
        }

        std::string fileName;
        in >> fileName;
        if (!in)
        {
            throw ReadingCommandStreamException();
        }

        cmd.setFileName(fileName);

        try
        {
            std::string output = cmd.invoke();
            out << output << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        
    }
    if (!in && !in.eof())
    {
        throw ReadingCommandStreamException();
    }
}
