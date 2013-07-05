TEMPLATE = lib

debug:DEFINES += _DEBUG
DEPENDPATH += . \
    appli \
    debug \
    vtk_prop \
    models \
    viewer \
    QWidget_value_accessors \
    release \
    utils \
    variogram2
INCLUDEPATH += . \
    vtk_prop \
    utils \
    models \
    viewer \
    vtk_prop \
    variogram2

HEADERS += library_gui_init.h    \
           appli/about_sgems.h    \
           appli/cli_commands_panel.h    \
           appli/scatterplot_control_panel.h    \
           appli/scatterplot_gui.h    \
           appli/snapshot_dialog.h    \
           appli/splash_screen.h    \
           appli/data_analysis_gui.h    \
           appli/visu_actions.h    \
           appli/histogram_control_panel.h    \
           appli/histogram_gui.h    \
           appli/new_cartesian_grid_dialog.h    \
           appli/qpplot_control_panel.h    \
           appli/qpplot_gui.h    \
           appli/qt_algo_control_panel.h    \
           appli/qt_grid_summary.h    \
           appli/qt_sp_application.h    \
           utils/categorical_definition_dialog.h    \
           utils/categorical_property_dialog.h    \
           utils/colormap.h    \
           utils/copy_property_dialog.h    \
           utils/downscale_grid_dialog.h    \
           utils/new_distribution_dialog.h    \
           utils/new_region_from_grid_filter_dialog.h \
           utils/save_grid_dialog.h    \
           utils/upscale_property_dialog.h    \
           utils/data_analysis_save_dialog.h    \
           utils/visualization_profile.h    \
           utils/qdirdialog.h    \
           utils/delete_properties_dialog.h    \
           utils/delete_regions_dialog.h    \
           utils/colors.h    \
           utils/colorscale.h    \
           utils/group_property_dialog.h    \
           utils/script_editor.h    \
           utils/script_syntax_highlighter.h    \
           utils/std_output_redirect.h    \
           utils/manager_dialog.h    \
           utils/merge_regions_dialog.h    \
           utils/multichoice_dialog.h    \
           utils/gstl_slider.h    \
           utils/gstl_widget_factory.h    \
           utils/indicator_property_dialog.h    \
           utils/new_mgrid_from_cgrid_dialog.h    \
           utils/new_region_from_property_dialog.h    \
           utils/qtbased_scribes.h    \
           utils/qtprogress_notifier.h    \
           utils/qwidget_value_accessor.h    \
           utils/qwidget_value_collector.h    \
           utils/set_not_informed_dialog.h \
           models/categorical_table_model.h    \
           models/gstl_item.h    \
           models/gstl_item_action.h    \
           models/gstl_item_selection_model.h    \
           models/project_ItemModel.h    \
           models/project_selection_model.h    \
           models/visualization_tree_view.h    \
           models/context_menu_interface.h    \
           QWidget_value_accessors/qbuttongroup_accessor.h    \
           QWidget_value_accessors/qcheckbox_accessor.h    \
           QWidget_value_accessors/qcombobox_accessor.h    \
           QWidget_value_accessors/default_accessor.h    \
           QWidget_value_accessors/qlineedit_accessor.h    \
           QWidget_value_accessors/qradiobutton_accessor.h    \
           QWidget_value_accessors/qspin_box_accessor.h    \
           QWidget_value_accessors/qtable_accessor.h    \
           variogram2/pset_params.h    \
           variogram2/rgrid_params.h    \
           variogram2/plot_settings_dialog.h    \
           variogram2/print_plots_dialog.h    \
           variogram2/variog_multiplot.h    \
           variogram2/variog_plot.h    \
           variogram2/variogram_controls.h    \
           variogram2/variogram_controls_base.h    \
           variogram2/variogram_modeler_gui.h    \
           variogram2/variogram_modeling_screen.h    \
           variogram2/first_scr.h    \
           viewer/qvtkGsTLViewer.h    \
           viewer/region_param_viewer.h    \
           viewer/grid_param_viewer.h    \
           viewer/group_param_viewer.h    \
           viewer/visualization_parameters.h    \
           viewer/object_property_viewer.h    \
           viewer/colormap_controller.h    \
           viewer/colormap_widget.h    \
           viewer/vtk_project_view_gui.h    \
           viewer/vtk_prop_map.h    \
           viewer/grid_section_view.h    \
           viewer/property_filter_view.h    \
           viewer/property_param_viewer.h    \
           viewer/property_stats_view.h    \
           vtk_prop/vtk_common.h    \
           vtk_prop/colormap_actor.h    \
           vtk_prop/vtk_prop_cgrid.h    \
           vtk_prop/vtk_prop_gstl.h    \
           vtk_prop/vtk_prop_log.h    \
           vtk_prop/vtk_prop_mgrid.h    \
           vtk_prop/vtk_prop_pointset.h    \
           vtk_prop/vtk_prop_structured_grid.h

