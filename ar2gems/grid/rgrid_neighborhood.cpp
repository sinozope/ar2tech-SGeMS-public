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
** This file is part of the "grid" module of the Geostatistical Earth
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
/*
#define _SECURE_SCL 0 
#ifdef _DEBUG
#define _HAS_ITERATOR_DEBUGGING 0
#endif
*/

#include <grid/rgrid_neighborhood.h>
#include <grid/rgrid.h>
#include <utils/gstl_messages.h>

#include <stack>
#include <algorithm>
#include <cmath>

//=====================================
//    Window Neighborhood
//=====================================

Rgrid_window_neighborhood::Rgrid_window_neighborhood()
  : Window_neighborhood(),
    grid_( 0 ),
    property_( 0 ),
    cursor_( 0,0,0 ),
    size_(-1) {
}


Rgrid_window_neighborhood::
Rgrid_window_neighborhood( const Grid_template& geom, RGrid* grid,
			   Grid_continuous_property* prop )
  : Window_neighborhood(),
    grid_( grid ),
    property_( prop ),
    center_( grid, prop, -1 ),
    size_(-1) {

  geom_ = geom;

  if( grid ) 
    cursor_ = *( grid->cursor() );
}



void Rgrid_window_neighborhood::set_geometry( Grid_template::iterator begin, 
					      Grid_template::iterator end ) {
  geom_.init( begin, end );
  //  for( ; begin!=end ; ++begin )
  //    geom_.add_vector( *begin );
}

void Rgrid_window_neighborhood::
add_geometry_vector( const Grid_template::Euclidean_vector& vec ) {
  geom_.add_vector( vec );
}


void Rgrid_window_neighborhood::includes_center( bool on ) {
  appli_warning( "it does not make much sense to use "
                 << "includes_center(...) on a window neighborhood\n"
                 << "Consider adding a vector to the geometry instead" );
  if( on == includes_center_ ) return;

  if( on ) { 
    // insert a (0,0,0) vector at the begining of the template
    geom_.add_vector( 0,0,0, 0 );
  }
  else {
    appli_assert( *(geom_.begin()) == Grid_template::Euclidean_vector(0,0,0) );
    geom_.remove_vector( 0 );
  }
}


void Rgrid_window_neighborhood::max_size( int s ) {
  geom_.max_size( s );
}

void Rgrid_window_neighborhood::set_grid( RGrid* grid ) {
  grid_ = grid;
  if( grid ) 
    cursor_ = *( grid->cursor() );
}


bool Rgrid_window_neighborhood::
select_property( const std::string& prop_name ) {
  appli_assert( grid_ );
  property_ = grid_->property( prop_name );
  return ( property_ != 0 );
}


void Rgrid_window_neighborhood::find_neighbors( const Geovalue& center ) {
  size_ = -1;
  center_ = center;
  center_.set_property_array( property_ );

  neighbors_.clear();
  if( !property_ ) return;

  SGrid_cursor cursor( *grid_->cursor() );
  GsTLInt i,j,k;
  cursor.coords( center.node_id(), i,j,k ); 
  GsTLGridNode center_location( i,j,k );

  if( geom_.size() == 0 ) return;

  Grid_template::iterator begin = geom_.begin();
  Grid_template::iterator bound = geom_.end()-1;
  /* nico: old code, remove if new works properly
  while (bound != begin-1) {
    GsTLGridNode p = center_location + (*bound);
    if( !grid_->contains( p ) ) {
      bound--;
      continue;
    }
    if( grid_->is_informed( p ) )
      break;
    else
      bound--;
  }
  */

  while (bound != begin) {
    GsTLGridNode p = center_location + (*bound);
    GsTLInt node_id = cursor.node_id( p[0], p[1], p[2] );
    if( node_id < 0 ) {
      bound--;
      continue;
    }
    if( property_->is_informed( node_id ) )
      break;
    else
      bound--;
  }

  // Need to place the bound at one pass the actual end point
  bound++;

  for( ; begin != bound; ++begin ) {
    GsTLGridNode node = center_location + (*begin);
    neighbors_.push_back( Geovalue( grid_, property_, 
				    cursor_.node_id( node[0], node[1],
						     node[2] ) )
			  );
    //neighbors_.push_back( grid_->geovalue( center_location + (*begin) ) );
  }
}

