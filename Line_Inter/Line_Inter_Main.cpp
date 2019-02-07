#include <iostream>
#include "BST.h"
#include "LineSegment.h"





int main()
{
  Line_Segment line_1({2.0,1.0},{4.0,2.0});
  Line_Segment line_2({2.0,3.0},{1.0,2.0});

  BST<Line_Segment,Point2, LineSegCompare> Queue;

  Queue.Insert(line_1.End_Points[0],line_1);
  Queue.Insert(line_2.End_Points[0],line_2);

  //std::cout << Queue.Root_Node.data[0].End_Points[0].x << std:: endl;
  //std::cout << Queue.Root_Node.Left_Node->data[0].End_Points[0].x << std:: endl;

  for(auto key=Queue.Root_Node.data.begin(); key!= Queue.Root_Node.data.end(); ++key)
  {
    std::cout << key->second.End_Points[0].x << std::endl;
  }


  return 0;
}
