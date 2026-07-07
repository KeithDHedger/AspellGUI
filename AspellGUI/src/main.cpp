/*
 *
 * ©K. D. Hedger. 2015-2026 keithdhedger@gmail.com

 * This file (main.cpp) is part of AspellGUI.

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

int main(int argc,char **argv)
{
	QApplication			app(argc,argv);
	QSettings			prefs("KDHedger",PACKAGE_NAME);

	realDataDir=QString("%1%2").arg(getenv("APPDIR")).arg(DATADIR);

	QIcon::setThemeSearchPaths(QStringList()<<QString("%1/usr/share/icons").arg(getenv("APPDIR"))<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME")) <<QString("%1/icons").arg(realDataDir) );
	QIcon::setFallbackSearchPaths(QStringList()<<QString("%1/usr/share/icons").arg(getenv("APPDIR"))<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME"))  <<QString("%1/icons").arg(realDataDir));
	QIcon::setFallbackThemeName("aspellqticons");

	app.setApplicationName(PACKAGE_NAME);
	app.setApplicationVersion(PACKAGE_VERSION);

	buildMainGuiQt();

	if(argc>1)
		{
			QFile	file(argv[argc-1]);
			if(file.open(QIODevice::ReadOnly | QIODevice::Text))
				{
					QTextStream in(&file);
					bufferBox->setPlainText(in.readAll());
					file.close();
				}
		}

	window->restoreGeometry(prefs.value("geometry").toByteArray());

	window->show();
	app.exec();

	prefs.setValue("geometry",window->saveGeometry());

	delete window;
	delete globalChecker;
}