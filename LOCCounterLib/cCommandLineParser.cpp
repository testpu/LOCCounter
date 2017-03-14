#include "cCommandLineParser.h"
#include "cLOCCounter.h"
#include "cCommonFileFilter.h"

//////////////////////////////////////////////////////////////////////////
const std::string& cCommandLineParser::GetCommandLineFormat()
{
    static std::string sCommandLineFormat("</o:output_file_name> </if:input_file_name>\n"
        "</id:input_directory [/rs] [/+n:included_file_names_filter] [/-n:excluded_file_names_filter]>");
    return sCommandLineFormat;
}

//////////////////////////////////////////////////////////////////////////
cCommandLineParser::cCommandLineParser(int argc, char* argv[])
{
    if (argc < 3)
    {
        throw std::invalid_argument("No input or output file names specified");
    }

    m_spLOCCounter.reset(new cLOCCounter());

    for (int argIndex = 1; argIndex < argc; argIndex++)
    {
        std::string sArg = argv[argIndex];
        if (sArg.find("/o:") == 0)
        {
            if (!m_outputFileData.first.empty())
            {
                throw std::invalid_argument("Input file name is already set");
            }
            m_outputFileData = std::make_pair(&sArg[3], false);
        }
        else if (sArg.find("/o+:") == 0)
        {
            if (!m_outputFileData.first.empty())
            {
                throw std::invalid_argument("Input file name is already set");
            }
            m_outputFileData = std::make_pair(&sArg[4], true);
        }
        else if (sArg.find("/if:") == 0)
        {
            std::string sInputFileName(&sArg[4]);
            m_spLOCCounter->AddFile(sInputFileName);
        }
        else if (!parseDirectoryCommand(argc, argv, argIndex))
        {
            throw std::invalid_argument("Incorrect command line format");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
cCommandLineParser::~cCommandLineParser()
{
}

//////////////////////////////////////////////////////////////////////////
cLOCCounter& cCommandLineParser::GetLOCCounter()
{
    return *m_spLOCCounter;
}

//////////////////////////////////////////////////////////////////////////
typedef cCommandLineParser::tOutputFileName tOutputFileName;
typedef cCommandLineParser::tOutputAppendFlag tOutputAppendFlag;

const std::pair<tOutputFileName, tOutputAppendFlag>& cCommandLineParser::GetOutputFileData()
{
    return m_outputFileData;
}

//////////////////////////////////////////////////////////////////////////
bool cCommandLineParser::parseDirectoryCommand(int argc, char* argv[], int& io_argIndex)
{
    bool bIsFound = false;
    std::string sDirectoryName;

    std::string sArg = argv[io_argIndex];
    if (sArg.find("/id:") == 0)
    {
        sDirectoryName = &sArg[4];
        bIsFound = true;
    }

    if (bIsFound)
    {
        bool bRecursiveScan = false;
        cCommonFileFilter fileFilter;
        for (; io_argIndex + 1 < argc; ++io_argIndex)
        {
            std::string sArg = argv[io_argIndex + 1];
            if (sArg.find("/+n:") == 0)
            {
                std::string sFilter(&sArg[4]);
                fileFilter.AddPatternIncludingFiles(sFilter);
            }
            else if (sArg.find("/-n:") == 0)
            {
                std::string sFilter(&sArg[4]);
                fileFilter.AddPatternExcludingFiles(sFilter);
            }
            else if (sArg.find("/rs") == 0)
            {
                bRecursiveScan = true;
            }
            else
            {
                break;
            }
        }
        m_spLOCCounter->AddDirectory(sDirectoryName, bRecursiveScan, &fileFilter);
    }
    return bIsFound;
}

//////////////////////////////////////////////////////////////////////////
