/*
 *
 * ©K. D. Hedger. 2015-2026 keithdhedger@gmail.com

 * This file (globals.h) is part of AspellGUI.

 * AspellGUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * AspellGUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with AspellGUI.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GLOBALS_
#define _GLOBALS_

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <aspell.h>

#include <QtWidgets>

#include "config.h"

#include "credits.h"
#include "guis.h"
#include "spellcheck.h"
#include "QT_AboutBox.h"

extern QPlainTextEdit		*bufferBox;
extern QMainWindow			*window;
extern QLabel				*badWordLabel;
extern QDialog				*spellCheckWord;
extern QComboBox				*wordListDropbox;
extern QComboBox				*langCode;

extern QString				badWord;
extern QString				goodWord;
extern QString				realDataDir;
extern QRect					checkWordGeom;

extern AspellConfig			*aspellConfig;
extern AspellSpeller			*spellChecker;
extern AspellCanHaveError	*possible_err;

extern int					numWords;
extern bool					blockFlag;
#endif
