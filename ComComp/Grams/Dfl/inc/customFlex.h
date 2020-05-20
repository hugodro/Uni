#ifndef _CUSTOMFLEXER_H_
#define _CUSTOMFLEXER_H_
/**************************************************
* File: customFlex.h.
* Desc: Definition of the CSharp version of a FlexLexer.
* Module: AkraLog : Compiler.
* Rev: 2001/04/23 : REV 0 : Hugo DesRosiers : Creation.
* $Log$
**************************************************/

#include <FlexLexer.h>


class SharpFlex : public yyFlexLexer {
  public:
    SharpFlex(istream *inStream);
#if defined(_WIN32)
    virtual void LexerOutput(const char* buf, int size);
#endif
    virtual int yylex();
    virtual int getLineNbr();
    virtual int getInput();
    virtual void doUnput(char aChar);
};

#endif          /* _CUSTOMFLEXER_H_ */
