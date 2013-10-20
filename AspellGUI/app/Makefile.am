include ../flagsandlibs
include ../sources

aspellgui_SOURCES = $(COMMONSRC)

aspellgui_CFLAGS = -O3 -export-dynamic
aspellgui_CXXFLAGS = -O3 -export-dynamic

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

bin_PROGRAMS = aspellgui

install-exec-hook:
	cp ../resources/pixmaps/AspellGUI.desktop $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	cp ../resources/pixmaps/AspellGUI.png $(DESTDIR)${prefix}/share/pixmaps
	echo Icon=${prefix}/share/AspellGUI/pixmaps/AspellGUI.png >> $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	echo Exec=${prefix}/bin/aspellgui >> $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop


uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/AspellGUI.desktop
	rm -fr $(pkgdatadir)

