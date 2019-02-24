#include "linetinterAlg.h"





std::map<Point2,Intersection_Point> Find_Intersection(std::vector<Line_Segment> lines)
{
  //Initilize the map that will contain the points and the line_segments
  std::map<Point2,Line_Segment> result;

  /* First, define the event queue
  * This holds the points in order as the pivot points
  * and holds the line_segments that have this point as its upper endpoint
  */
  Queue Q;

  /* Second, define the status BST
  * This holds a ordered tree of all the line line segments
  * that intersect the sweep line (y=some constant number)
  * So if a line segment does not intersect the sweep line, it
  * must be deleted.  On the other hand, a new line segment that intersects
  * the sweep line must be added in
  */
  Status T;

  /*Next, lets insert all the relevent points in to Q
  * i.e. the end points of the line line_segments
  * But only store the line segment witht the point
  * iff it is the largest point in the line segment
  */
  for(unsigned int k=0; k<lines.size(); ++k)
  {
    Q.Insert(lines[k].End_Points[0],lines[k]);  //Insert the pivot point as the upper left most point, and the connected line segment
    Q.Insert(lines[k].End_Points[1]);           //Just insert the pivot point, with no data added to it
  }

  while(Q.Is_Empty()!=true)
  {
    //Determine the new event point
    //to do this, we need to find the ordered list of events in Q
    std::vector<Queue_Node*> ordered_events=Q.Node_list(Q.Root_Node);

    //Event point, which is the first elemnt of this list
    Queue_Node* event_point=ordered_events[0];

    //Insertection of line_segments that intersect the event point
    std::vector<Line_Segment> int_lines;

    //Next, process this event point
    //This is the meat of the algo
    int_lines=HandleEventPoint(Queue_Node* event_point);

    //Insert the line_segments in to the result map.
    for(unsigned int k=0; k<int_lines.size(); ++k)
    {
      result[event_point->Pivot]=int_lines[k];
    }

  }

  //Now we are done, so we can return the result
  return result;

}





//-----------------------------------------------------
//Handle event point function
std::vector<Line_Segment> HandleEventPoint(Queue_Node* p,Queue Q, Status T)
{
  //This is the collection of line_segments that contain the point p as a upper point
  std::vector<Line_Segment> U_p;

  //Input the data in to U_p from p.
  for(auto it=p->data.begin(); it != p->data.end(); ++it)
  {
    U_p.push_back(it->second);
  }
  //This is the collection of line_segments in T that contain p as a lower end point
  std::vector<Line_Segment> L_p;

  //This is the collection of line segments in T that contain p in the interior
  std::vector<Line_Segment> C_p;

  //Next, we need to process through the status T for all the line segments that contain the point p
  // and put the correct line segments in to L_p and C_p.

  //Do the iterator stuff to go through T and find them and insert in to L_p, C_p.

}


//-----------------------------------------------------
//Find New Event point function
