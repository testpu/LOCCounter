#ifndef __C_LOC_COUNTER_H_
#define __C_LOC_COUNTER_H_

#include <boost/noncopyable.hpp>
#include <list>
#include <boost/scoped_ptr.hpp>
#include "cFileFilter.h"

class cFileNameCollection;
//////////////////////////////////////////////////////////////////////////
/**
* @class cLOCCounter
* @respons Facade for LOC counting subsystem
* @collab None
*/

class cLOCCounter : private boost::noncopyable
{
public:
    typedef std::list<std::pair<std::string, int> >::const_iterator cConstIterator;

    cLOCCounter();
    ~cLOCCounter();

    void AddDirectory(
        const std::string& i_sDirectoryPath, bool i_bRecursive, cFileFilter* i_pFileFilter);
    void AddFile(const std::string& i_sFilePath);

    void RunLOCsCounting();
    int GetTotalLOCsCount() const;

    cConstIterator GetProcessedFileLOCsBeginIt() const;
    cConstIterator GetProcessedFileLOCsEndIt() const;
private:
    std::list<std::pair<std::string, int> > m_fileLOCs;
    int m_nTotalLOCsCount;
    boost::scoped_ptr<cFileNameCollection> m_fileNameCollection;
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_LOC_COUNTER_H_