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
  UPPER=0,    //so we can also use the fact this is int (0)
  LOWER=1    // so we can also use the fact this is int (1)
};

class Line_Segment
{
public:
  std::vector<Point2> End_Points;    // End points of the line segment:  End_Points[0] is the upper left most point.
  std::pair<Point2,Which_Side> sweep_int;                 //Intersection point to the sweep line (changes at event points only)

  //Constructor
  Line_Segment(Point2 point_1, Point2 point_2);
  //Default constructor
  Line_Segment(){};

  //Copy Constructor
  //Line_Segment(const Line_Segment &other);

  //Copy Assignment Operator
  //Line_Segment& operator=(const Line_Segment &other);



  //Methods for this class
  //Relation operators

  /*We will order the line_segments based on the sweep_int,
  * which is ordered left to right
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
  bool On_Line(const Point2 &p)const;

  /* Updates the Sweep_int when ever the sweep line changes to a new event point.
  * This just takes the sweep line and plugs the y-component in to the line equation
  * to obtain the x-coordinate.
  */
  void Update_sweep(const Point2 &sweep);

  /*
  * Find the x on this line corresponding to the y-value.
  */
  float Find_x(const float &y)const;

};

/*This is the relation between line segments in the std::map
* This is using lexographic ordering with respect to the endpoints,
* different then the relation defined in the class Line_segment.
* Those are used for relations with respect to a sweep line.
* This needs to distinguish two distinct lines.
*/
template<>
struct std::less <Line_Segment>   //compare class for input in to the std::map
{
public:
  constexpr bool operator()( const Line_Segment &line1,const Line_Segment &line2)const
  {
    if(line1.End_Points[0]<line2.End_Points[0])
    {
      return true;
    }
    else if(line1.End_Points[0]==line2.End_Points[0] && line1.End_Points[1]<line2.End_Points[1])
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};

#endif
