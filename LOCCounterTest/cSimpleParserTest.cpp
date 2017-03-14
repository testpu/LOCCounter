#include "cSimpleParserTest.h"
#include "../LOCCounterLib/SimpleParser.h"

CPPUNIT_TEST_SUITE_REGISTRATION(cSimpleParserTest);

//////////////////////////////////////////////////////////////////////////
cSimpleParserTest::cSimpleParserTest()
{
}

//////////////////////////////////////////////////////////////////////////
cSimpleParserTest::~cSimpleParserTest()
{
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::setUp()
{
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::tearDown()
{
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::testSimpleCommentParsing()
{
    {
        std::string sContent = "   ///**/\"\"  ";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 0);
    }

    {
        std::string sContent = "   ///**/\"\"  \n";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 0);
    }

    {
        std::string sContent = "\t\"   ///**/\"   ";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
    {
        std::string sContent = "\t\"   ///**/\"   //\n\t// some comment";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::testComplexCommetParsing()
{
    {
        std::string sContent = "   /*/**/\"\" //\n // \n\"\" ";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 2);
    }
    {
        std::string sContent = "   /*\n\n*/ \t";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 0);
    }
    {
        std::string sContent = "some_code/*\n\n*/ \t";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
    {
        std::string sContent = "   /*\n\n*/ some code;";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
    {
        std::string sContent = "   /*\n\n/*/ some code;";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
    {
        std::string sContent = "/**\n*\n*/\n\n some code;";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::testEmptyLinesParsing()
{
    {
        std::string sContent = "\n   ";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 0);
    }

    {
        std::string sContent = "\n   \n";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 0);
    }
    {
        std::string sContent = "some_code\n   \nsome_code";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 2);
    }
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::testEmptyStreamParsing()
{
    std::string sContent;
    std::stringstream streamContent(sContent);
    int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
    CPPUNIT_ASSERT(nCodeLines == 0);
}

//////////////////////////////////////////////////////////////////////////
void cSimpleParserTest::testStringParsing()
{
    {
        std::string sContent = "\"/*some comment*/\"";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
    {
        std::string sContent = "\"//\"";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
    {
        std::string sContent = "\" \\\" \\\" \"";
        std::stringstream streamContent(sContent);
        int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(streamContent);
        CPPUNIT_ASSERT(nCodeLines == 1);
    }
}

//////////////////////////////////////////////////////////////////////////
