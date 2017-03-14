#ifndef __C_TOKEN_H_
#define __C_TOKEN_H_

#include <string>

////////////////////////////////////////////////////////////////////////////////
class cToken
{
public:
    enum Type
    {
        EndLine,
        DoubleSlash,
        SlashStar,
        StarSlash,
        SlashStarSlash,
        DoubleApostroph,
        SlashDoubleApostroph,
        Unknown
    };

    cToken(Type type, const std::string& value);
    cToken(const cToken& src);
    ~cToken();

    inline const std::string& GetValue() const;
    inline Type GetType() const;

private:
    const cToken& operator = (const cToken&);
    std::string m_value;
    Type m_type;
};

////////////////////////////////////////////////////////////////////////////////
inline const std::string& cToken::GetValue() const
{
    return m_value;
}

////////////////////////////////////////////////////////////////////////////////
inline cToken::Type cToken::GetType() const
{
    return m_type;
}

////////////////////////////////////////////////////////////////////////////////

#endif // __C_TOKEN_H_