void Rgrid_window_neighborhood::find_neighbors( const Geovalue& center , Neighbors & neighbors ) const
{
  neighbors.clear();
  neighbors.center_is(center);
  if( !property_ ) return;

  SGrid_cursor cursor( *grid_->cursor() );
  GsTLInt i,j,k;
  cursor.coords( center.node_id(), i,j,k ); 
  GsTLGridNode center_location( i,j,k );

  if( geom_.size() == 0 ) return;

  Grid_template::const_iterator begin = geom_.begin();
  Grid_template::const_iterator bound = geom_.end()-1;
  /* nico: old code, remove if new works properly
  while (bound != begin-1) {
    GsTLGridNode p = center_location + (*bound);
    if( !grid_->contains( p ) ) {
      bound--;
      continue;
    }
    if( grid_->is_informed( p ) )
      break;
    else
      bound--;
  }
  */

  while (bound != begin) {
    GsTLGridNode p = center_location + (*bound);
    GsTLInt node_id = cursor.node_id( p[0], p[1], p[2] );
    if( node_id < 0 ) {
      bound--;
      continue;
    }
    if( property_->is_informed( node_id ) )
      break;
    else
      bound--;
  }

  // Need to place the bound at one pass the actual end point
  bound++;

  for( ; begin != bound; ++begin ) {
    GsTLGridNode node = center_location + (*begin);
    neighbors.push_back( Geovalue( grid_, property_, 
				    cursor_.node_id( node[0], node[1],
						     node[2] ) )
			  );
    //neighbors_.push_back( grid_->geovalue( center_location + (*begin) ) );
  }

  neighbors.set_valid(neigh_filter_->is_neighborhood_valid());
}


void Rgrid_window_neighborhood::find_all_neighbors( const Geovalue& center ) {
  size_ = -1;
  center_ = center;
  center_.set_property_array( property_ );

  neighbors_.clear();
  if( !property_ ) return;

  SGrid_cursor cursor( *grid_->cursor() );
  GsTLInt i,j,k;
  cursor.coords( center.node_id(), i,j,k ); 
  GsTLGridNode center_location( i,j,k );

  if( geom_.size() == 0 ) return;

  Grid_template::iterator begin = geom_.begin();
  Grid_template::iterator bound = geom_.end()-1;

  for( ; begin != bound+1 ; ++begin ) {
    GsTLGridNode node = center_location + (*begin);
    neighbors_.push_back( Geovalue( grid_, property_, 
				    cursor_.node_id( node[0], node[1],
						     node[2] ) )
			  );
  }
}

void Rgrid_window_neighborhood::find_all_neighbors( const Geovalue& center , Neighbors & neighbors ) const 
{
  neighbors.clear();
  neighbors.center_is(center);
  if( !property_ ) return;

  SGrid_cursor cursor( *grid_->cursor() );
  GsTLInt i,j,k;
  cursor.coords( center.node_id(), i,j,k ); 
  GsTLGridNode center_location( i,j,k );

  if( geom_.size() == 0 ) return;

  Grid_template::const_iterator begin = geom_.begin();
  Grid_template::const_iterator bound = geom_.end()-1;

  for( ; begin != bound+1 ; ++begin ) {
    GsTLGridNode node = center_location + (*begin);
    neighbors.push_back( Geovalue( grid_, property_, 
				    cursor_.node_id( node[0], node[1],
						     node[2] ) )
			  );
  }

  neighbors.set_valid(neigh_filter_->is_neighborhood_valid());
}


void Rgrid_window_neighborhood::
set_neighbors( const_iterator begin, const_iterator end ) {
  neighbors_.clear();
  int i =0;
  for( const_iterator it = begin ; it != end ; ++it, ++i ) {
    const Geostat_grid* g_grid = it->grid();
    if( g_grid != grid_ ) continue;

    neighbors_.push_back( *it );
    neighbors_[i].set_property_array( property_ );
  }
}


struct Is_informed {
  bool operator() ( const Geovalue& g ) { return g.is_informed(); }
};


/*
 * Note:  class Window_neighborhood will call this size() function, whose
 *           return value is not the actual size of neighbors_ vector, 
 *           but the number of informed nodes in neighbors_ vector
 */
int Rgrid_window_neighborhood::size() const {
  if( size_ == -1 )
    size_ = std::count_if( neighbors_.begin(), neighbors_.end(), Is_informed() );

  return size_;
}





