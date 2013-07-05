TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += root_model.h \
           common.h \
           library_appli_init.h \
           manager_repository.h \
           project.h \
           utilities.h

SOURCES += root_model.cpp \
           library_appli_init.cpp \
           manager_repository.cpp \
           project.cpp \
           utilities.cpp

TARGET = ar2gems_appli

INCLUDEPATH += $(QTDIR)/tools/designer/interfaces
contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/appli
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/appli
}
include( $$GSTLAPPLI_HOME/config.qmake )
exists( MMakefile ):include( MMakefile )
