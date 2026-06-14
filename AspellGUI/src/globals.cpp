/*
 *
 * ©K. D. Hedger. Wed 2015-2026 keithdhedger@gmail.com

 * This file (globals.cpp) is part of AspellGUI.

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

#include "globals.h"

QPlainTextEdit		*bufferBox=NULL;
QMainWindow			*window=NULL;
QLabel				*badWordLabel=NULL;
QDialog				*spellCheckWord=NULL;
QComboBox			*wordListDropbox=NULL;
QComboBox			*langCode=NULL;

//spellcheck
QString				badWord;
QString				goodWord;
QString				realDataDir;
QRect				checkWordGeom;

AspellConfig			*aspellConfig=NULL;
AspellSpeller		*spellChecker=NULL;
AspellCanHaveError	*possible_err=NULL;

int					numWords=0;
bool					blockFlag=false;

