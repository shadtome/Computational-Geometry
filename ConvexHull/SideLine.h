#ifndef SIDEOFLINE_H
#define SIDEOFLINE_H

//----------------------------------------------------------
enum Side
{
  LEFT=1,
  RIGHT=0,
  COLINEAR=1
};


//Determines which side the point R is with respect to the line segment PQ
Side Side_of_line(std::vector<float> P,std::vector<float> Q,std::vector<float> R)
{
  float result=(Q[0]*R[1]-Q[1]*R[0])-(P[0]*R[1]-P[1]*R[0])+(P[0]*Q[1]-P[1]*Q[0]);

  if(result>0)
    return LEFT; //This means that R is on the left side of the line segment from P to Q

  if(result<0)
    return RIGHT; //This means that R is on the right side of the line Segment from P to Q

  return COLINEAR; // meaning they are on the same line
}




#endif
