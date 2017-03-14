#include "cDirectoryScannerTest.h"
#include "../LOCCounterLib/cDirectoryScanner.h"
#include "../LOCCounterLib/cCommonFileFilter.h"
#include "cUtils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(cDirectoryScannerTest);

//////////////////////////////////////////////////////////////////////////
cDirectoryScannerTest::cDirectoryScannerTest()
{
}

//////////////////////////////////////////////////////////////////////////
cDirectoryScannerTest::~cDirectoryScannerTest()
{
}

//////////////////////////////////////////////////////////////////////////
void cDirectoryScannerTest::setUp()
{
    cUtils::CreateDirectory(cUtils::GetTestDirectoryPath());
}

//////////////////////////////////////////////////////////////////////////
void cDirectoryScannerTest::tearDown()
{
    cUtils::DeleteDirectory(cUtils::GetTestDirectoryPath());
}

//////////////////////////////////////////////////////////////////////////
void cDirectoryScannerTest::testSimpleScan()
{
    static const std::string sTestPath = cUtils::GetTestDirectoryPath() + "/simple_scan";
    cUtils::CreateDirectory(sTestPath);
    static std::set<std::string> sFileNames;
    if (sFileNames.empty())
    {
        sFileNames.insert(sTestPath + "/1._t1");
        sFileNames.insert(sTestPath + "/2._t1");
        sFileNames.insert(sTestPath + "/3._t1");
    }

    {
        for (std::set<std::string>::const_iterator it = sFileNames.begin(); it != sFileNames.end(); ++it)
        {
            cUtils::CreateFile(*it);
        }
    }

    cCommonFileFilter filter;
    cDirectoryScanner scanner(sTestPath, false, &filter);
    scanner.Scan();
    CPPUNIT_ASSERT(std::distance(scanner.GetProcessedFileNamesBeginIt(), scanner.GetProcessedFileNamesEndIt()) == 3);
    cDirectoryScanner::cConstIterator it = scanner.GetProcessedFileNamesBeginIt();

    CPPUNIT_ASSERT(sFileNames.find(*it++) != sFileNames.end());
    CPPUNIT_ASSERT(sFileNames.find(*it++) != sFileNames.end());
    CPPUNIT_ASSERT(sFileNames.find(*it++) != sFileNames.end());
}

//////////////////////////////////////////////////////////////////////////
void cDirectoryScannerTest::testRecursiveScan()
{
    static const std::string sTestPath = cUtils::GetTestDirectoryPath() + "/complex_scan";
    static const std::string sChildDir1Name = sTestPath + "/child1";
    static const std::string sChildDir2Name = sTestPath + "/child2";
    static const std::string sChildDir3Name = sTestPath + "/child2/child2_child";

    cUtils::CreateDirectory(sTestPath);
    cUtils::CreateDirectory(sChildDir1Name);
    cUtils::CreateDirectory(sChildDir2Name);
    cUtils::CreateDirectory(sChildDir3Name);

    static std::set<std::string> sFileNames;
    if (sFileNames.empty())
    {
        sFileNames.insert(sTestPath + "/child1/1._t3");
        sFileNames.insert(sTestPath + "/child2/2._t3");
        sFileNames.insert(sTestPath + "/child2/child2_child/3._t3");
    }

    {
        for (std::set<std::string>::const_iterator it = sFileNames.begin(); it != sFileNames.end(); ++it)
        {
            cUtils::CreateFile(*it);
        }
    }

    sFileNames.insert(sChildDir1Name);
    sFileNames.insert(sChildDir2Name);
    sFileNames.insert(sChildDir3Name);

    cCommonFileFilter filter;
    cDirectoryScanner scanner(sTestPath, true, &filter);
    scanner.Scan();
    CPPUNIT_ASSERT(std::distance(scanner.GetProcessedFileNamesBeginIt(), scanner.GetProcessedFileNamesEndIt()) == sFileNames.size());
    cDirectoryScanner::cConstIterator it = scanner.GetProcessedFileNamesBeginIt();
    cDirectoryScanner::cConstIterator itEnd = scanner.GetProcessedFileNamesEndIt();
    for (; it != itEnd; ++it)
    {
        CPPUNIT_ASSERT(sFileNames.find(*it) != sFileNames.end());
    }
}

//////////////////////////////////////////////////////////////////////////
void cDirectoryScannerTest::testScanWithFilter()
{
    static const std::string sTestPath = cUtils::GetTestDirectoryPath() + "/complex_scan";
    cUtils::CreateDirectory(sTestPath);

    static std::set<std::string> sFileNames;
    if (sFileNames.empty())
    {
        sFileNames.insert(sTestPath + "/1._t2");
        sFileNames.insert(sTestPath + "/2._t2");
        sFileNames.insert(sTestPath + "/3._t2");
        sFileNames.insert(sTestPath + "/3._t1");
    }

    {
        for (std::set<std::string>::const_iterator it = sFileNames.begin(); it != sFileNames.end(); ++it)
        {
            cUtils::CreateFile(*it);
        }
    }

    {
        cCommonFileFilter filter;
        cDirectoryScanner scanner(sTestPath, true, &filter);
        scanner.Scan();
        CPPUNIT_ASSERT(std::distance(scanner.GetProcessedFileNamesBeginIt(), scanner.GetProcessedFileNamesEndIt()) == 4);
    }

    {
        cCommonFileFilter filter;
        filter.AddPatternIncludingFiles("*._t2");
        cDirectoryScanner scanner(sTestPath, true, &filter);
        scanner.Scan();
        CPPUNIT_ASSERT(std::distance(scanner.GetProcessedFileNamesBeginIt(), scanner.GetProcessedFileNamesEndIt()) == 3);
        cDirectoryScanner::cConstIterator it = scanner.GetProcessedFileNamesBeginIt();

        CPPUNIT_ASSERT(sFileNames.find(*it++) != sFileNames.end());
        CPPUNIT_ASSERT(sFileNames.find(*it++) != sFileNames.end());
        CPPUNIT_ASSERT(sFileNames.find(*it++) != sFileNames.end());
    }
}

//////////////////////////////////////////////////////////////////////////
