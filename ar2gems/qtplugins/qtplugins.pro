TEMPLATE = lib
DEPENDPATH += . \
    icons
INCLUDEPATH += .

HEADERS += region_proxy_model.h \
           property_proxy_model.h \
           grid_proxy_model.h \
           common.h \
           ellipsoid_input.h \
           filechooser.h \
           gstl_table.h \
           gstl_widgets_plugin.h \
           kriging_type_selector.h \
           kriging_type_selector_base.h \
           neighborhood_filter_input.h \
           non_param_cdf_input.h \
           selectors.h \
           group_selectors.h \
           variogram_input.h \
           icons/selectors_icons.h \
           categorical_selectors.h \
           categorical_definition_proxy_model.h \
           color_delegate.h \
           distribution_parameter_widget.h \
           distribution_proxy_model.h \
           distribution_selectors.h \
           project_proxy_model.h \
           region_weight_proxy_model.h \
           weight_property_proxy_model.h \
           weight_property_selector.h    \
           grid_filter_delegate.h \
           grid_filter_model.h \
           grid_filter_model_item.h \
           grid_filter_named_interface.h \
           grid_filter_widgets.h \
           library_qtplugins_init.h \
           rename_dialog.h

SOURCES += region_proxy_model.cpp \
           property_proxy_model.cpp \
           grid_proxy_model.cpp \
           ellipsoid_input.cpp \
           filechooser.cpp \
           gstl_table.cpp \
           gstl_widgets_plugin.cpp \
           kriging_type_selector.cpp \
           kriging_type_selector_base.cpp \
           neighborhood_filter_input.cpp \
           non_param_cdf_input.cpp \
           selectors.cpp \
           group_selectors.cpp \
           variogram_input.cpp \
           categorical_selectors.cpp \
           categorical_definition_proxy_model.cpp \
           color_delegate.cpp \
           distribution_parameter_widget.cpp \
           distribution_proxy_model.cpp \
           distribution_selectors.cpp \
           project_proxy_model.cpp \
           region_weight_proxy_model.cpp \
           weight_property_proxy_model.cpp \
           weight_property_selector.cpp  \
           grid_filter_delegate.cpp \
           grid_filter_model.cpp \
           grid_filter_model_item.cpp \
           grid_filter_named_interface.cpp \
           grid_filter_widgets.cpp \
           library_qtplugins_init.cpp \
           rename_dialog.cpp

FORMS += order_properties_dialog.ui \
         variogram_input_base.ui \
         variogram_structure_base.ui

RESOURCES += icons.qrc

TARGET = ar2gems_widgets

QT += xml
CONFIG += uitools
CONFIG += plugin \
    designer \
    debug_and_release

LIBS += -lar2gems_math
INCLUDEPATH += $(QTDIR)/tools/designer/interfaces
contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/extra/qtplugins
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/extra/qtplugins
}
include( $$GSTLAPPLI_HOME/config.qmake )
exists( MMakefile ):include( MMakefile )
