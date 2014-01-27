/****************************************************************************
 *
 * $Id$
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2014 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 * Plane geometrical structure.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/


#ifndef vpPlane_hh
#define vpPlane_hh




/*!
  \class vpPlane

  \ingroup GeometryPlane

  \brief This class defines the container for a plane geometrical structure.

  A plane is given by the equation \f$Ax + By + Cz + D = 0\f$ where
  (x,y,z) are the coordinates of a point and where \f$[A,B,C]^T\f$ is a normal
  vector of the plane.

*/

#include <visp/vpColVector.h>
#include <visp/vpPoint.h>
#include <visp/vpHomogeneousMatrix.h>


class VISP_EXPORT vpPlane
{

#ifdef VISP_BUILD_DEPRECATED_FUNCTIONS
  // for backward compatibility
 public:
#else
 private:
#endif
  double A,B,C,D ;


public:
  vpPlane() ;
  vpPlane(const vpPlane& P) ;
  vpPlane(const double A, const double B,const  double C,const  double D) ;
  vpPlane(const vpPoint& P, const vpColVector &n) ;
  vpPlane(const vpPoint &P, const vpPoint &Q, const vpPoint &R) ;
  void init(const vpPoint& P, const vpPoint& Q, const vpPoint& R) ;
  void init(const vpColVector& P, const vpColVector &n) ;
  void init(const vpPlane& P) ;

  // SET the parameter
  /*! Set plane parameter A. */
  inline void setA(const double A) {   this->A = A ; }
  /*! Set plane parameter B. */
  inline void setB(const double B) {   this->B = B ; }
  /*! Set plane parameter C. */
  inline void setC(const double C) {   this->C = C ; }
  /*! Set plane parameter D. */
  inline void setD(const double D) {   this->D = D ; }
  /*! Set plane parameters A, B, C, D. */
  inline void setABCD(const double A, const double B, 
		      const double C, const double D) 
  {
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D; 
  }

  vpPlane& operator =(const vpPlane& f) ;

  // GET information
  /*! \return The value of the plane parameter A. */
  double getA() const { return A ; }
  /*! \return The value of the plane parameter B. */
  double getB() const { return B ; }
  /*! \return The value of the plane parameter C. */
  double getC() const { return C ; }
  /*! \return The value of the plane parameter D. */
  double getD() const { return D ; }

  /*!

    \return Return the four dimension vector \f$[A,B,C,D]^T\f$
    corresponding to the plane parameters.

  */
  inline vpColVector getABCD() const {
    vpColVector n(4);
    n[0]=A;
    n[1]=B;
    n[2]=C;
    n[3]=D;
    
    return n;
  }
  /*!

    \warning This method is provided for compatibility with the
    previous versions. Users should now use getABCD().

    \return Return the four dimension vector \f$[A,B,C,D]^T\f$
    corresponding to the plane parameters.

    \sa getABCD()
  */
  inline vpColVector abcd() const {
    vpColVector n(4);
    n[0]=A;
    n[1]=B;
    n[2]=C;
    n[3]=D;
    
    return n;
  }

  vpColVector getNormal() const;
  void getNormal(vpColVector &n) const;

  friend VISP_EXPORT std::ostream& operator<< (std::ostream& os, vpPlane& p);

  // Operation with  Plane
  void projectionPointOnPlan(const vpPoint& P, vpPoint& Pproj) const ;

  double rayIntersection(const vpPoint &M0,
			 const vpPoint &M1,
			 vpColVector &H )const ;

  double getIntersection(const vpColVector &M1,vpColVector &H )const ;
  void changeFrame(const vpHomogeneousMatrix &cMo);

} ;



#endif
