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

#ifndef __GSTLAPPLI_GUI_VTK_MGRID_H__
#define __GSTLAPPLI_GUI_VTK_MGRID_H__

#include <gui/common.h>
#include <gui/vtk_prop/vtk_prop_strati_grid.h>
#include <grid/reduced_grid.h>

#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkImageData.h>
#include <vtkUniformGrid.h>
#include <vtkStructuredGrid.h>
#include <vtkUnstructuredGrid.h>
#include <vtkLookupTableWithEnabling.h>
#include <vtkThreshold.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkPassThrough.h>

#include <map>

class GUI_DECL vtkProp_mgrid : public GsTL_vtkProp {

 public:
  static Named_interface* create_new_interface( std::string& );

 public:
  vtkProp_mgrid();
  virtual ~vtkProp_mgrid();

//  virtual void init( const Geostat_grid* grid );
  virtual void init( Geostat_grid* grid, vtkRenderer* renderer );

  virtual vtkProp* prop();
  virtual void set_visibility(bool on);
  virtual bool is_visibile();

//  virtual void update( const std::string& property_name,
//                       Oinv::Update_reason reason );

  virtual void enable_full_view();
  virtual void disable_full_view();

  virtual int add_section(int id, QString orientation, bool is_visible);
  virtual bool update_section(int id, int steps, bool is_visible);

  virtual void show_bounding_box( bool on );
  virtual void hide_volume( bool on ) ;

  virtual void set_colormap( Colormap* cmap );
  virtual void refresh_colormap();

  virtual void set_property( const std::string& property_name, Colormap* cmap );
  virtual void set_region(const std::string& region_name );

 protected:
  virtual void refresh();
  virtual void property_deleted( const std::string& prop_name );
  virtual bool connect_threshold_to_data(vtkThreshold* thresholder);
  virtual bool disable_threshold_pipeline();
  virtual bool enable_threshold_pipeline();
  virtual bool enable_section_pipeline();
  virtual bool disable_section_pipeline();

  virtual void set_colortable_to_mapper(vtkMapper* mapper);


 protected:
//  typedef std::list< Oinv_slice* >::iterator SliceList_iterator;

  const Reduced_grid* grid_;

  vtkUnstructuredGrid* ugrid_;
  vtkDataSetMapper* mapper_;
  //vtkActor* actor_;
  vtkActor* actor_outline_;
  vtkImageData* image_data_;
  vtkThreshold* vtk_mask_threshold_;
  vtkDataSetSurfaceFilter* surface_extractor_;
  vtkPassThrough* data_pass_through_;

  std::string cached_region_name_;
  vtkThreshold* region_threshold_;

  vtkLookupTableWithEnabling* color_table_;

  bool initialized_;

};



#endif
