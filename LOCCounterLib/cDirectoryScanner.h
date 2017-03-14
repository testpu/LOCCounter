#ifndef __C_DIRECTORY_SCANNER_H_
#define __C_DIRECTORY_SCANNER_H_

#include "cFileFilter.h"
#include <set>
#include <boost/filesystem/path.hpp>


//////////////////////////////////////////////////////////////////////////
class cDirectoryScanner
{
public:
    typedef std::set<std::string>::const_iterator cConstIterator;

    cDirectoryScanner(
        const std::string& i_sDirectoryPath, bool i_bRecursive, cFileFilter* i_pFileFilter);
    ~cDirectoryScanner();

    bool Scan();

    cConstIterator GetProcessedFileNamesBeginIt() const;
    cConstIterator GetProcessedFileNamesEndIt() const;
private:
    void scanImpl(const boost::filesystem::path& i_rDirectoryPath);

    std::string m_sDirectoryPath;
    bool m_bRecursive;
    cFileFilter* m_pFileFilter;
    std::set<std::string> m_sFilePaths;
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_DIRECTORY_SCANNER_H_