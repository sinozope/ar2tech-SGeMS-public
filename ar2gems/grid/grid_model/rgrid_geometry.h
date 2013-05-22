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

#ifndef __GSTLAPPLI_GRID_RGRIDGEOMETRY_H__ 
#define __GSTLAPPLI_GRID_RGRIDGEOMETRY_H__ 
 
#include <grid/common.h>
#include <math/gstlpoint.h> 
 
 
/*****************************************************************/ 
class GRID_DECL RGrid_geometry { 
public: 
    virtual ~RGrid_geometry(); 
     
    virtual RGrid_geometry* clone() const = 0; 
 
    GsTLInt dim( GsTLInt i ) const { return n_[i];} 
    GsTLInt size() const { return ( n_[0]*n_[1]*n_[2] ); } 
    void set_size( GsTLInt i, GsTLInt n ) {  
        n_[i] = n ; 
        n1_[i] = n-1; 
        if (n1_[i] <= 0 ) n1_[i] = 1; 
    } 
 
    /** Returns the location of node (i,j,k). For an Rgrid, the location 
     * is expressed in stratigraphic coordinates (x and y are the real coordinates 
     * but z is in [0,1[ if the point is in layer 0, [1,2[ if in layer 1, etc) 
     * Actually, z can b multiplied by a constant layer thickness and shifted by 
     * a constant z0. 
     *  
     * This point should be clarified... 
     */ 
    virtual GsTLPoint coordinates(GsTLInt i, GsTLInt j, GsTLInt k) const = 0;

    /** find the grid coordinates of point \c p. The grid coordinates are 
    * stored into \c ijk. \c grid_coordinates return a flag indicating 
    * whether the operation suceeded. If the flag is flase, \c ijk was not 
    * changed.
    * The i,j,k coordinates are coordinates in grid itself (no coarse grid
    * is taken into account)
    */
    virtual bool 
      grid_coordinates( GsTLGridNode& ijk, const GsTLPoint& p ) const = 0;
 
   virtual void set_rotation_z(double z_angle)=0;
   virtual double rotation_z() const =0;


    /** The dimensions of a grid cell (in stratigraphic coordinates) 
     */ 
    virtual void set_cell_dims( const GsTLCoordVector& v ) { 
        cell_dims_ = v; 
    } 
    virtual const GsTLCoordVector& cell_dims() const  { 
        return cell_dims_; 
    } 

 
protected: 
    RGrid_geometry() 
      : cell_dims_(1,1,1) { 
        n_[0] = 0; n_[1] = 0; n_[2] = 0; 
        n1_[0] = 1; n1_[1] = 1; n1_[2] = 1; 
    } 
protected: 
    GsTLInt n_[3]; 
    GsTLInt n1_[3]; 
 
    GsTLCoordVector cell_dims_;

}; 
 
 
/*****************************************************************/ 
 
class GRID_DECL Simple_RGrid_geometry : public RGrid_geometry { 
public: 
    Simple_RGrid_geometry(); 
    ~Simple_RGrid_geometry(); 
 
    virtual RGrid_geometry* clone() const; 
 
 
    /** The origin is the leftmost, bottom NODE of the grid 
     */ 
    void set_origin(const GsTLPoint& o) { 
        origin_ = o; 
    } 
   const GsTLPoint& origin() const { 
        return origin_; 
    } 

    virtual void set_cell_dims( const GsTLCoordVector& v ) { 
        cell_dims_ = v; 
        volume_ = cell_dims_[0]*cell_dims_[1]*cell_dims_[2];
    } 

    double get_volume() const {return volume_;}

    /** The zrotation defined the azimuth of the j axis
     */ 
   virtual void set_rotation_z(double z_angle); 
   virtual double rotation_z() const { 
        return z_rot_; 
    } 

    /** Find the actual coordinates of a grid node given its (i,j,k)  
     * coordinates. 
     */ 
    virtual GsTLPoint coordinates(GsTLInt i, GsTLInt j, GsTLInt k) const;
 
    virtual bool grid_coordinates( GsTLGridNode& ijk, const GsTLPoint& p ) const;
 
protected: 
    GsTLPoint origin_;
    double z_rot_;
    double z_cos_angle_;
    double z_sin_angle_;

    double volume_;
 
 //   double z_cos_back_angle_;
 //   double z_sin_back_angle_;
}; 
 
 
#endif 
 
