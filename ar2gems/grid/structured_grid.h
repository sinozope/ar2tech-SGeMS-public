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

#ifndef __GSTLAPPLI_STRUCTURED_GRID_H__ 
#define __GSTLAPPLI_STRUCTURED_GRID_H__ 

#include <grid/cartesian_grid.h>
#include <math/gstlpoint.h>
#include <grid/common.h>
#include <vtkStructuredGrid.h>
#include <vtkSmartPointer.h>
#include <vtkCellCenters.h>



class Structured_grid_coord_mapper;


class GRID_DECL Structured_grid :  public Cartesian_grid
{
public:

  static Named_interface* create_new_interface(std::string& params);

  Structured_grid();

  Structured_grid(std::string name);

  Structured_grid(std::string name, int nx, int ny, int nz);

  virtual ~Structured_grid();

  virtual std::string type() const { return "Structured_grid"; } 
  virtual std::string classname() const { return this->type(); } 

  virtual GsTLPoint origin() const {return origin_;}

  void set_structured_points( std::vector<GsTLPoint>& corner_points);

    /** Computes the location of a node, given its node_id. 
  // This is the "real world" coordinates.  Use location to get
  // the geological coordinate
   */ 
  virtual location_type xyz_location( int node_id ) const;

  vtkSmartPointer<vtkStructuredGrid> get_structured_geometry() { return sgrid_geom_;}
  GsTLPoint get_corner_point_locations(int id) const ;

//  virtual double get_support(int nodeid) const;

protected:
  vtkSmartPointer<vtkStructuredGrid> sgrid_geom_;
  vtkSmartPointer<vtkCellCenters> cell_centers_filter_;
  GsTLPoint origin_;

};


class Structured_grid_coord_mapper : public Coordinate_mapper 
{
public :
  Structured_grid_coord_mapper(Structured_grid* sgrid);

  virtual GsTLPoint uvw_coords(GsTLPoint xyz); 
  virtual GsTLPoint xyz_coords(GsTLPoint uvw); 

protected :
  Structured_grid* sgrid_;  
  GsTLTripletTmpl<int> grid_cell_number_;

};

#endif