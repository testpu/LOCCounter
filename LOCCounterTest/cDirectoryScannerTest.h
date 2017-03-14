#ifndef __C_FILE_FINDER_TEST_H_
#define __C_FILE_FINDER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////////
class cDirectoryScannerTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(cDirectoryScannerTest);
    CPPUNIT_TEST(testSimpleScan);
    CPPUNIT_TEST(testRecursiveScan);
    CPPUNIT_TEST(testScanWithFilter);
    CPPUNIT_TEST_SUITE_END();
public:
    cDirectoryScannerTest();
    ~cDirectoryScannerTest();

    virtual void setUp();
    virtual void tearDown();

    void testSimpleScan();
    void testRecursiveScan();
    void testScanWithFilter();
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_FILE_FINDER_TEST_H_
