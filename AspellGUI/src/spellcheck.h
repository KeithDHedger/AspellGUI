/*
 *
 * ©K. D. Hedger. Thu 26 Nov 14:21:30 GMT 2015 kdhedger68713@gmail.com

 * This file (spellcheck.h) is part of AspellGUI.

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

#include "config.h"

#ifndef _SPELLCHECK_
#define _SPELLCHECK_

void checkWord(Widget* widget,void* data);
void doChangeWord(Widget* widget,void* data);
void doAddIgnoreWord(Widget* widget,gpointer data);
void doSpellCheckDoc(Widget* widget,void* data);
void doCancelCheck(Widget* widget,gpointer data);

#endif
