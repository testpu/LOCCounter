#ifndef __TOKEN_BUILDER_H_
#define __TOKEN_BUILDER_H_

#include <list>
#include <istream>
#include "Token.h"

class cTokenBuilder
{
public:
    cTokenBuilder();
    cTokenBuilder(std::istream& input);
    ~cTokenBuilder();

    void ParseToTokens(std::istream& input);
    void Reset();

    const cToken& ReplyNextToken();

    bool IsNoTokensAnymore();
private:
    bool IsDelimiter(char symbol) const;
    bool IsSpace(char symbol) const;
    std::string ReadTokenString(const std::string& codeLine, int& idx);

    std::list<cToken> m_tokens;
    std::list<cToken>::const_iterator m_currentToken;
};

#endif // __TOKEN_BUILDER_H_