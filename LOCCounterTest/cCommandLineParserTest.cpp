#include "cCommandLineParserTest.h"
#include "cCommandLineParser.h"
#include "cLOCCounter.h"
#include "cUtils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(cCommandLineParserTest);

//////////////////////////////////////////////////////////////////////////
cCommandLineParserTest::cCommandLineParserTest()
{
}

//////////////////////////////////////////////////////////////////////////
cCommandLineParserTest::~cCommandLineParserTest()
{
}


//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::setUp()
{
    cUtils::CreateDirectory(cUtils::GetTestDirectoryPath());
}

//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::tearDown()
{
    cUtils::DeleteDirectory(cUtils::GetTestDirectoryPath());
}

//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::testFileReading()
{
    static const std::string sOutputFilePath = cUtils::GetTestDirectoryPath() + "/output_file.txt";
    static const std::string sInputFilePath = cUtils::GetTestDirectoryPath() + "/test_file.txt";
    cUtils::CreateFile(sInputFilePath);

    std::string sParamOutputFile = "/o:" + sOutputFilePath;
    std::string sParamInputFile = "/if:" + sInputFilePath;

    char* argv[] =
    {
        "executable_module",
        const_cast<char*>(sParamOutputFile.c_str()),
        const_cast<char*>(sParamInputFile.c_str())
    };
    const int argc = sizeof(argv) / sizeof(argv[0]);
    cCommandLineParser commandLineParser(argc, argv);
    commandLineParser.GetLOCCounter().RunLOCsCounting();

    cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
    cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

    CPPUNIT_ASSERT(distance(it, itEnd) == 1);
    CPPUNIT_ASSERT(it->first == sInputFilePath);
}

//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::testDirectoryReadingWithoutFilters()
{
    static const std::string sOutputFilePath = cUtils::GetTestDirectoryPath() + "/output_file.txt";
    static const std::string sInputFilePath = cUtils::GetTestDirectoryPath() + "/test_file.txt";
    cUtils::CreateFile(sInputFilePath);

    std::string sParamOutputFile = "/o:" + sOutputFilePath;
    std::string sParamInputDirectory = "/id:" + cUtils::GetTestDirectoryPath();

    char* argv[] =
    {
        "executable_module",
        const_cast<char*>(sParamOutputFile.c_str()),
        const_cast<char*>(sParamInputDirectory.c_str())
    };
    const int argc = sizeof(argv) / sizeof(argv[0]);
    cCommandLineParser commandLineParser(argc, argv);
    commandLineParser.GetLOCCounter().RunLOCsCounting();

    cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
    cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

    CPPUNIT_ASSERT(distance(it, itEnd) == 1);
    CPPUNIT_ASSERT(it->first == sInputFilePath);
}

//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::testDirectoryReadingWithIncludeFilter()
{
    static const std::string sOutputFilePath = cUtils::GetTestDirectoryPath() + "/output_file.txt";
    static const std::string sInputFilePath1 = cUtils::GetTestDirectoryPath() + "/test_file._t1";
    static const std::string sInputFilePath2 = cUtils::GetTestDirectoryPath() + "/test_file._t2";
    cUtils::CreateFile(sInputFilePath1);
    cUtils::CreateFile(sInputFilePath2);

    std::string sParamOutputFile = "/o:" + sOutputFilePath;
    std::string sParamInputDirectory = "/id:" + cUtils::GetTestDirectoryPath();
    std::string sParamIncludeFilter1 = "/+n:*._t1";

    {
        char* argv[] =
        {
            "executable_module",
            const_cast<char*>(sParamOutputFile.c_str()),
            const_cast<char*>(sParamInputDirectory.c_str()),
            const_cast<char*>(sParamIncludeFilter1.c_str())
        };
        const int argc = sizeof(argv) / sizeof(argv[0]);
        cCommandLineParser commandLineParser(argc, argv);
        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

        CPPUNIT_ASSERT(distance(it, itEnd) == 1);
        CPPUNIT_ASSERT(it->first == sInputFilePath1);
    }

    std::string sParamIncludeFilter2 = "/+n:*._t2";
    {
        char* argv[] =
        {
            "executable_module",
            const_cast<char*>(sParamOutputFile.c_str()),
            const_cast<char*>(sParamInputDirectory.c_str()),
            const_cast<char*>(sParamIncludeFilter1.c_str()),
            const_cast<char*>(sParamIncludeFilter2.c_str())
        };
        const int argc = sizeof(argv) / sizeof(argv[0]);
        cCommandLineParser commandLineParser(argc, argv);
        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

        CPPUNIT_ASSERT(distance(it, itEnd) == 2);
        CPPUNIT_ASSERT(it->first == sInputFilePath1);
        ++it;
        CPPUNIT_ASSERT(it->first == sInputFilePath2);
    }
}

