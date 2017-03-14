#include "TokenBuilder.h"

////////////////////////////////////////////////////////////////////////////////
cTokenBuilder::cTokenBuilder() : m_currentToken(m_tokens.begin())
{
    Reset();
}

////////////////////////////////////////////////////////////////////////////////
cTokenBuilder::cTokenBuilder(std::istream& input) : m_currentToken(m_tokens.begin())
{
    ParseToTokens(input);
    Reset();
}

////////////////////////////////////////////////////////////////////////////////
cTokenBuilder::~cTokenBuilder()
{
}

////////////////////////////////////////////////////////////////////////////////
const cToken& cTokenBuilder::ReplyNextToken()
{
    const cToken& token(*m_currentToken);
    ++m_currentToken;
    return token;
}

////////////////////////////////////////////////////////////////////////////////
void cTokenBuilder::Reset()
{
    m_currentToken = m_tokens.begin();
}

////////////////////////////////////////////////////////////////////////////////
bool cTokenBuilder::IsNoTokensAnymore()
{
    return !(m_currentToken != m_tokens.end());
}

////////////////////////////////////////////////////////////////////////////////
void cTokenBuilder::ParseToTokens(std::istream& input)
{
    while (!input.eof())
    {
        std::string codeLine;
        getline(input, codeLine);

        for (int idx = 0; idx < static_cast<int>(codeLine.size());)
        {
            if (!IsSpace(codeLine[idx]))
            {
                if (codeLine.find("//", idx) == idx)
                {
                    m_tokens.push_back(cToken(cToken::DoubleSlash, "//"));
                    idx += 2;
                }
                if (codeLine.find("/*/", idx) == idx)
                {
                    m_tokens.push_back(cToken(cToken::SlashStarSlash, "/*/"));
                    idx += 3;
                }
                else if (codeLine.find("/*", idx) == idx)
                {
                    m_tokens.push_back(cToken(cToken::SlashStar, "/*"));
                    idx += 2;
                }
                else if (codeLine.find("*/", idx) == idx)
                {
                    m_tokens.push_back(cToken(cToken::StarSlash, "*/"));
                    idx += 2;
                }
                else if (codeLine.find("\\\"", idx) == idx)
                {
                    m_tokens.push_back(cToken(cToken::SlashDoubleApostroph, "\\\""));
                    idx += 2;
                }
                else
                {
                    std::string token = ReadTokenString(codeLine, idx);
                    if (token == "\"")
                    {
                        m_tokens.push_back(cToken(cToken::DoubleApostroph, "\""));
                    }
                    else
                    {
                        m_tokens.push_back(cToken(cToken::Unknown, token));
                    }
                }
            }
            else
            {
                idx++;
            }
        }
        m_tokens.push_back(cToken(cToken::EndLine, "\n"));
    }
}

////////////////////////////////////////////////////////////////////////////////
bool cTokenBuilder::IsDelimiter(char symbol) const
{
    static std::string delimiters = "{}()+-*/=|&!%?<>:;\"";
    return (IsSpace(symbol) || delimiters.find(std::string(1, symbol)) != -1);
}

////////////////////////////////////////////////////////////////////////////////
bool cTokenBuilder::IsSpace(char symbol) const
{
    return (symbol == ' ' || symbol == '\t');
}

////////////////////////////////////////////////////////////////////////////////
std::string cTokenBuilder::ReadTokenString(const std::string& codeLine, int& idx)
{
    std::string token;
    if (IsDelimiter(codeLine[idx]))
    {
        token = std::string(1, codeLine[idx]);
        idx++;
    }
    else
    {
        while (!IsDelimiter(codeLine[idx]) && idx < static_cast<int>(codeLine.size()))
        {
            token += codeLine[idx];
            idx++;
        }
    }
    return token;
}

////////////////////////////////////////////////////////////////////////////////
