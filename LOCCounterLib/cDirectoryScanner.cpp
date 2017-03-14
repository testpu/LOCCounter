#include "cDirectoryScanner.h"
#include <boost/filesystem/operations.hpp>

//////////////////////////////////////////////////////////////////////////
cDirectoryScanner::cDirectoryScanner(
    const std::string& i_sDirectoryPath, bool i_bRecursive, cFileFilter* i_pFileFilter)
    : m_sDirectoryPath(i_sDirectoryPath)
    , m_bRecursive(i_bRecursive)
    , m_pFileFilter(i_pFileFilter)
{
    if (m_pFileFilter == NULL)
    {
        std::invalid_argument("NULL pointer to file filter has been passed");
    }
}

//////////////////////////////////////////////////////////////////////////
cDirectoryScanner::~cDirectoryScanner()
{
}

//////////////////////////////////////////////////////////////////////////
bool cDirectoryScanner::Scan()
{
    m_sFilePaths.clear();
    bool bOk = true;

    //try
    //{
    const boost::filesystem::path dirPath(m_sDirectoryPath);
    scanImpl(dirPath);
    //}
    //catch (const boost::filesystem::filesystem_error&)
    //{
    //r.what()
    //  bOk = false;
    //}
    return bOk;
}

//////////////////////////////////////////////////////////////////////////
void cDirectoryScanner::scanImpl(const boost::filesystem::path& i_rDirectoryPath)
{
    namespace fs = boost::filesystem;

    //default construction yields past-the-end
    fs::directory_iterator itEnd;

    for (fs::directory_iterator it(i_rDirectoryPath); it != itEnd; ++it)
    {
        const std::string strFilePath = it->path().generic_string();
        if (m_pFileFilter->IsFileAccepted(strFilePath))
        {
            m_sFilePaths.insert(strFilePath);
        }

        if (m_bRecursive && fs::is_directory(*it))
        {
            scanImpl(*it);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
cDirectoryScanner::cConstIterator cDirectoryScanner::GetProcessedFileNamesBeginIt() const
{
    return m_sFilePaths.begin();
}

//////////////////////////////////////////////////////////////////////////
cDirectoryScanner::cConstIterator cDirectoryScanner::GetProcessedFileNamesEndIt() const
{
    return m_sFilePaths.end();
}

//////////////////////////////////////////////////////////////////////////
