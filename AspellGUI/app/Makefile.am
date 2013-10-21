include ../flagsandlibs
include ../sources

aspellgui_SOURCES = $(COMMONSRC)

aspellgui_CFLAGS = -O3 -export-dynamic
aspellgui_CXXFLAGS = -O3 -export-dynamic

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

docfilesdir = $(pkgdatadir)/docs
docfiles_DATA = ../resources/docs/*

bin_PROGRAMS = aspellgui

install-exec-hook:
	cp ../resources/pixmaps/AspellGUI.desktop $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	cp ../resources/pixmaps/AspellGUI.png $(DESTDIR)${prefix}/share/pixmaps
	echo Icon=AspellGUI.png >> $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	echo Exec=aspellgui >> $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop


uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	rm -f $(DESTDIR)${prefix}/share/pixmaps/AspellGUI.png
	rm -fr $(pkgdatadir)

