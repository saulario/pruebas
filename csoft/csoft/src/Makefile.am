bin_PROGRAMS = csoft
csoft_SOURCES = main.cpp \
		Csoft.cpp \
		mod1/Worker1.cpp \
		mod2/Worker2.cpp

AM_CPPFLAGS=-DDATADIR=\"$(datadir)\" -DSYSCONFDIR=\"$(sysconfdir)\" -DDBDIR=\"$(prefix)/db\" -DLOGDIR=\"$(prefix)/log\"

csoft_CXXFLAGS=--std=c++14 -Wpedantic -DBOOST_LOG_DYN_LINK
csoft_LDADD=-lboost_filesystem -lboost_log -lboost_log_setup -lboost_thread -lboost_system -lpthread
