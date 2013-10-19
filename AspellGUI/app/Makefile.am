
include ../flagsandlibs
include ../sources

aspellgui_SOURCES = $(COMMONSRC)

aspellgui_CFLAGS = -O3 -export-dynamic
aspellgui_CXXFLAGS = -O3 -export-dynamic

pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ../resources/pixmaps/*

scriptfilesdir = $(pkgdatadir)/scripts
scriptfiles_SCRIPTS = ../resources/scripts/README

bin_PROGRAMS = aspellgui

man1_MANS = ../resources/man/aspellgui.1

install-exec-hook:
	cp ../resources/pixmaps/AspellGUI.desktop /usr/share/applications/AspellGUI.desktop
	echo Icon=${prefix}/share/AspellGUI/pixmaps/AspellGUI.png >> /usr/share/applications/AspellGUI.desktop
	echo Exec=${prefix}/bin/aspellgui >> /usr/share/applications/AspellGUI.desktop
#	update-menus

uninstall-hook:
	rm -f /usr/share/applications/AspellGUI.desktop
#	update-menus
	rm -fr $(pkgdatadir)

