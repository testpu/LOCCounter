#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include "cLOCCounter.h"
#include "cCommandLineParser.h"

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    try
    {
        cCommandLineParser commandLineParser(argc, argv);

        std::ofstream outFile(
            commandLineParser.GetOutputFileData().first.c_str(),
            commandLineParser.GetOutputFileData().second ? std::ios::app : std::ios::trunc);
        if (!outFile.is_open())
        {
            throw std::invalid_argument("Cannot open output file");
        }

        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd =
            commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        for (cLOCCounter::cConstIterator it =
            commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt(); it != itEnd; ++it)
        {
            outFile.width(10);
            outFile << it->second;
            outFile << " | " << it->first << std::endl;
        }

        outFile.width(10);
        outFile << commandLineParser.GetLOCCounter().GetTotalLOCsCount();
        outFile << " | " << "Total LOCs count";
        outFile << std::endl;
        outFile << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }
}

////////////////////////////////////////////////////////////////////////////////
