#ifndef __C_COMMAND_LINE_PARSER_TEST_H_
#define __C_COMMAND_LINE_PARSER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////////
class cCommandLineParserTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(cCommandLineParserTest);
    CPPUNIT_TEST(testFileReading);
    CPPUNIT_TEST(testDirectoryReadingWithoutFilters);
    CPPUNIT_TEST(testDirectoryReadingWithIncludeFilter);
    CPPUNIT_TEST(testDirectoryReadingWithExcludeFilter);
    CPPUNIT_TEST(testDirectoryReadingWithComplexFilters);
    CPPUNIT_TEST_SUITE_END();

public:
    cCommandLineParserTest();
    ~cCommandLineParserTest();

    virtual void setUp();
    virtual void tearDown();

    void testFileReading();
    void testDirectoryReadingWithoutFilters();
    void testDirectoryReadingWithIncludeFilter();
    void testDirectoryReadingWithExcludeFilter();
    void testDirectoryReadingWithComplexFilters();
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_COMMAND_LINE_PARSER_TEST_H_