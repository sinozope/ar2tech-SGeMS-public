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
** This file is part of the "filters" module of the Geostatistical Earth
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

#ifndef __GSTLAPPLI_LIBRARY_FILTERS_INIT_H__ 
#define __GSTLAPPLI_LIBRARY_FILTERS_INIT_H__ 
 
#include <filters/common.h>
#include <appli/manager_repository.h> 
 
 
#include <iostream> 
 
 
 
 
class FILTERS_DECL library_filters_init { 
  public: 
  static int init_lib() ; 
     
  static int release_lib(); 
 
  private: 
  static int references_; 
   
  static bool bind_toplevel_infilters_factories(Manager* dir); 
  static bool bind_gslib_infilters_factories(Manager* dir); 
  static bool bind_output_filters_factories(Manager* dir); 
  static bool bind_csv_infilters_factories(Manager* dir);

  static bool bind_geometry_xml_managers(Manager* dir);
  static bool bind_project_output(Manager* dir);
 
}; 
 
 
 
extern "C" FILTERS_DECL int libGsTLAppli_filters_init(); 
extern "C" FILTERS_DECL  int libGsTLAppli_filters_release(); 

 
 
#endif 
