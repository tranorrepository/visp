/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet Lagadic / IRISA-INRIA Rennes, 2005
 * www  : http://www.irisa.fr/lagadic
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      vpImageTools.cpp
 * Project:   ViSP2
 *
 * Version control
 * ===============
 *
 *  $Id: vpImageTools.cpp,v 1.3 2006-02-07 14:44:27 fspindle Exp $
 *
 * Description
 * ============
 *   various image tools, convolution, etc...
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include<visp/vpImageTools.h>


/*!

  Change the look up table (LUT) of an image. Considering image values
   v in the range [A, B], rescale this values in [newA, newB] by linear
  interpolation.

  - if v \f$ \in \f$ ]-inf, A], set v to newA
  - else if v \f$ \in \f$ [B, inf[ set v to newB
  - else set v to newA + (newB-newA)/(B-A)*(v-A)

  \param A : Low value of the range to consider.
  \param newA : New value to attribute to pixel who's value was A
  \param B : Height value of the range to consider.
  \param newB : New value to attribute to pixel who's value was B

  This method can be used to binarize an image. For an unsigned char image
  (in the range 0-255), thresholding this image at level 128 can be done by:

  \code
  // Binarize image I:
  // - values less than or equal to 128 are set to 0,
  // - values greater than 128 are set to 255
  vpImageTools::changeLUT(I, 128, 0, 128, 255);
  \endcode

*/
void vpImageTools::changeLUT(vpImage<unsigned char>& I,
			     unsigned char A,
			     unsigned char newA,
			     unsigned char B,
			     unsigned char newB)
{
  unsigned char v;
  double factor = (double)(newB-newA)/(double)(B-A);

  for (int i=0 ; i < I.getRows(); i++)
    for (int j=0 ; j < I.getCols(); j++) {
      v = I[i][j];

      if (v <= A)
	I[i][j] = newA;
      else if (v >= B)
	I[i][j] = newB;
      else
	I[i][j] = (unsigned char)(newA + factor*(v-A));
  }
}


/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
