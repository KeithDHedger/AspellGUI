/******************************************************
*
*     ©keithhedger Tue 16 Jul 20:46:19 BST 2013
*     kdhedger68713@gmail.com
*
*     spellcheck.h
* 
******************************************************/

#include "config.h"

#ifndef _SPELLCHECK_
#define _SPELLCHECK_

void checkWord(Widget* widget,void* data);
void doChangeWord(Widget* widget,void* data);
void doAddIgnoreWord(Widget* widget,gpointer data);
void doSpellCheckDoc(Widget* widget,void* data);
void doCancelCheck(Widget* widget,gpointer data);

#endif
