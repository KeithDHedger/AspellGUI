/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:18:19 GMT 2015 kdhedger68713@gmail.com

 * This file (guis.h) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
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