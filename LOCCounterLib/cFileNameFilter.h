#ifndef __C_FILE_NAME_FILTER_H_
#define __C_FILE_NAME_FILTER_H_

#include <string>
#include <list>
#include <boost/regex.hpp>
#include <boost/filesystem/operations.hpp>

//////////////////////////////////////////////////////////////////////////
class cFileNameFilter
{
public:

    cFileNameFilter();
    ~cFileNameFilter();

    void AddPattern(const std::string& i_sPattern);
    bool IsFileNameAccepted(const std::string& i_sFileName) const;

private:
    friend class cFileNameFilterTest;
    typedef std::list<boost::regex>::const_iterator cConstIterator;

    bool isSpecialSymbol(char i_ch) const;

    std::list<boost::regex> m_sRegExpressions;
};
//////////////////////////////////////////////////////////////////////////


#endif // __C_FILE_NAME_FILTER_H_