//===================================================
//    Ellipsoid Neighborhood
//======================================

Rgrid_ellips_neighborhood::
Rgrid_ellips_neighborhood( RGrid* grid,
			   Grid_continuous_property* property,
			   double radius1, double radius2, double radius3, 
			   double angle1, double angle2, double angle3,
			   int max_neighbors, 
			   const Covariance<GsTLPoint>* cov,
         const Grid_region* region) 
  : Neighborhood(),
    grid_( grid ),
    property_( property ),
    max_neighbors_( max_neighbors ) {

  region_ = region;
  
  appli_assert( grid_ );

  cursor_ = *( grid_->cursor() );
  double cell_dim_x = grid->geometry()->cell_dims().x();
  double cell_dim_y = grid->geometry()->cell_dims().y();
  double cell_dim_z = grid->geometry()->cell_dims().z();


  // use a geobody approach to find all the cells inside the ellipsoid.
  // Then sort them according to covariance.
  Ellipsoid_rasterizer ellipsoid( radius1, radius2, radius3,
			                            angle1, angle2, angle3,
                                  cell_dim_x,cell_dim_y,cell_dim_z,
                                  grid->nx(), grid->ny(), grid->nz());

  const std::vector<Ellipsoid_rasterizer::EuclideanVector >& templ = ellipsoid.rasterize();

  //rebuilt the vector in euclidean space
  typedef std::pair<Ellipsoid_rasterizer::EuclideanVector,int> pair_templ_indexT;
  std::vector< pair_templ_indexT > xyz_templ;
  xyz_templ.reserve(templ.size());
  for(int i=0; i< templ.size(); ++i) {
    Ellipsoid_rasterizer::EuclideanVector dijk =  templ[i];
    xyz_templ.push_back(  std::make_pair( Ellipsoid_rasterizer::EuclideanVector(dijk.x()*cell_dim_x, dijk.y()*cell_dim_y, dijk.z()*cell_dim_z)  ,i  ) );
  }

  // We now sort the template according to covariance cov.
  // If no covariance was specified, create a default one
  if( !cov ) {
    Covariance<GsTLPoint> covar;
    int id = covar.add_structure( "Spherical" );
    
    covar.set_geometry( id, 
			radius1, radius2, radius3,
			angle1, angle2, angle3 );

    std::sort( xyz_templ.begin(), xyz_templ.end(), Evector_indexed_greater_than( covar ) );
  }
  else
    std::sort( xyz_templ.begin(), xyz_templ.end(), Evector_indexed_greater_than( *cov ) );

  // set templ in the same order than 
  std::vector<Ellipsoid_rasterizer::EuclideanVector > sorted_templ;
  sorted_templ.reserve(templ.size());
  for(int i=0; i<xyz_templ.size(); ++i ) {
    sorted_templ.push_back(templ[ xyz_templ[i].second ]);
  }
  
  geom_.init( sorted_templ.begin(), sorted_templ.end() );

}


void Rgrid_ellips_neighborhood::max_size( int s ) {
  max_neighbors_ = s;
}

bool Rgrid_ellips_neighborhood::
select_property( const std::string& prop_name ) {
  property_ = grid_->property( prop_name );
  return ( property_ != 0 );
}


/* This function could be optimized by directly using the property values 
 * array, hence bypassing the virtual function calls in Grid_continuous_property.
 */
