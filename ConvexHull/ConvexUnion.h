#ifndef CONVEXUNION_H
#define CONVEXUNION_H


#include "Polygon.h"



//------------------------------------------------------------------------------
// Now lets find the convex hull for the union of two disjoint convex polygons that are already ordered

Polygon Convex_Union(Polygon &poly1, Polygon &poly2)
{
  Points* Vertices[2]={ &poly1.Vertices, &poly2.Vertices};

  int First_poly;  //This is the index for Vertices array of pointers, to make sure we pick the first polygon to have more then 1 point
                  //Check for which Polygon has more points then 1

  //We need to go through some specific cases and choose which of the polygons is more left then the other
  if(Vertices[0]->size()>1 || Vertices[1]->size()>1)          //Checks if at least of of the polygons has size >1
  {
    if(Vertices[0]->size()>1 && Vertices[1]->size()>1)        // see if both have size >1
    {
      if(Lexo_Order((*Vertices[0])[0],(*Vertices[1])[0]))     //Check which polygon is the most left
      {
        First_poly=0;                                         // Poly1<Poly2
      }
      else
      {
        First_poly=1;                                         //Poly2<Poly1
      }
    }
    else                                                  //Pick the one that has size greater then one, since the other one is of size 1
    {
      if(Vertices[0]->size()>1)
      {
        First_poly=0;                                     //Poly1 has more then 1 point, while poly2 does not
      }
      if(Vertices[1]->size()>1)
      {
        First_poly=1;                                     // POly2 has more then 1 point, while poly 1 does not
      }
    }
  }
  else                                                  //This is the cases when both have size one, so make the convex hull just be the two vertices, but we need to order it from left to right
  {
    if(Lexo_Order((*Vertices[0])[0],(*Vertices[1])[0]))         //If both are of size 1, construct the convex polygon of two points, but ordering it from left to right
    {
      Points verts={{(*Vertices[0])[0]},{(*Vertices[1])[0]}};
      return Polygon(verts);
    }
    else
    {
      Points verts = {{(*Vertices[1])[0]}, {(*Vertices[0])[0]}};
      return Polygon(verts);
    }
  }

  //THis is where we go through the algorithm by slowly putting the vertices together in clockwise order to find the convex union of the union

  // Make enough room for all the vertices
  std::vector<float> ConvUnion[poly1.Vertices.size()+poly2.Vertices.size()]; // the resulting list of vertices that will make the convex polygon
  ConvUnion[0]= (*Vertices[First_poly])[0];
  ConvUnion[1]= (*Vertices[First_poly])[1];

  int flip;          //This will help us flip between the Polygons
  int index[2]={0,0};   //This will hold which index we are at for each polygon

  if(First_poly==0)
  {
    index[0]=2;
    index[1]=0;     // We inputted the first two points of poly1
    flip =1;        // this tells us we will check the second polygon first in the first step of the algorithm
  }
  else
  {
    index[0]=0;
    index[1]=2;     //we inputted the first two points of poly2
    flip = 0;       // this tells us we will check the first polygon first in the first step of the algorithm
  }

  Points deleted;   //This is where we will put the points that are deleted and ignored, we will check at the end if we need to add these

  int j=1;  // Which index of the list ConvUnion we are putting the next vertex in to.

  // Go through each polygon, switching between and adding the next point in to the new list of vertices and delete the one behind it if it makes a left turn
  // Untill we go through all of the vertices
  while(index[0] < poly1.Vertices.size() || index[1] < poly2.Vertices.size())
  {
    bool did_delete=false;                        // tell if we deleted vertices, which means, don't flip
    j += 1;
    ConvUnion[j]= (*Vertices[flip])[index[flip]]; // plug in the vertex for poly in to the jth spot
    index[flip] += 1;                             // increment the index for this polygon

    if(j>1)
    {
      while(Side_of_line(ConvUnion[j-2],ConvUnion[j-1],ConvUnion[j])==LEFT ) // Check if the three points are turn left, which is what we dont want
      {
        did_delete=true;              // if deleted, we wont swich the flip, but continue on
        deleted.push_back(ConvUnion[j-1]); // Add the deleted one to this list that we will check in the end
        ConvUnion[j-1]=ConvUnion[j]; // delate the middle point out of these three
        j -=1;                       // go back on which vertex we want to put in, since we deleted one

        if(j<=1)
          break;                    // if we go back to 2 elements, break out of this loop
      }
      if(did_delete==false)
      {
        flip = (flip+1) %2;                           // change the flip so we can check the other polygon
      }
      if(index[0]==poly1.Vertices.size())   //if we finished this polygon, just stay on the other polygon till the end
      {
        flip = 1;
      }
      if(index[1] == poly2.Vertices.size())
      {
        flip =0;
      }
    }
  }

//Now lets check the deleted ones, so see if we need to add them to it
for(int k=0; k<deleted.size(); ++k)
{

  if(Side_of_line(ConvUnion[j],deleted[k],ConvUnion[0])==RIGHT)   // Check if the new point is inside of the convex hull or outside of it
  {
    ConvUnion[j+1]=deleted[k]; // Add the deleted one
    j += 1;                   // Increment the j
  }
}

  //Put the results together
  Polygon result;
  for (int k=0; k<j+1; ++k)
  {
    result.Vertices.push_back(ConvUnion[k]);
  }
  return result;
}


#endif
