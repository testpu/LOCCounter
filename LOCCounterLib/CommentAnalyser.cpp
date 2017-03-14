#include "CommentAnalyser.h"

////////////////////////////////////////////////////////////////////////////////
cCommentAnalyser::cCommentAnalyser()
    : m_bIsActive(false)
    , m_bIsOneLineComment(false)
    , m_stringAnalyser(this)
    , m_bShallBeDeactivated(false)
{
}

////////////////////////////////////////////////////////////////////////////////
cCommentAnalyser::~cCommentAnalyser()
{
}

////////////////////////////////////////////////////////////////////////////////
void cCommentAnalyser::Analyse(const cToken& token)
{
    if (m_bShallBeDeactivated)
    {
        m_bIsActive = false;
        m_bShallBeDeactivated = false;
    }

    m_stringAnalyser.Analyse(token);
    if (!m_stringAnalyser.IsActive())
    {
        if (!IsActive())
        {
            if (token.GetType() == cToken::DoubleSlash)
            {
                m_bIsActive = true;
                m_bIsOneLineComment = true;
            }
            else if (token.GetType() == cToken::SlashStar || token.GetType() == cToken::SlashStarSlash)
            {
                m_bIsActive = true;
                m_bIsOneLineComment = false;
            }
        }
        else
        {
            if (m_bIsOneLineComment)
            {
                m_bShallBeDeactivated = (token.GetType() == cToken::EndLine);
            }
            else
            {
                m_bShallBeDeactivated =
                    (token.GetType() == cToken::StarSlash || token.GetType() == cToken::SlashStarSlash);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
bool cCommentAnalyser::IsActive()
{
    return m_bIsActive;
}

////////////////////////////////////////////////////////////////////////////////