void Rgrid_ellips_neighborhood::find_neighbors( const Geovalue& center ) {
  neighbors_.clear();
  neigh_filter_->clear();
  if( !property_ ) return;

  center_ = center;
//  center_.set_property_array( property_ );

  // "already_found" is the number of neighbors already found
  int already_found=0;

  // loc will store the i,j,k coordinates of the center, node_id is the 
  // center's node-id. They will be computed differently, whether "center"
  // and *this both refer to the same grid or not.
  GsTLGridNode loc;
  GsTLInt node_id = -1;

  if( center.grid() != grid_ ) {
    // "center" and "*this" do not refer to the same grid
    bool ok = grid_->geometry()->grid_coordinates( loc, center.location() );
    if( !ok ) return;

    if( includes_center_ ) 
      node_id = cursor_.node_id( loc[0], loc[1], loc[2] );
  }
  else {
    // "center" and "*this" both refer to the same grid
    cursor_.coords( center.node_id(), loc[0], loc[1], loc[2] ); 
    node_id = center.node_id();      
  }
  
  if( includes_center_ && property_->is_informed( node_id ) ) {
    Geovalue gval( grid_, property_, node_id );
    if(neigh_filter_->is_admissible(gval, center)) {
      neighbors_.push_back( gval );
      already_found++;
    }
  }
 
  
  // Visit each node defined by the window ("geom_")
  // For each node, check if the node is inside the grid.
  // If it is and it contains a data value, add it to the list of
  // neighbors
  Grid_template::const_iterator it = geom_.begin();
  Grid_template::const_iterator end = geom_.end();

  while( it != end && already_found < max_neighbors_ ) {
    GsTLGridNode node = loc + (*it);
    GsTLInt node_id = cursor_.node_id( node[0], node[1], node[2] );
    
    if( node_id < 0 ) {
      // The node does not belong to the grid: skip it
      it++;
      continue;
    }

    if( property_->is_informed( node_id )  ) {
      if(region_ &&  !region_->is_inside_region(node_id) ) continue;
      // The node is informed: get the corresponding geovalue and add it
      // to the list of neighbors
      Geovalue gval( grid_, property_, node_id );
      if(neigh_filter_->is_admissible(gval, center)) {
        neighbors_.push_back( gval );
        already_found++;
      }
//      neighbors_.push_back( Geovalue( grid_, property_, node_id ) );
//      already_found++;
    }

    it++;
  }
 // if(!neigh_filter_->is_neighborhood_valid()) neighbors_.clear();

}

void Rgrid_ellips_neighborhood::find_neighbors( const Geovalue& center , Neighbors & neighbors ) const
{
  neighbors.clear();
  neighbors.center_is(center);
  neigh_filter_->clear();
  if( !property_ ) return;

  // "already_found" is the number of neighbors already found
  int already_found=0;

  // loc will store the i,j,k coordinates of the center, node_id is the 
  // center's node-id. They will be computed differently, whether "center"
  // and *this both refer to the same grid or not.
  GsTLGridNode loc;
  GsTLInt node_id = -1;
  SGrid_cursor cursor( *grid_->cursor() );

  if( center.grid() != grid_ ) {
    // "center" and "*this" do not refer to the same grid
    bool ok = grid_->geometry()->grid_coordinates( loc, center.location() );
    if( !ok ) return;

    if( includes_center_ ) 
      node_id = cursor.node_id( loc[0], loc[1], loc[2] );
  }
  else {
    // "center" and "*this" both refer to the same grid
    cursor.coords( center.node_id(), loc[0], loc[1], loc[2] ); 
    node_id = center.node_id();      
  }
  
  if( includes_center_ && property_->is_informed( node_id ) ) {
    Geovalue gval( grid_, property_, node_id );
    if(neigh_filter_->is_admissible(gval, center)) {
      neighbors.push_back( gval );
      already_found++;
    }
  }
 
  
  // Visit each node defined by the window ("geom_")
  // For each node, check if the node is inside the grid.
  // If it is and it contains a data value, add it to the list of
  // neighbors
  Grid_template::const_iterator it = geom_.begin();
  Grid_template::const_iterator end = geom_.end();

  while( it != end && already_found < max_neighbors_ ) {
    GsTLGridNode node = loc + (*it);
    GsTLInt node_id = cursor.node_id( node[0], node[1], node[2] );
    
    if( node_id < 0 ) {
      // The node does not belong to the grid: skip it
      it++;
      continue;
    }

    if( property_->is_informed( node_id )  ) {
      if(region_ &&  !region_->is_inside_region(node_id) ) continue;
      // The node is informed: get the corresponding geovalue and add it
      // to the list of neighbors
      Geovalue gval( grid_, property_, node_id );
      if(neigh_filter_->is_admissible(gval, center)) {
        neighbors.push_back( gval );
        already_found++;
      }
//      neighbors_.push_back( Geovalue( grid_, property_, node_id ) );
//      already_found++;
    }

    it++;
  }

  neighbors.set_valid(neigh_filter_->is_neighborhood_valid());
 // if(!neigh_filter_->is_neighborhood_valid()) neighbors_.clear();

}