//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::testDirectoryReadingWithExcludeFilter()
{
    static const std::string sOutputFilePath = cUtils::GetTestDirectoryPath() + "/output_file.txt";
    static const std::string sInputFilePath1 = cUtils::GetTestDirectoryPath() + "/test_file._t1";
    static const std::string sInputFilePath2 = cUtils::GetTestDirectoryPath() + "/test_file._t2";
    cUtils::CreateFile(sInputFilePath1);
    cUtils::CreateFile(sInputFilePath2);

    std::string sParamOutputFile = "/o:" + sOutputFilePath;
    std::string sParamInputDirectory = "/id:" + cUtils::GetTestDirectoryPath();
    std::string sParamExcludeFilter1 = "/-n:*._t2";

    {
        char* argv[] =
        {
            "executable_module",
            const_cast<char*>(sParamOutputFile.c_str()),
            const_cast<char*>(sParamInputDirectory.c_str()),
            const_cast<char*>(sParamExcludeFilter1.c_str())
        };
        const int argc = sizeof(argv) / sizeof(argv[0]);
        cCommandLineParser commandLineParser(argc, argv);
        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

        CPPUNIT_ASSERT(distance(it, itEnd) == 1);
        CPPUNIT_ASSERT(it->first == sInputFilePath1);
    }

    std::string sParamExcludeFilter2 = "/-n:*._t1";
    {
        char* argv[] =
        {
            "executable_module",
            const_cast<char*>(sParamOutputFile.c_str()),
            const_cast<char*>(sParamInputDirectory.c_str()),
            const_cast<char*>(sParamExcludeFilter1.c_str()),
            const_cast<char*>(sParamExcludeFilter2.c_str())
        };
        const int argc = sizeof(argv) / sizeof(argv[0]);
        cCommandLineParser commandLineParser(argc, argv);
        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

        CPPUNIT_ASSERT(distance(it, itEnd) == 0);
    }
}

//////////////////////////////////////////////////////////////////////////
void cCommandLineParserTest::testDirectoryReadingWithComplexFilters()
{
    static const std::string sOutputFilePath = cUtils::GetTestDirectoryPath() + "/output_file.txt";
    static const std::string sInputFilePath1 = cUtils::GetTestDirectoryPath() + "/test_file._t1";
    static const std::string sInputFilePath2 = cUtils::GetTestDirectoryPath() + "/test_file._t2";
    static const std::string sInputFilePath3 = cUtils::GetTestDirectoryPath() + "/test_file._t3";
    cUtils::CreateFile(sInputFilePath1);
    cUtils::CreateFile(sInputFilePath2);
    cUtils::CreateFile(sInputFilePath3);

    std::string sParamOutputFile = "/o:" + sOutputFilePath;
    std::string sParamInputDirectory = "/id:" + cUtils::GetTestDirectoryPath();
    std::string sParamIncludeFilter1 = "/+n:test_file._t?";
    std::string sParamIncludeFilter2 = "/+n:test_file._t2";
    std::string sParamExcludeFilter1 = "/-n:*._t2";
    std::string sParamExcludeFilter2 = "/-n:*._t3";

    {
        char* argv[] =
        {
            "executable_module",
            const_cast<char*>(sParamOutputFile.c_str()),
            const_cast<char*>(sParamInputDirectory.c_str()),
            const_cast<char*>(sParamIncludeFilter1.c_str()),
            const_cast<char*>(sParamExcludeFilter1.c_str()),
            const_cast<char*>(sParamExcludeFilter2.c_str())
        };
        const int argc = sizeof(argv) / sizeof(argv[0]);
        cCommandLineParser commandLineParser(argc, argv);
        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

        CPPUNIT_ASSERT(distance(it, itEnd) == 1);
        CPPUNIT_ASSERT(it->first == sInputFilePath1);
    }

    {
        char* argv[] =
        {
            "executable_module",
            const_cast<char*>(sParamOutputFile.c_str()),
            const_cast<char*>(sParamInputDirectory.c_str()),
            const_cast<char*>(sParamIncludeFilter1.c_str()),
            const_cast<char*>(sParamExcludeFilter1.c_str()),
            const_cast<char*>(sParamExcludeFilter2.c_str()),
            const_cast<char*>(sParamIncludeFilter2.c_str())
        };
        const int argc = sizeof(argv) / sizeof(argv[0]);
        cCommandLineParser commandLineParser(argc, argv);
        commandLineParser.GetLOCCounter().RunLOCsCounting();

        cLOCCounter::cConstIterator itEnd = commandLineParser.GetLOCCounter().GetProcessedFileLOCsEndIt();
        cLOCCounter::cConstIterator it = commandLineParser.GetLOCCounter().GetProcessedFileLOCsBeginIt();

        CPPUNIT_ASSERT(distance(it, itEnd) == 1);
        CPPUNIT_ASSERT(it->first == sInputFilePath1);
    }
}

//////////////////////////////////////////////////////////////////////////
