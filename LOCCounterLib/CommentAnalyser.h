#ifndef __COMMENT_ANALYSER_H_
#define __COMMENT_ANALYSER_H_

#include "StringAnalyser.h"

////////////////////////////////////////////////////////////////////////////////
class cCommentAnalyser
{
public:
    cCommentAnalyser();
    ~cCommentAnalyser();

    void Analyse(const cToken& token);
    bool IsActive();

private:
    bool m_bIsActive;
    bool m_bShallBeDeactivated;
    bool m_bIsOneLineComment;
    cStringAnalyser m_stringAnalyser;
};

////////////////////////////////////////////////////////////////////////////////

#endif // __COMMENT_ANALYSER_H_