#include "cCommonFileFilter.h"
#include "cFileNameFilter.h"

//////////////////////////////////////////////////////////////////////////
cCommonFileFilter::cCommonFileFilter()
{
    m_spIncludeFileNamesFilter.reset(new cFileNameFilter());
}

//////////////////////////////////////////////////////////////////////////
cCommonFileFilter::~cCommonFileFilter()
{
}

//////////////////////////////////////////////////////////////////////////
void cCommonFileFilter::AddPatternIncludingFiles(const std::string& i_sPattern)
{
    m_spIncludeFileNamesFilter->AddPattern(i_sPattern);
}

//////////////////////////////////////////////////////////////////////////
void cCommonFileFilter::AddPatternExcludingFiles(const std::string& i_sPattern)
{
    if (m_spExcludeFileNamesFilter.get() == NULL)
    {
        m_spExcludeFileNamesFilter.reset(new cFileNameFilter());
    }
    m_spExcludeFileNamesFilter->AddPattern(i_sPattern);
}

//////////////////////////////////////////////////////////////////////////
bool cCommonFileFilter::IsFileAccepted(const std::string& i_sFileName)
{
    bool bFileIncluded = m_spIncludeFileNamesFilter->IsFileNameAccepted(i_sFileName);

    bool bFileExcluded = false;
    if (m_spExcludeFileNamesFilter.get() != NULL)
    {
        bFileExcluded = m_spExcludeFileNamesFilter->IsFileNameAccepted(i_sFileName);
    }

    return bFileIncluded && !bFileExcluded;
}

//////////////////////////////////////////////////////////////////////////
