#ifndef __C_SIMPLE_PARSER_TEST_H_
#define __C_SIMPLE_PARSER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

//////////////////////////////////////////////////////////////////////////
class cSimpleParserTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(cSimpleParserTest);
    CPPUNIT_TEST(testSimpleCommentParsing);
    CPPUNIT_TEST(testComplexCommetParsing);
    CPPUNIT_TEST(testStringParsing);
    CPPUNIT_TEST(testEmptyLinesParsing);
    CPPUNIT_TEST(testEmptyStreamParsing);
    CPPUNIT_TEST_SUITE_END();
public:
    cSimpleParserTest();
    ~cSimpleParserTest();

    virtual void setUp();
    virtual void tearDown();

    void testSimpleCommentParsing();
    void testComplexCommetParsing();
    void testEmptyLinesParsing();
    void testEmptyStreamParsing();
    void testStringParsing();
};
//////////////////////////////////////////////////////////////////////////


#endif // __C_SIMPLE_PARSER_TEST_H_

