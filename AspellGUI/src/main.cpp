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
	QSettings			prefs("KDHedger","AspellGUI");

	realDataDir=QString("%1%2").arg(getenv("APPDIR")).arg(DATADIR);

	QIcon::setThemeSearchPaths(QStringList()<<QString("%1/usr/share/icons").arg(getenv("APPDIR"))<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME")) <<QString("%1/icons").arg(realDataDir) );
	QIcon::setFallbackSearchPaths(QStringList()<<QString("%1/usr/share/icons").arg(getenv("APPDIR"))<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME"))  <<QString("%1/icons").arg(realDataDir));
	QIcon::setFallbackThemeName("aspellqticons");

	app.setApplicationName(PACKAGE_NAME);

	aspellConfig=new_aspell_config();

	QDir dir("/usr/lib");
	QStringList folders=dir.entryList(QStringList()<<"aspell*",QDir::Dirs|QDir::NoDotAndDotDot);
	if(folders.size()>0)
		aspell_config_replace(aspellConfig,"dict-dir",qPrintable("/usr/lib/"+folders.at(0)));

	possible_err=new_aspell_speller(aspellConfig);
	if(aspell_error_number(possible_err)!= 0)
		{
			puts(aspell_error_message(possible_err));
			puts("Trying internal dicts ...");
			qDebug()<<qPrintable(QString("%1/lib/aspell-0.60").arg(getenv("APPDIR")));
			aspell_config_replace(aspellConfig,"dict-dir",qPrintable(QString("%1/lib/aspell-0.60").arg(getenv("APPDIR"))));
			possible_err=new_aspell_speller(aspellConfig);
		}

	if(aspell_error_number(possible_err)!= 0)
		{
			QMessageBox::critical(nullptr,"Critical Error ...",aspell_error_message(possible_err));
			puts(aspell_error_message(possible_err));
			exit(1);
		}
	else
		spellChecker=to_aspell_speller(possible_err);

	buildMainGuiQt();
	buildWordCheckQt(1);

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
	spellCheckWord->restoreGeometry(prefs.value("wordgeom").toByteArray());
	checkWordGeom=spellCheckWord->geometry();

	window->show();
	app.exec();

	prefs.setValue("geometry",window->saveGeometry());
	prefs.setValue("wordgeom",spellCheckWord->saveGeometry());
	delete window;
	delete_aspell_speller(spellChecker);
	delete_aspell_config(aspellConfig);
}