FORMS += viewer/Project_view_form.ui \
         appli/controls_widget.ui \
         appli/data_analysis_gui_base.ui \
         appli/histogram_control_panel_base.ui \
         appli/MainWindow.ui \
         appli/new_cartesian_grid_dialog_base.ui \
         appli/qpplot_control_panel_base.ui \
         appli/qt_algo_control_panel_base.ui \
         appli/scatterplot_control_panel_base.ui \
         appli/snapshot_dialog_base.ui \
         utils/delete_properties_dialog_base.ui \
         utils/delete_regions_dialog_base.ui \
         utils/multichoice_dialog_base.ui \
         utils/create_distribution_dialog.ui \
         variogram2/first_scr_base.ui \
         variogram2/point_set_base.ui \
         variogram2/rgrid_base.ui \
         variogram2/variogram_modeler_gui_base.ui \
         variogram2/variogram_plot_settings_dialog.ui \
         variogram2/variogram_print_plots_dialog.ui \
         variogram2/variogram_structure_controls_base.ui

SOURCES += library_gui_init.cpp    \
           appli/about_sgems.cpp \
           appli/cli_commands_panel.cpp    \
           appli/scatterplot_control_panel.cpp    \
           appli/scatterplot_gui.cpp    \
           appli/snapshot_dialog.cpp    \
           appli/splash_screen.cpp    \
           appli/data_analysis_gui.cpp    \
           appli/visu_actions.cpp    \
           appli/histogram_control_panel.cpp    \
           appli/histogram_gui.cpp    \
           appli/new_cartesian_grid_dialog.cpp    \
           appli/qpplot_control_panel.cpp    \
           appli/qpplot_gui.cpp    \
           appli/qt_algo_control_panel.cpp    \
           appli/qt_grid_summary.cpp    \
           appli/qt_sp_application.cpp    \
           utils/categorical_definition_dialog.cpp    \
           utils/categorical_property_dialog.cpp    \
           utils/colormap.cpp    \
           utils/copy_property_dialog.cpp    \
           utils/downscale_grid_dialog.cpp    \
           utils/new_distribution_dialog.cpp    \
           utils/new_region_from_grid_filter_dialog.cpp \
           utils/save_grid_dialog.cpp    \
           utils/upscale_property_dialog.cpp    \
           utils/data_analysis_save_dialog.cpp    \
           utils/visualization_profile.cpp    \
           utils/qdirdialog.cpp    \
           utils/delete_properties_dialog.cpp    \
           utils/delete_regions_dialog.cpp    \
           utils/colors.cpp    \
           utils/colorscale.cpp    \
           utils/group_property_dialog.cpp    \
           utils/script_editor.cpp    \
           utils/script_syntax_highlighter.cpp    \
           utils/std_output_redirect.cpp    \
           utils/manager_dialog.cpp    \
           utils/merge_regions_dialog.cpp    \
           utils/multichoice_dialog.cpp    \
           utils/gstl_slider.cpp    \
           utils/gstl_widget_factory.cpp    \
           utils/indicator_property_dialog.cpp    \
           utils/new_mgrid_from_cgrid_dialog.cpp    \
           utils/new_region_from_property_dialog.cpp    \
           utils/qtbased_scribes.cpp    \
           utils/qtprogress_notifier.cpp    \
           utils/qwidget_value_accessor.cpp    \
           utils/qwidget_value_collector.cpp    \
           utils/set_not_informed_dialog.cpp \
           models/categorical_table_model.cpp    \
           models/gstl_item.cpp    \
           models/gstl_item_action.cpp    \
           models/gstl_item_selection_model.cpp    \
           models/project_ItemModel.cpp    \
           models/project_selection_model.cpp    \
           models/visualization_tree_view.cpp    \
           models/context_menu_interface.cpp    \
           QWidget_value_accessors/qbuttongroup_accessor.cpp    \
           QWidget_value_accessors/qcheckbox_accessor.cpp    \
           QWidget_value_accessors/qcombobox_accessor.cpp    \
           QWidget_value_accessors/default_accessor.cpp    \
           QWidget_value_accessors/qlineedit_accessor.cpp    \
           QWidget_value_accessors/qradiobutton_accessor.cpp    \
           QWidget_value_accessors/qspin_box_accessor.cpp    \
           QWidget_value_accessors/qtable_accessor.cpp    \
           variogram2/pset_params.cpp    \
           variogram2/rgrid_params.cpp    \
           variogram2/plot_settings_dialog.cpp    \
           variogram2/print_plots_dialog.cpp    \
           variogram2/variog_multiplot.cpp    \
           variogram2/variog_plot.cpp    \
           variogram2/variogram_controls.cpp    \
           variogram2/variogram_controls_base.cpp    \
           variogram2/variogram_modeler_gui.cpp    \
           variogram2/variogram_modeling_screen.cpp    \
           variogram2/first_scr.cpp    \
           viewer/qvtkGsTLViewer.cpp    \
           viewer/region_param_viewer.cpp    \
           viewer/grid_param_viewer.cpp    \
           viewer/group_param_viewer.cpp    \
           viewer/visualization_parameters.cpp    \
           viewer/object_property_viewer.cpp    \
           viewer/colormap_controller.cpp    \
           viewer/colormap_widget.cpp    \
           viewer/vtk_project_view_gui.cpp    \
           viewer/vtk_prop_map.cpp    \
           viewer/grid_section_view.cpp    \
           viewer/property_filter_view.cpp    \
           viewer/property_param_viewer.cpp    \
           viewer/property_stats_view.cpp    \
           vtk_prop/vtk_common.cpp    \
           vtk_prop/colormap_actor.cpp    \
           vtk_prop/vtk_prop_cgrid.cpp    \
           vtk_prop/vtk_prop_gstl.cpp    \
           vtk_prop/vtk_prop_log.cpp    \
           vtk_prop/vtk_prop_mgrid.cpp    \
           vtk_prop/vtk_prop_pointset.cpp    \
           vtk_prop/vtk_prop_structured_grid.cpp

