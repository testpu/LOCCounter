#include "cUtils.h"
#include <boost/filesystem/operations.hpp>
#include <fstream>

//////////////////////////////////////////////////////////////////////////
bool cUtils::CreateFile(const std::string& i_sFilePath)
{
    bool bFileExists = boost::filesystem::exists(i_sFilePath);
    if (!bFileExists)
    {
        std::ofstream file(i_sFilePath.c_str());
        if (file.is_open())
        {
            bFileExists = true;
            file.close();
        }
    }
    return bFileExists;
}

//////////////////////////////////////////////////////////////////////////
void cUtils::CreateDirectory(const std::string& i_sDirectoryPath)
{
    DeleteDirectory(i_sDirectoryPath);
    boost::filesystem::create_directory(i_sDirectoryPath);
}

//////////////////////////////////////////////////////////////////////////
void cUtils::DeleteDirectory(const std::string& i_sDirectoryPath)
{
    if (boost::filesystem::exists(i_sDirectoryPath))
    {
        boost::filesystem::remove_all(i_sDirectoryPath);
    }
}

//////////////////////////////////////////////////////////////////////////
const std::string& cUtils::GetTestDirectoryPath()
{
    static std::string sPath = "test_files";
    return sPath;
}

//////////////////////////////////////////////////////////////////////////
