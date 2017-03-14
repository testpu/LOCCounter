#ifndef __C_FILE_FILTER_TEST_H_
#define __C_FILE_FILTER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////////
class cFileNameFilterTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(cFileNameFilterTest);
    CPPUNIT_TEST(testAddingData);
    CPPUNIT_TEST(testFileNameAccepting);
    CPPUNIT_TEST_SUITE_END();
public:
    cFileNameFilterTest();
    ~cFileNameFilterTest();

    virtual void setUp();
    virtual void tearDown();

    void testAddingData();
    void testFileNameAccepting();
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_FILE_FILTER_TEST_H_
