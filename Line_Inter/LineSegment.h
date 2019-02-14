#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <vector>
#include "Point.h"


/*
*Contains the endpoints of the LineSegment, and does relational operations based on the lexographical ordering with respect to
* (x,y)< (z,w) iff y>w or y=w and x<z.
*/

class Line_Segment
{
public:
  std::vector<Point2> End_Points;  // End points of the line segment:  End_Points[0] is the upper left most point.

  //Constructor
  Line_Segment(Point2 point_1, Point2 point_2);
  Line_Segment(){};                                     //Default constructor
  //Methods for this class
  bool operator<( const Line_Segment &line)const ;       //Overload the relational operators
  bool operator>( const Line_Segment &line)const ;
  bool operator==(const Line_Segment &line)const ;


};

class LineSegCompare      //compare class for input in to the std::map
{
public:
  bool operator()( const Line_Segment &line1,const Line_Segment &line2)const;
};

#endif
