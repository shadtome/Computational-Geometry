#ifndef DCCONVEX_H
#define DCCONVEX_H

#include "Polygon.h"
#include "ConvexUnion.h"

//-----------------------------------------------------------------------------------
//Convex Hull Divide and Conquer method
Polygon ConvexHull_DAC(Points &points)
{
  if(points.size()==1)            // If a single point, then it is a convex hull of a single point
  {
    Polygon one_point;
    one_point.Vertices=points;
    return one_point;
  }

  //First lets order the points from left to right, so that the convex hulls are disjoint
  LexMergeSort(points);

  Points pointsA;  //Polygon A  for the first half of the Points
  //pointsA.reserve(points.size()/2);
  Points pointsB;  // Polygon B for the second half of the points
  //pointsB.reserve(points.size()-points.size()/2);

  for (int k=0; k< (int)points.size()/2; ++k)
  {
    pointsA.push_back(points[k]);               // input the first half of the points in to A
  }

  for(int k=(int)(points.size()/2); k<points.size(); ++k)
  {
    pointsB.push_back(points[k]);               //INput the last laft in to B
  }

  Polygon PolyA = ConvexHull_DAC(pointsA); // Continuing breaking apart by halfs and then build them up agian by constructing convex hulls of them
  Polygon PolyB = ConvexHull_DAC(pointsB);



  Polygon result = Convex_Union(PolyA, PolyB);
  return result;
}




#endif
