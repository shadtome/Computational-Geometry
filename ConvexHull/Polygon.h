#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "SideLine.h"
#include "Mergesort.h"

class Polygon
{
public:
  //Vertices of the polygon // just use this for now, I can make it better later if I need this, just to make it easy to test
  Points Vertices; // vertices of a polygon in clockwise order
  //Default Constructor
  Polygon();
  //Constructor: finds the polygonal convex hull that contains the points
  Polygon(Points &points);
  // Size of the set of vertices to the polygons
  int size();
  //Convex Hull for the Points
  void ConvexHull(Points &points);
};

Polygon::Polygon()
{}

Polygon::Polygon(Points &points)
{
  this->Vertices=points;
}



//ConvexHull algorithm using a iterate method of slowly constructing the List
//THis inputs any collection of points
//OUtputs a Polygon, which is convex
void Polygon::ConvexHull(Points &points)
{
  //Sort the points
  LexMergeSort(points);


  //Temporary list of points
  std::vector<float> List_Upper[points.size()];
  std::vector<float> List_Lower[points.size()];

  //Put in the first two points of the sorted list of points;

  List_Upper[0]=points[0];
  List_Upper[1]=points[1];

  //Current locaiton in upper or lower index where we are changing the points
  unsigned int isize_U=1;

  for (int k=2; k<points.size(); ++k)
  {
    //Append the p_kth point in to the List_Upper
    isize_U=isize_U+1;
    List_Upper[isize_U]=points[k];


    if(isize_U>1)
    {
      while(Side_of_line(List_Upper[isize_U-2],List_Upper[isize_U-1],List_Upper[isize_U])==LEFT)
      {
        //Delete the middle of the last three points, and move the list back to and the isize back by 1
        //if the last three points do not curve right
        List_Upper[isize_U-1]=List_Upper[isize_U];
        isize_U=isize_U-1;
        if(isize_U<=1)
        {
          break;
        }
      }
    }
  }
  //Now for the List_Lower part
  int size=points.size();
  List_Lower[0]=points[size-1];
  List_Lower[1]=points[size-2];
  int isize_L=1;

  for (int k=2; k<size-1; ++k)
  {
    //Append the p_n-kth point in to the List_low
    isize_L=isize_L+1;
    List_Lower[isize_L]=points[size-1-k];

    if(isize_L>1)
    {
      while(Side_of_line(List_Lower[isize_L-2],List_Lower[isize_L-1],List_Lower[isize_L])==LEFT)
      {
        //Delete the middle of the last three points, and move the list back to and the isize back by 1
        //if the last three points dont curve right
        List_Lower[isize_L-1]=List_Lower[isize_L];
        isize_L=isize_L-1;
        if(isize_L<=1)
        {
          break;
        }
      }
    }

  }

  //Finished with completeing Upper and Lower vertices, now we need to put them all in order in to the Vertices
  Points Result_Vertices;
  for(int k=0; k<isize_U+1; ++k)
  {
    Result_Vertices.push_back(List_Upper[k]);
  }
  //Put in the LIst_Lower but ignore the first and lasst one, since those are already in it
  for(int k=1; k<isize_L; ++k)
  {
    Result_Vertices.push_back(List_Lower[k]);
  }
  this->Vertices=Result_Vertices;
}



int Polygon::size()
{
  return this->Vertices.size();
}


#endif
