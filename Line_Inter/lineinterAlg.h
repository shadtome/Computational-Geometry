#ifndef LINE_INTERSECTION_ALGORITHM_H
#define LINE_INTERSECTION_ALGORITHM_H

#include <map>
#include <vector>
#include "LineSegment.h"
#include "BST.h"


//typedef
typedef BST<Line_Segment,Point2>  Queue;
typedef BST_Node<Line_Segment,Point2> Queue_Node;
typedef BST<Line_Segment,Line_Segment> Status;
typedef BST_Node<Line_Segment,Line_Segment> Status_Node;



struct Intersection_Point
{
  //The single point at this intersection point
  Point2 point;

  //vector list of all the line segments that intersect this point
  std::vector<Line_Segment> lines;

  //default Constructor
  Intersection_Point(){};

  //Constructor
  Intersection_Point(Point2 &point,std::vector<Line_Segment> lines): point(point),lines(lines){};

};



class LineIntersections
{
  typedef std::map<Point2,Intersection_Point>::iterator iterator;
  typedef const std::map<Point2,Intersection_Point>::const_iterator const_iterator;
public:

  //Constructor
  LineIntersections(std::vector<Line_Segment> lines);

  //Iterators
  iterator begin()
  {
    return intersections.begin();
  }

  iterator end()
  {
    return intersections.end();
  }

  const_iterator cbegin()
  {
    return intersections.cbegin();
  }

  const_iterator cend()
  {
    return intersections.cend();
  }


private:
  /* Collection of intersection points with the corresponding lines
  * that intersect the point
  */
  std::map<Point2,Intersection_Point> intersections;


  /* Finds all the intersection points between all the linesegments in the list
  * Take in a collection of lines in the plane (that are nice meaning no infinite intersections)
  * This algorthim uses two balanced binary search trees for the event queue and status.
  * This algorthim finds the line intersections by following a line sweep downward and check for intersection
  * everytime a event queue is processed.
  * Furthermore, this does not account for infinite number of intersections.
  */
  void Find_Intersection(std::vector<Line_Segment> lines);

  /* Handles event points
  * This function takes in , Queue, Status, and an event point (named Queue_Node*)
  * which holds all the line_segments that have their upper most endpoint as this point
  * this function processes through the main parts of the algorthm
  * It outputs a vector of line segments that intersect the point corresponding to the event point
  */
  void HandleEventPoint(Queue_Node* p,Queue &Q, Status &T);

  /* Find new event points
  * This function takes in two line_segments, one to the left and one to the right
  * and determines if there is a new intersection between them, since they are now neighbors to each other
  *
  */

  void Find_New_Event(Line_Segment &l_1,Line_Segment &l_2, Point2 &point,Queue &Q);

};





#endif