/*
void Rgrid_ellips_neighborhood::find_neighbors( const Geovalue& center ) {
  // this function only works if both geovalue "center" and the neighborhood 
  // refer to the same grid
  appli_assert( center.grid() == grid_ );
  
  neighbors_.clear();
  if( !property_ ) return;

  center_ = center;
  center_.set_property_array( property_ );

  // "already_found" is the number of neighbors already found
  int already_found=0;

  if( includes_center_ && center_.is_informed() ) {
    neighbors_.push_back( center_ );
    already_found++;
  }
 
  
  // Get the grid coordinates (not the real coordinates) of the center.
  GsTLGridNode loc;
  cursor_.coords( center.node_id(), loc[0], loc[1], loc[2] ); 

  // Visit each node defined by the window ("geom_")
  // For each node, check if the node is inside the grid.
  // If it is and it contains a data value, add it to the list of
  // neighbors
  Grid_template::const_iterator it = geom_.begin();
  Grid_template::const_iterator end = geom_.end();

  while( it != end && already_found < max_neighbors_ ) {
    GsTLGridNode node = loc + (*it);
    GsTLInt node_id = cursor_.node_id( node[0], node[1], node[2] );
    
    if( node_id < 0 ) {
      // The node does not belong to the grid: skip it
      it++;
      continue;
    }

    if( property_->is_informed( node_id ) ) {
      // The node is informed: get the corresponding geovalue and add it
      // to the list of neighbors
      neighbors_.push_back( Geovalue( grid_, property_, node_id ) );
      already_found++;
    }

    it++;
  }
}
*/


void Rgrid_ellips_neighborhood::
set_neighbors( const_iterator begin, const_iterator end ) {
  neighbors_.clear();
  int i =0; 
  for( const_iterator it = begin ; it != end ; ++it, ++i ) {
    const Geostat_grid* g_grid = it->grid();
    if( g_grid != grid_ ) continue;

    neighbors_.push_back( *it );
    neighbors_[i].set_property_array( property_ );
  }
}

//==================================================

Rgrid_ellips_neighborhood_hd::
Rgrid_ellips_neighborhood_hd( RGrid* grid,
			      Grid_continuous_property* property,
			      double radius1, double radius2, double radius3, 
			      double angle1, double angle2, double angle3,
			      int max_neighbors,
			      const Covariance<GsTLPoint>* cov,
            const Grid_region* region) 
  : Rgrid_ellips_neighborhood( grid, property,
			       radius1, radius2, radius3,
			       angle1, angle2, angle3,
			       max_neighbors, cov, region ) {
}

void Rgrid_ellips_neighborhood_hd::find_neighbors( const Geovalue& center ) {

  // This is exactly the same function as 
  // Rgrid_ellips_neighborhood::find_neighbors, except that the condition
  // for a node to be a neighbor is that it contains a hard-data
  neighbors_.clear();
  if( !property_ ) return;

  center_ = center;
//  center_.set_property_array( property_ );

  // "already_found" is the number of neighbors already found
  int already_found=0;

  // loc will store the i,j,k coordinates of the center, node_id is the 
  // center's node-id. They will be computed differently, whether "center"
  // and *this both refer to the same grid or not.
  GsTLGridNode loc;
  GsTLInt node_id = -1;

  if( center.grid() != grid_ ) {
    // "center" and "*this" do not refer to the same grid
    bool ok = grid_->geometry()->grid_coordinates( loc, center.location() );
    if( !ok ) return;

    if( includes_center_ ) 
      //GsTLInt id = cursor_.node_id( loc[0], loc[1], loc[2] );
      node_id = cursor_.node_id( loc[0], loc[1], loc[2] );
  }
  else {
    // "center" and "*this" both refer to the same grid
    cursor_.coords( center.node_id(), loc[0], loc[1], loc[2] ); 
    node_id = center.node_id();      
  }

  
  if( includes_center_ && property_->is_informed( node_id ) ) {
    neighbors_.push_back( Geovalue( grid_, property_, node_id ) );
    already_found++;
  }
 
  
  // Visit each node defined by the window ("geom_")
  // For each node, check if the node is inside the grid.
  // If it is and it contains a data value, add it to the list of
  // neighbors
  Grid_template::const_iterator it = geom_.begin();
  Grid_template::const_iterator end = geom_.end();

  while( it != end && already_found < max_neighbors_ ) {
    GsTLGridNode node = loc + (*it);
    GsTLInt node_id = cursor_.node_id( node[0], node[1], node[2] );
    
    if( node_id < 0 ) {
      // The node does not belong to the grid: skip it
      it++;
      continue;
    }

    if( property_->is_harddata( node_id ) ) {
      // The node is informed: get the corresponding geovalue and add it
      // to the list of neighbors
      neighbors_.push_back( Geovalue( grid_, property_, node_id ) );
      already_found++;
    }

    it++;
  }
}

