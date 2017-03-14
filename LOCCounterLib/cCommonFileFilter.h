#ifndef __C_COMMON_FILE_FILTER_H_
#define __C_COMMON_FILE_FILTER_H_

#include <boost/scoped_ptr.hpp>
#include "cFileFilter.h"

class cFileNameFilter;
//////////////////////////////////////////////////////////////////////////
class cCommonFileFilter : public cFileFilter
{
public:
    cCommonFileFilter();
    ~cCommonFileFilter();

    void AddPatternIncludingFiles(const std::string& i_sPattern);
    void AddPatternExcludingFiles(const std::string& i_sPattern);

    bool IsFileAccepted(const std::string& i_sFileName);
private:
    boost::scoped_ptr<cFileNameFilter> m_spIncludeFileNamesFilter;
    boost::scoped_ptr<cFileNameFilter> m_spExcludeFileNamesFilter;
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_COMMON_FILE_FILTER_H_
