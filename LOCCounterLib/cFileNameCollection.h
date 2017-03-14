#ifndef __C_FILE_NAME_COLLECTION_H_
#define __C_FILE_NAME_COLLECTION_H_

#include "cFileFilter.h"
#include <set>

//////////////////////////////////////////////////////////////////////////
class cFileNameCollection
{
public:
    typedef std::set<std::string>::const_iterator cConstIterator;

    cFileNameCollection();
    ~cFileNameCollection();

    void AddDirectory(
        const std::string& i_sDirectoryPath, bool i_bRecursive, cFileFilter* i_pFileFilter);
    void AddFile(const std::string& i_sFilePath);

    cConstIterator GetProcessedFileNamesBeginIt() const;
    cConstIterator GetProcessedFileNamesEndIt() const;
private:
    friend class cFileNameCollectionTest;

    std::set<std::string> m_sFilePaths;
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_FILE_NAME_COLLECTION_H_
