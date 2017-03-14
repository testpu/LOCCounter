#ifndef __C_FILE_NAME_COLLECTION_TEST_H_
#define __C_FILE_NAME_COLLECTION_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////////
class cFileNameCollectionTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(cFileNameCollectionTest);
    CPPUNIT_TEST(testDirectoryAdding);
    CPPUNIT_TEST(testFileAdding);
    CPPUNIT_TEST_SUITE_END();
public:
    cFileNameCollectionTest();
    ~cFileNameCollectionTest();

    virtual void setUp();
    virtual void tearDown();

    void testDirectoryAdding();
    void testFileAdding();
};
//////////////////////////////////////////////////////////////////////////

#endif // __C_FILE_NAME_COLLECTION_TEST_H_