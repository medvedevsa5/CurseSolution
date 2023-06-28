// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <iterator>

#include "FmtGuard.h"
#include "EncodingTable.h"
#include "HuffmanTree.h"
#include "Commander.h"
#include "Commands.h"

void handleCommands(std::istream& in, std::ostream& out);

int main()
{
    handleCommands(std::cin, std::cout);

    return 0;
}

// НЕ ЗАБУДЬ КОНСТ

void handleCommands(std::istream& in, std::ostream& out)
{
    Commander cmd;
    std::string command;

    while (in >> command)
    {
        if (command == "COMPRESS")
        {
            cmd.setCommand(Commands::EncodeNum);
        }
        else if (command == "DECOMPRESS")
        {
            cmd.setCommand(Commands::DecodeNum);
        }
        else if (command == "ANALYZE")
        {
            cmd.setCommand(Commands::AnalyzeNum);
        }
        else
        {
            std::cerr << "Unknown command.";
        }
        std::string fileName;
        in >> fileName;
        if (!in)
        {
            //throw 
        }

        cmd.setFileName(fileName);

        try
        {
            cmd.invoke();
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        out << "DONE" << std::endl;
    }
}
