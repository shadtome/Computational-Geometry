#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <map>
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
  Line_Segment(){};
                                    //Default constructor
  //Methods for this class
  //Relation operators
  bool operator<( const Line_Segment &line)const ;       //Overload the relational operators
  bool operator>( const Line_Segment &line)const ;
  bool operator==(const Line_Segment &line)const ;

  //Test Intersection
  /*Intersection function
  * Takes in another line segment and checks the projections on to the
  * x-axis and y-axis and see if those intersect , by look at relations of the endpoints
  */
  bool Intersection(const Line_Segment &other);


};


template<>
struct std::less <Line_Segment>   //compare class for input in to the std::map
{
public:
  constexpr bool operator()( const Line_Segment &line1,const Line_Segment &line2)const
  {
    return line1<line2;
  }
};

#endif
