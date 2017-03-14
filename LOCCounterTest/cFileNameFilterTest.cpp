#include "cFileNameFilterTest.h"
#include "../LOCCounterLib/cFileNameFilter.h"

CPPUNIT_TEST_SUITE_REGISTRATION(cFileNameFilterTest);

//////////////////////////////////////////////////////////////////////////
cFileNameFilterTest::cFileNameFilterTest()
{
}

//////////////////////////////////////////////////////////////////////////
cFileNameFilterTest::~cFileNameFilterTest()
{
}

//////////////////////////////////////////////////////////////////////////
void cFileNameFilterTest::setUp()
{
}

//////////////////////////////////////////////////////////////////////////
void cFileNameFilterTest::tearDown()
{
}

//////////////////////////////////////////////////////////////////////////
void cFileNameFilterTest::testAddingData()
{
    cFileNameFilter fileFilter;
    fileFilter.AddPattern("abc*.cpp");
    fileFilter.AddPattern("1.h*");
    fileFilter.AddPattern("");
    fileFilter.AddPattern("*");
    fileFilter.AddPattern("*.*");
    fileFilter.AddPattern("*{}*.*");
    fileFilter.AddPattern("{}()[]+|^$,:;-.\"'");
    CPPUNIT_ASSERT(fileFilter.m_sRegExpressions.size() == 6);
    cFileNameFilter::cConstIterator it = fileFilter.m_sRegExpressions.begin();
    CPPUNIT_ASSERT(it->str() == "(abc){1}.*(\\.cpp)+");
    ++it;
    CPPUNIT_ASSERT(it->str() == "(1\\.h){1}.*");
    ++it;
    CPPUNIT_ASSERT(it->str() == ".*");
    ++it;
    CPPUNIT_ASSERT(it->str() == ".*(\\.){1}.*");
    ++it;
    CPPUNIT_ASSERT(it->str() == ".*(\\{\\}){1}.*(\\.){1}.*");
    ++it;
    CPPUNIT_ASSERT(it->str() == "(\\{\\}\\(\\)\\[\\]\\+\\|\\^\\$\\,\\:\\;\\-\\.\"'){1}");
}

//////////////////////////////////////////////////////////////////////////
void cFileNameFilterTest::testFileNameAccepting()
{
    cFileNameFilter fileFilter;
    fileFilter.AddPattern("*._t1");
    fileFilter.AddPattern("*._t2");
    fileFilter.AddPattern("*{}*._t2");

    CPPUNIT_ASSERT(fileFilter.IsFileNameAccepted("../LOCCounterTest/test._t2"));
    CPPUNIT_ASSERT(!fileFilter.IsFileNameAccepted("test._t2._t3"));
    CPPUNIT_ASSERT(fileFilter.IsFileNameAccepted("test._t2._t2"));
    CPPUNIT_ASSERT(fileFilter.IsFileNameAccepted("{}aaa._t2"));
    CPPUNIT_ASSERT(fileFilter.IsFileNameAccepted("aaa{}aaa._t2"));
    CPPUNIT_ASSERT(fileFilter.IsFileNameAccepted("aaa{}._t2"));
    CPPUNIT_ASSERT(fileFilter.IsFileNameAccepted("{}()[]+^$,;-.'._t2"));
}

//////////////////////////////////////////////////////////////////////////
