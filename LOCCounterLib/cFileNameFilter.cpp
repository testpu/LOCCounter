#include "cFileNameFilter.h"

//////////////////////////////////////////////////////////////////////////
cFileNameFilter::cFileNameFilter()
{
}

//////////////////////////////////////////////////////////////////////////
cFileNameFilter::~cFileNameFilter()
{
}

//////////////////////////////////////////////////////////////////////////
void cFileNameFilter::AddPattern(const std::string& i_sPattern)
{
    if (i_sPattern.empty())
    {
        return;
    }

    std::string sExpression;
    bool bGroupIsStarted = false;
    bool bNeedForGroupMultiplication = false;
    for (std::string::const_iterator it = i_sPattern.begin(); it != i_sPattern.end(); ++it)
    {
        bool bSlashIsNeeded = false;
        char chSymbol = *it;
        switch (chSymbol)
        {
        case '*':
            if (bGroupIsStarted)
            {
                sExpression += "){1}";
                bGroupIsStarted = false;
            }
            sExpression += ".*";
            bNeedForGroupMultiplication = true;
            break;
        case '?':
            sExpression += ".{1}";
            break;
        default:
            if (!bGroupIsStarted)
            {
                sExpression += '(';
                bGroupIsStarted = true;
            }

            if (isSpecialSymbol(chSymbol))
            {
                sExpression += '\\';
            }
            sExpression += chSymbol;
            break;
        }
    }

    if (bGroupIsStarted)
    {
        sExpression += ")";
        bGroupIsStarted = false;

        if (bNeedForGroupMultiplication)
        {
            sExpression += "+";
        }
        else
        {
            sExpression += "{1}";
        }
    }

    if (sExpression.empty())
    {
        sExpression = ".+";
    }

    m_sRegExpressions.push_back(boost::regex(sExpression));
}

//////////////////////////////////////////////////////////////////////////
bool cFileNameFilter::IsFileNameAccepted(const std::string& i_sFileName) const
{
    bool bAccepted = false;
    boost::filesystem::path filePath(i_sFileName);
    std::string sFileName(filePath.leaf().string());
    if (m_sRegExpressions.empty())
    {
        bAccepted = true;
    }
    else
    {
        cConstIterator itEnd = m_sRegExpressions.end();
        for (cConstIterator it = m_sRegExpressions.begin(); it != itEnd; ++it)
        {
            if (boost::regex_match(sFileName, *it))
            {
                bAccepted = true;
                break;
            }
        }
    }
    return bAccepted;
}

//////////////////////////////////////////////////////////////////////////
bool cFileNameFilter::isSpecialSymbol(char i_ch) const
{
    static std::string sSpecialSymbols("{}()[]+|^$,:;-.");
    return (sSpecialSymbols.find(i_ch) != -1);
}

//////////////////////////////////////////////////////////////////////////