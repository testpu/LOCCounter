#include "SimpleParser.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
cSimpleParser& cSimpleParser::GetInstance()
{
    static cSimpleParser parser;
    return parser;
}

////////////////////////////////////////////////////////////////////////////////
cSimpleParser::cSimpleParser()
{
}

////////////////////////////////////////////////////////////////////////////////
int cSimpleParser::ComputeCodeLines(std::istream& input)
{
    cTokenBuilder tokenBuilder(input);
    return ComputeCodeLines(tokenBuilder);
}

////////////////////////////////////////////////////////////////////////////////
int cSimpleParser::ComputeCodeLines(cTokenBuilder& tokenBuilder)
{
    // output trace info
    /*
    tokenBuilder.Reset();
    while(!tokenBuilder.IsNoTokensAnymore())
    {
    const cToken& token = tokenBuilder.ReplyNextToken();
    std::cout << token.GetValue();
    }
    */

    tokenBuilder.Reset();
    int linesCount = 0;

    bool bShallBeCounted = false;

    while (!tokenBuilder.IsNoTokensAnymore())
    {
        const cToken& token = tokenBuilder.ReplyNextToken();
        m_commentAnalyser.Analyse(token);
        bool bIsCommentIsActive = m_commentAnalyser.IsActive();

        bool bEndLine = (token.GetType() == cToken::EndLine);

        if (bEndLine || tokenBuilder.IsNoTokensAnymore())
        {
            if (bShallBeCounted)
            {
                linesCount++;
                bShallBeCounted = false;
            }
        }
        else if (!bIsCommentIsActive)
        {
            bShallBeCounted = true;
        }
    }


    return linesCount;
}

////////////////////////////////////////////////////////////////////////////////
