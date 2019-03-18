#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include <map>
#include <vector>
#include "Point.h"


/*
*Contains the endpoints of the LineSegment
* We are going to order the Line_Segments based on their intersection point with the sweep line.
* So we store this intersection data, and only change it at event points (crossing intersection points,
* upper points of line segments and lower points of line segments
*/
enum Which_Side
{
  UPPER=false,    //so we can also use the fact this is int (0)
  LOWER=true    // so we can also use the fact this is int (1)
};

class Line_Segment
{
public:
  std::vector<Point2> End_Points;    // End points of the line segment:  End_Points[0] is the upper left most point.
  std::pair<Point2,Which_Side> sweep_int;                 //Intersection point to the sweep line (changes at event points only)

  //Constructor
  Line_Segment(Point2 point_1, Point2 point_2);
  Line_Segment(){};
                                    //Default constructor
  //Methods for this class
  //Relation operators

  /*We will order the line_segments based on the sweep_int,
  * which is ordered left to right, lexographically
  */
  bool operator<( const Line_Segment &line)const ;       //Overload the relational operators
  bool operator<=(const Line_Segment &line)const;
  bool operator>( const Line_Segment &line)const ;
  bool operator>=(const Line_Segment &line)const;
  bool operator==(const Line_Segment &line)const ;
  bool operator!=(const Line_Segment &line)const ;

  //Test Intersection
  /*Intersection function
  * Takes in another line segment and checks the projections on to the
  * x-axis and y-axis and see if those intersect , by look at relations of the endpoints
  */
  std::pair<bool,Point2> Intersection(const Line_Segment &other)const;

  /* Checks if point is on the line
  * Finds the equation of the line and evaluates the point (maybe I should just keep the slope saved?)
  */
  bool On_Line(Point2 &p);


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
