AUTOMAKE_OPTIONS = subdir-objects

include ../flagsandlibs
include ../sources

aspellgui_SOURCES = $(COMMONSRC)

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

docfilesdir = $(pkgdatadir)/docs
docfiles_DATA = ../resources/docs/*

bin_PROGRAMS = aspellgui

install-exec-hook:
	mkdir -vp $(DESTDIR)${prefix}/share/icons/hicolor/256x256/apps||true
	mkdir -vp $(DESTDIR)${prefix}/share/applications $(DESTDIR)${prefix}/share/pixmaps||true
	cp ../resources/pixmaps/AspellGUI.desktop $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	cp ../resources/pixmaps/AspellGUI.png $(DESTDIR)${prefix}/share/icons/hicolor/256x256/apps
	gtk-update-icon-cache --ignore-theme-index --force /usr/share/icons/hicolor

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	rm -f $(DESTDIR)${prefix}/share/icons/hicolor/256x256/apps/AspellGUI.png
	rm -fr $(pkgdatadir)

