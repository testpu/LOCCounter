#ifndef __C_COMMAND_LINE_PARSER_H_
#define __C_COMMAND_LINE_PARSER_H_

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <string>

class cLOCCounter;
//////////////////////////////////////////////////////////////////////////
class cCommandLineParser : private boost::noncopyable
{
public:
    typedef std::string tOutputFileName;
    typedef bool tOutputAppendFlag;
    static const std::string& GetCommandLineFormat();

    cCommandLineParser(int argc, char* argv[]);
    ~cCommandLineParser();

    cLOCCounter& GetLOCCounter();
    const std::pair<tOutputFileName, tOutputAppendFlag>& GetOutputFileData();
private:
    bool parseDirectoryCommand(int argc, char* argv[], int& io_argIndex);

    std::pair<tOutputFileName, tOutputAppendFlag> m_outputFileData;
    boost::scoped_ptr<cLOCCounter> m_spLOCCounter;
};

//////////////////////////////////////////////////////////////////////////

#endif // __C_COMMAND_LINE_PARSER_H_
