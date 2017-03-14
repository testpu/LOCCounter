#include "cFileNameCollection.h"
#include "cDirectoryScanner.h"

//////////////////////////////////////////////////////////////////////////
cFileNameCollection::cFileNameCollection()
{
}

//////////////////////////////////////////////////////////////////////////
cFileNameCollection::~cFileNameCollection()
{
}

//////////////////////////////////////////////////////////////////////////
void cFileNameCollection::AddDirectory(
    const std::string& i_sDirectoryPath, bool i_bRecursive, cFileFilter* i_pFileFilter)
{
    cDirectoryScanner scanner(i_sDirectoryPath, i_bRecursive, i_pFileFilter);
    scanner.Scan();
    cDirectoryScanner::cConstIterator itEnd = scanner.GetProcessedFileNamesEndIt();
    for (cDirectoryScanner::cConstIterator it = scanner.GetProcessedFileNamesBeginIt(); it != itEnd; ++it)
    {
        m_sFilePaths.insert(*it);
    }
}

//////////////////////////////////////////////////////////////////////////
void cFileNameCollection::AddFile(const std::string& i_sFilePath)
{
    boost::filesystem::path filePath(i_sFilePath);
    m_sFilePaths.insert(filePath.generic_string());
}

//////////////////////////////////////////////////////////////////////////
cFileNameCollection::cConstIterator cFileNameCollection::GetProcessedFileNamesBeginIt() const
{
    return m_sFilePaths.begin();
}

//////////////////////////////////////////////////////////////////////////
cFileNameCollection::cConstIterator cFileNameCollection::GetProcessedFileNamesEndIt() const
{
    return m_sFilePaths.end();
}

//////////////////////////////////////////////////////////////////////////
