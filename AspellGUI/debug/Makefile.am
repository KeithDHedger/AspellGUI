

include ../flagsandlibs
include ../sources

aspellguidebug_SOURCES = $(COMMONSRC)

aspellguidebug_CFLAGS = -ggdb -O0 -export-dynamic
aspellguidebug_CXXFLAGS = -ggdb -O0 -export-dynamic

bin_PROGRAMS = aspellguidebug

install-exec-local:
	cd $(DESTDIR)$(bindir) && \
	rm aspellguidebug

