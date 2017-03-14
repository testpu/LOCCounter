#ifndef __C_STRING_ANALYSER_H_
#define __C_STRING_ANALYSER_H_

#include "Token.h"

class cCommentAnalyser;

////////////////////////////////////////////////////////////////////////////////
class cStringAnalyser
{
public:
    cStringAnalyser(cCommentAnalyser* commentAnalyser);
    ~cStringAnalyser();

    void Analyse(const cToken& token);
    bool IsActive();
private:
    bool m_bIsActive;
    bool m_bShallBeDeactivated;
    cCommentAnalyser* m_commentAnalyser;
};

////////////////////////////////////////////////////////////////////////////////

#endif // __C_STRING_ANALYSER_H_