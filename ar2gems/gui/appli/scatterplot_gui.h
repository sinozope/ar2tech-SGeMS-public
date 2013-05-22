/* -----------------------------------------------------------------------------
** Copyright (c) 2012 Advanced Resources and Risk Technology, LLC
** All rights reserved.
**
** This file is part of Advanced Resources and Risk Technology, LLC (AR2TECH) 
** version of the open source software sgems.  It is a derivative work by 
** AR2TECH (THE LICENSOR) based on the x-free license granted in the original 
** version of the software (see notice below) and now sublicensed such that it 
** cannot be distributed or modified without the explicit and written permission 
** of AR2TECH.
**
** Only AR2TECH can modify, alter or revoke the licensing terms for this 
** file/software.
**
** This file cannot be modified or distributed without the explicit and written 
** consent of AR2TECH.
**
** Contact Dr. Alex Boucher (aboucher@ar2tech.com) for any questions regarding
** the licensing of this file/software
**
** The open-source version of sgems can be downloaded at 
** sourceforge.net/projects/sgems.
** ----------------------------------------------------------------------------*/



/**********************************************************************
** Author: Nicolas Remy
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the "gui" module of the Geostatistical Earth
** Modeling Software (GEMS)
**
** This file may be distributed and/or modified under the terms of the 
** license defined by the Stanford Center for Reservoir Forecasting and 
** appearing in the file LICENSE.XFREE included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
**
** Contact the Stanford Center for Reservoir Forecasting, Stanford University
** if any conditions of this licensing are not clear to you.
**
**********************************************************************/

#ifndef __GSTLAPPLI_GUI_APPLI_SCATTERPLOT_GUI_H__
#define __GSTLAPPLI_GUI_APPLI_SCATTERPLOT_GUI_H__


#include <gui/common.h>
#include <gui/appli/data_analysis_gui.h>
//Added by qt3to4:
#include <QLabel>

class GsTL_project;
class Grid_continuous_property;
class Grid_region;
class Scatterplot_control_panel;
class QLabel;
class Scatter_plot;
class QwtPlotCurve;

class GUI_DECL Scatterplot_gui : public Data_analysis_gui {

  Q_OBJECT

public:
  Scatterplot_gui( GsTL_project* project,
                   QWidget* parent = 0, const char* name = 0 );
  ~Scatterplot_gui();


public slots:
  void update_var1_low_clip( float );
  void update_var1_high_clip( float );
  void update_var2_low_clip( float );
  void update_var2_high_clip( float );
  void reset_var1_clipping_values();
  void reset_var2_clipping_values();

//  void get_var1_data_from( const Grid_continuous_property* );
//  void get_var2_data_from( const Grid_continuous_property* );
  void get_var1_data_from(  Grid_continuous_property*, const Grid_region* = NULL );
  void get_var2_data_from(  Grid_continuous_property*, const Grid_region* = NULL );
  void draw_regression_line( bool on );

  virtual void set_x_axis_logscale( bool on );
  virtual void set_y_axis_logscale( bool on );

protected:
  virtual void clean();
  void update_all();
  void refresh_stats();
  virtual void paint_stats( QPainter& );

  //TL modified
  void savePostScript(SimplePs & ps){}
  void build_stats();

// When the two same properties are selected
// there is a riks that the original
// active region will be lost
  Grid_continuous_property* prop1_;
  Grid_continuous_property* prop2_;


protected:
  Scatterplot_control_panel* control_panel_;
  QwtPlotCurve * regression_line_curve_id_;

  Scatter_plot* plotter_;


 private:
  void find_regression_line_end_points( double*& x, double*& y,
					float xmin, float ymin,
					float xmax, float ymax,
					float slope, float intercept );
};

#endif
