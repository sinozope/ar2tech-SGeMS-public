TEMPLATE = lib
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += angle_convention.h \
           box.h \
           common.h \
           correlation_measure.h \
           correlation_measure_computer.h \
           direction_3d.h \
           discrete_function.h \
           gstlpoint.h \
           gstlvector.h \
           histogram.h \
           Interpolator_1d.h \
           Linear_interpolator_1d.h \
           qpplot.h \
           random_numbers.h \
           scatterplot.h \
           continuous_distribution.h \
           library_math_init.h \
           non_parametric_distribution.h \
           categorical_distribution.h

SOURCES += box.cpp \
           correlation_measure.cpp \
           correlation_measure_computer.cpp \
           direction_3d.cpp \
           discrete_function.cpp \
           gstlappli_math_init.cpp \
           histogram.cpp \
           Linear_interpolator_1d.cpp \
           qpplot.cpp \
           random_numbers.cpp \
           scatterplot.cpp \
           continuous_distribution.cpp \
           library_math_init.cpp \
           non_parametric_distribution.cpp \
           categorical_distribution.cpp

TARGET=ar2gems_math

LIBS += -lar2gems_utils
CONFIG      += plugin
INCLUDEPATH += $(QTDIR)/tools/designer/interfaces


contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/math
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/math
}


include( $$GSTLAPPLI_HOME/config.qmake )

exists( MMakefile ) {
   include( MMakefile )
}
