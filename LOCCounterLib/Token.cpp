#include "Token.h"

////////////////////////////////////////////////////////////////////////////////
cToken::cToken(Type type, const std::string& value) : m_type(type), m_value(value)
{
}

////////////////////////////////////////////////////////////////////////////////
cToken::cToken(const cToken& src) : m_type(src.m_type), m_value(src.m_value)
{
}

////////////////////////////////////////////////////////////////////////////////
cToken::~cToken()
{
}

////////////////////////////////////////////////////////////////////////////////