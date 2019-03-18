#ifndef LINEINTER_MATH_H
#define LINEINTER_MATH_H

#include "Point.h"

//Takes three row vectors and out puts the determinant of
/*  a_1 a_2 1
*   b_1 b_2 1
*   c_1 c_2 1
*/
inline float Determinent2(Point2 &A,Point2 &B,Point2 &C)
{
  return B[0]*C[1]-B[1]*C[0]-(A[0]*C[1]-A[1]*C[0])+A[0]*B[1]-B[0]*A[1];
}


inline bool Collinear(Point2 &A,Point2 &B,Point2 &C)
{
  float det=Determinent2(A,B,C);
  if(det!=0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}





#endif