void 
Rgrid_ellips_neighborhood_hd::find_neighbors( const Geovalue& center , Neighbors & neighbors ) const
{
  // This is exactly the same function as 
  // Rgrid_ellips_neighborhood::find_neighbors, except that the condition
  // for a node to be a neighbor is that it contains a hard-data
  neighbors.clear();
  neighbors.center_is(center);
  if( !property_ ) return;

  SGrid_cursor cursor( *grid_->cursor() );
  
  // "already_found" is the number of neighbors already found
  int already_found=0;

  // loc will store the i,j,k coordinates of the center, node_id is the 
  // center's node-id. They will be computed differently, whether "center"
  // and *this both refer to the same grid or not.
  GsTLGridNode loc;
  GsTLInt node_id = -1;

  if( center.grid() != grid_ ) {
    // "center" and "*this" do not refer to the same grid
    bool ok = grid_->geometry()->grid_coordinates( loc, center.location() );
    if( !ok ) return;

    if( includes_center_ ) 
      //GsTLInt id = cursor_.node_id( loc[0], loc[1], loc[2] );
      node_id = cursor.node_id( loc[0], loc[1], loc[2] );
  }
  else {
    // "center" and "*this" both refer to the same grid
    cursor.coords( center.node_id(), loc[0], loc[1], loc[2] ); 
    node_id = center.node_id();      
  }

  
  if( includes_center_ && property_->is_informed( node_id ) ) {
    neighbors.push_back( Geovalue( grid_, property_, node_id ) );
    already_found++;
  }
 
  
  // Visit each node defined by the window ("geom_")
  // For each node, check if the node is inside the grid.
  // If it is and it contains a data value, add it to the list of
  // neighbors
  Grid_template::const_iterator it = geom_.begin();
  Grid_template::const_iterator end = geom_.end();

  while( it != end && already_found < max_neighbors_ ) {
    GsTLGridNode node = loc + (*it);
    GsTLInt node_id = cursor.node_id( node[0], node[1], node[2] );
    
    if( node_id < 0 ) {
      // The node does not belong to the grid: skip it
      it++;
      continue;
    }

    if( property_->is_harddata( node_id ) ) {
      // The node is informed: get the corresponding geovalue and add it
      // to the list of neighbors
      neighbors.push_back( Geovalue( grid_, property_, node_id ) );
      already_found++;
    }

    it++;
  }

  neighbors.set_valid(neigh_filter_->is_neighborhood_valid());
}






//=================================================
//    Ellipsoid_rasterizer
//=================================

Ellipsoid_rasterizer::Ellipsoid_rasterizer(
  double xyz_rad1, double xyz_rad2, double xyz_rad3,
  double xyz_angle1, double xyz_angle2, double xyz_angle3,
  double block_size_x, double block_size_y, double block_size_z,
  int max_size_i, int max_size_j, int max_size_k)
  : block_size_x_(block_size_x),block_size_y_(block_size_y),block_size_z_(block_size_z),
    cursor_(max_size_i,max_size_j,max_size_k),
    norm_( xyz_rad1, xyz_rad2, xyz_rad3,xyz_angle1, xyz_angle2, xyz_angle3 ),
    center_(int(max_size_i/2), int(max_size_j/2), int(max_size_k/2)),
    already_visited_( max_size_i*max_size_j*max_size_k, false ),
    reference_radius_(xyz_rad1)

{
  this->rasterize_ellipsoid();

  already_visited_.resize(0);

}