FORMS += viewer/Project_view_form.ui \
         appli/controls_widget.ui \
         appli/data_analysis_gui_base.ui \
         appli/histogram_control_panel_base.ui \
         appli/MainWindow.ui \
         appli/new_cartesian_grid_dialog_base.ui \
         appli/qpplot_control_panel_base.ui \
         appli/qt_algo_control_panel_base.ui \
         appli/scatterplot_control_panel_base.ui \
         appli/snapshot_dialog_base.ui \
         utils/delete_properties_dialog_base.ui \
         utils/delete_regions_dialog_base.ui \
         utils/multichoice_dialog_base.ui \
         utils/create_distribution_dialog.ui \
         variogram2/first_scr_base.ui \
         variogram2/point_set_base.ui \
         variogram2/rgrid_base.ui \
         variogram2/variogram_modeler_gui_base.ui \
         variogram2/variogram_plot_settings_dialog.ui \
         variogram2/variogram_print_plots_dialog.ui \
         variogram2/variogram_structure_controls_base.ui

RESOURCES += icons.qrc

TARGET = ar2gems_gui

QT += xml
QT += opengl
CONFIG += plugin
INCLUDEPATH += $(QTDIR)/tools/designer/interfaces
INCLUDEPATH += /usr/local/include/
contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/gui
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/gui
}
include( $$GSTLAPPLI_HOME/config.qmake )
exists( MMakefile ):include( MMakefile )
