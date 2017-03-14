#ifndef __SIMPLE_PARSER_H_
#define __SIMPLE_PARSER_H_

#include <istream>
#include "TokenBuilder.h"
#include "CommentAnalyser.h"

////////////////////////////////////////////////////////////////////////////////
class cSimpleParser
{
public:
    static cSimpleParser& GetInstance();
    int ComputeCodeLines(std::istream& input);
    int ComputeCodeLines(cTokenBuilder& tokenBuilder);
private:
    cSimpleParser();

    cCommentAnalyser m_commentAnalyser;
};

////////////////////////////////////////////////////////////////////////////////

#endif // __SIMPLE_PARSER_H_