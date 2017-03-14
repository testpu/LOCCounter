#include "StringAnalyser.h"
#include "CommentAnalyser.h"

////////////////////////////////////////////////////////////////////////////////
cStringAnalyser::cStringAnalyser(cCommentAnalyser* commentAnalyser)
    : m_bIsActive(false)
    , m_commentAnalyser(commentAnalyser)
    , m_bShallBeDeactivated(false)
{
}

////////////////////////////////////////////////////////////////////////////////
cStringAnalyser::~cStringAnalyser()
{
}

////////////////////////////////////////////////////////////////////////////////
void cStringAnalyser::Analyse(const cToken& token)
{
    if (m_bShallBeDeactivated)
    {
        m_bShallBeDeactivated = false;
        m_bIsActive = false;
    }

    if (!m_commentAnalyser->IsActive())
    {
        if (token.GetType() == cToken::DoubleApostroph)
        {
            if (!IsActive())
            {
                m_bIsActive = true;
            }
            else
            {
                m_bShallBeDeactivated = true;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
bool cStringAnalyser::IsActive()
{
    return m_bIsActive;
}

////////////////////////////////////////////////////////////////////////////////

