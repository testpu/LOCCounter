#ifndef __C_UTILS_H_
#define __C_UTILS_H_

#include <string>

//////////////////////////////////////////////////////////////////////////
class cUtils
{
public:
    static bool CreateFile(const std::string& i_sFilePath);
    static void CreateDirectory(const std::string& i_sDirectoryPath);
    static void DeleteDirectory(const std::string& i_sDirectoryPath);
    static const std::string& GetTestDirectoryPath();
};
//////////////////////////////////////////////////////////////////////////

#endif // __C_UTILS_H_