void Ellipsoid_rasterizer::rasterize_ellipsoid() {
  GsTLInt center_id = 
    cursor_.node_id( center_[0], center_[1], center_[2] );
//  appli_assert( center_id >= 0 && center_id < int(already_visited_.size()) );

  already_visited_[ center_id ] = true;
  s_.push( center_id );

  EuclideanVector west(-1,0,0);
  EuclideanVector east(1,0,0);
  EuclideanVector south(0,-1,0);
  EuclideanVector north(0,1,0);
  EuclideanVector down(0,0,-1);
  EuclideanVector up(0,0,1);


  // move away from center, until we reach the border of the ellipsoid
  while( ! s_.empty() ) {
    GsTLInt id = s_.top();
    s_.pop();
    GsTLGridNode loc;
    cursor_.coords( id, loc[0], loc[1], loc[2] );
    
    check_node( loc+west );
    check_node( loc+east );
    check_node( loc+north );
    check_node( loc+south );
    check_node( loc+up );
    check_node( loc+down );
        
  }

  //return ellipsoid_nodes_;
}


void Ellipsoid_rasterizer::check_node( const GsTLGridNode& loc ) {
  // check if loc belongs to the grid
  if ( !cursor_.check_triplet( loc[0], loc[1], loc[2] ) ) return;
  
  int id = cursor_.node_id( loc[0], loc[1], loc[2] );
  //appli_assert( id >= 0 && id < int(already_visited_.size()) );

  if ( already_visited_[id] ) return;

  // vector in ijk to be transfomed into x,y,z
  EuclideanVector vec_ijk = loc - center_;
  EuclideanVector vec_xyz;
  vec_xyz.x() = vec_ijk.x() * block_size_x_;
  vec_xyz.y() = vec_ijk.y() * block_size_y_;
  vec_xyz.z() = vec_ijk.z() * block_size_z_;

  if( norm_( vec_xyz ) <= reference_radius_ ) {
    // loc is inside the ellipsoid

    ellipsoid_nodes_.push_back( vec_ijk );
    s_.push( id );
    already_visited_[id] = true;
  }
}

/*
Ellipsoid_rasterizer::
Ellipsoid_rasterizer( GsTLInt nx, GsTLInt ny, GsTLInt nz,
		      GsTLInt max_radius, GsTLInt mid_radius, GsTLInt min_radius,
		      double x_angle, double y_angle, double z_angle ) 
  : already_visited_( nx*ny*nz, false ),
    cursor_( nx, ny, nz ),
    norm_( double(max_radius), double(mid_radius), double(min_radius),
	   x_angle, y_angle, z_angle ),
    center_( int(nx/2), int(ny/2), int(nz/2) ) {

  max_radius_ = max_radius;
}


Ellipsoid_rasterizer::~Ellipsoid_rasterizer() {
}

std::vector< Ellipsoid_rasterizer::EuclideanVector >&
Ellipsoid_rasterizer::rasterize() {
  GsTLInt center_id = 
    cursor_.node_id( center_[0], center_[1], center_[2] );
  appli_assert( center_id >= 0 && center_id < int(already_visited_.size()) );

  already_visited_[ center_id ] = true;
  s_.push( center_id );

  EuclideanVector west(-1,0,0);
  EuclideanVector east(1,0,0);
  EuclideanVector south(0,-1,0);
  EuclideanVector north(0,1,0);
  EuclideanVector down(0,0,-1);
  EuclideanVector up(0,0,1);


  // move away from center, until we reach the border of the ellipsoid
  while( ! s_.empty() ) {
    GsTLInt id = s_.top();
    s_.pop();
    GsTLGridNode loc;
    cursor_.coords( id, loc[0], loc[1], loc[2] );
    
    check_node( loc+west );
    check_node( loc+east );
    check_node( loc+north );
    check_node( loc+south );
    check_node( loc+up );
    check_node( loc+down );
        
  }

  return ellipsoid_nodes_;
}


void Ellipsoid_rasterizer::check_node( const GsTLGridNode& loc ) {
  // check if loc belongs to the grid
  if ( !cursor_.check_triplet( loc[0], loc[1], loc[2] ) ) return;
  
  int id = cursor_.node_id( loc[0], loc[1], loc[2] );
  appli_assert( id >= 0 && id < int(already_visited_.size()) );

  if ( already_visited_[id] ) return;

  EuclideanVector vec = loc - center_;

  if( norm_( vec ) <= max_radius_ ) {
    // loc is inside the ellipsoid

    ellipsoid_nodes_.push_back( vec );
    s_.push( id );
    already_visited_[id] = true;
  }
}

*/