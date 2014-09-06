/*
 *
 * K.D.Hedger 2013 <kdhedger68713@gmail.com>
 *
*/

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifndef _GUIS_
#define _GUIS_

void buildMainGuiQt(void);
void buildMainGuiGtk(void);
void buildWordCheckGtk(int documentCheck);
void buildWordCheckQt(int documentCheck);

#endif