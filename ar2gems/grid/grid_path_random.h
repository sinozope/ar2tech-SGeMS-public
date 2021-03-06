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



#ifndef __GSTLAPPLI_GRID_MODEL_GRID_RANDOM_PATH_H__  
#define __GSTLAPPLI_GRID_MODEL_GRID_RANDOM_PATH_H__ 
 
#include <grid/common.h>
#include <math/gstlvector.h> 
#include <grid/geovalue.h>  
#include <grid/geostat_grid.h>
#include <grid/grid_path.h>
#include <grid/gval_iterator.h>
#include <grid/grid_property.h>
#include <grid/grid_region.h>

#include <vector> 
 

/**
 * Grid_random_path class represents a traversal random path on a Geostat_grid. 
 * The path covers all nodes of the grid.
 */
class GRID_DECL Grid_random_path : public Grid_path< Gval_iterator<TabularMapIndex> >
{
public:
  typedef Gval_iterator<TabularMapIndex> iterator;


public:
  // get the reference to the begin of the path
  iterator begin() const;

  // get the end of the path
  iterator end() const;

  // get the size of the path
  GsTLInt size() const;

  // get the node_id (used in the grid) of a node on the path. The argument _path_index is the index on the path
  GsTLInt node_id( GsTLInt _path_index ) const;

  // get the Geovalue associated with a node on the path. The argument _path_index is the index on the path
  Geovalue geovalue( GsTLInt _path_index ) const;

  virtual bool set_property(std::string prop_name);


protected:
  std::vector<GsTLInt> grid_path_;
  Geostat_grid* grid_;
  Grid_continuous_property * prop_;
  

public:
  Grid_random_path(Geostat_grid * _grid, Grid_continuous_property * _prop, Grid_region* region = 0);
  Grid_random_path(Geostat_grid * _grid, Grid_region* region=0);
  Grid_random_path(Geostat_grid * _grid, Grid_continuous_property * _prop);
  virtual ~Grid_random_path(void);
};


#endif