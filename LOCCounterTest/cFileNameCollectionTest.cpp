#include "cFileNameCollectionTest.h"
#include "../LOCCounterLib/cFileNameCollection.h"
#include "../LOCCounterLib/cCommonFileFilter.h"
#include "cUtils.h"

CPPUNIT_TEST_SUITE_REGISTRATION(cFileNameCollectionTest);

//////////////////////////////////////////////////////////////////////////
cFileNameCollectionTest::cFileNameCollectionTest()
{
}

//////////////////////////////////////////////////////////////////////////
cFileNameCollectionTest::~cFileNameCollectionTest()
{
}

//////////////////////////////////////////////////////////////////////////
void cFileNameCollectionTest::setUp()
{
    cUtils::CreateDirectory(cUtils::GetTestDirectoryPath());

    static std::set<std::string> sFileNames;
    if (sFileNames.empty())
    {
        sFileNames.insert(cUtils::GetTestDirectoryPath() + "/1._t1");
        sFileNames.insert(cUtils::GetTestDirectoryPath() + "/2._t1");
        sFileNames.insert(cUtils::GetTestDirectoryPath() + "/3._t2");
    }

    for (std::set<std::string>::const_iterator it = sFileNames.begin(); it != sFileNames.end(); ++it)
    {
        cUtils::CreateFile(*it);
    }
}

//////////////////////////////////////////////////////////////////////////
void cFileNameCollectionTest::tearDown()
{
    cUtils::DeleteDirectory(cUtils::GetTestDirectoryPath());
}

//////////////////////////////////////////////////////////////////////////
void cFileNameCollectionTest::testDirectoryAdding()
{
    cFileNameCollection fileNameCollection;
    cCommonFileFilter filter;
    filter.AddPatternIncludingFiles("*._t1");
    fileNameCollection.AddDirectory(cUtils::GetTestDirectoryPath(), true, &filter);

    CPPUNIT_ASSERT(fileNameCollection.m_sFilePaths.size() == 2);
}

//////////////////////////////////////////////////////////////////////////
void cFileNameCollectionTest::testFileAdding()
{
    static const std::string sFileName = cUtils::GetTestDirectoryPath() + "/1._t1";
    cFileNameCollection fileNameCollection;

    fileNameCollection.AddFile(sFileName);
    CPPUNIT_ASSERT(fileNameCollection.m_sFilePaths.size() == 1);
}

//////////////////////////////////////////////////////////////////////////

