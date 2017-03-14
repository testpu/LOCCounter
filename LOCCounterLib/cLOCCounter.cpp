#include "cLOCCounter.h"
#include "cFileNameCollection.h"
#include <fstream>
#include "SimpleParser.h"

//////////////////////////////////////////////////////////////////////////
cLOCCounter::cLOCCounter()
    : m_nTotalLOCsCount(0)
{
    m_fileNameCollection.reset(new cFileNameCollection());
}

//////////////////////////////////////////////////////////////////////////
cLOCCounter::~cLOCCounter()
{
}

//////////////////////////////////////////////////////////////////////////
void cLOCCounter::AddDirectory(
    const std::string& i_sDirectoryPath, bool i_bRecursive, cFileFilter* i_pFileFilter)
{
    m_fileNameCollection->AddDirectory(i_sDirectoryPath, i_bRecursive, i_pFileFilter);
}

//////////////////////////////////////////////////////////////////////////
void cLOCCounter::AddFile(const std::string& i_sFilePath)
{
    m_fileNameCollection->AddFile(i_sFilePath);
}

//////////////////////////////////////////////////////////////////////////
void cLOCCounter::RunLOCsCounting()
{
    m_nTotalLOCsCount = 0;
    m_fileLOCs.clear();

    cFileNameCollection::cConstIterator itEnd = m_fileNameCollection->GetProcessedFileNamesEndIt();
    for (cFileNameCollection::cConstIterator it = m_fileNameCollection->GetProcessedFileNamesBeginIt(); it != itEnd; ++it)
    {
        std::ifstream file(it->c_str());
        if (file.is_open())
        {
            int nCodeLines = cSimpleParser::GetInstance().ComputeCodeLines(file);
            m_fileLOCs.push_back(std::make_pair(*it, nCodeLines));
            m_nTotalLOCsCount += nCodeLines;
        }
        else
        {
            throw std::invalid_argument("Cannot open input file");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
int cLOCCounter::GetTotalLOCsCount() const
{
    return m_nTotalLOCsCount;
}

//////////////////////////////////////////////////////////////////////////
cLOCCounter::cConstIterator cLOCCounter::GetProcessedFileLOCsBeginIt() const
{
    return m_fileLOCs.begin();
}

//////////////////////////////////////////////////////////////////////////
cLOCCounter::cConstIterator cLOCCounter::GetProcessedFileLOCsEndIt() const
{
    return m_fileLOCs.end();
}

//////////////////////////////////////////////////////////////////////////
