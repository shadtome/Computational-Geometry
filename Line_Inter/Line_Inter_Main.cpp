#include <iostream>
#include "BST.h"
#include "LineSegment.h"
#include "lineinterAlg.h"




int main()
{
  std::vector<Line_Segment> lines;
  lines.push_back(Line_Segment({0.0,0.0},{1.0,1.0}));
  lines.push_back(Line_Segment({0.0,1.0},{1.0,0.0}));
  lines.push_back(Line_Segment({0.0,0.5},{0.5,0.0}));


  /*BST<Line_Segment,Line_Segment> test;
  test.Insert(lines[0]);
  test.Insert(lines[1]);
  Point2 point(5.0,6.0);
  test.Insert(Line_Segment(point,point));*/



  std::map<Point2,Intersection_Point> inter=Find_Intersection(lines);
  std::cout << inter.size()<<std::endl;
  for(auto k=inter.begin(); k!=inter.end(); ++k)
  {
    std::cout << k->first.x << "::"<<k->first.y<<std::endl;
  }



  /*BST<int,int> test;
  test.Insert(0,0);
  test.Insert(1,1);
  test.Insert(2,2);
  test.Insert(3,3);
  test.Insert(4,4);
  test.Insert(5,5);
  test.Insert(6,6);
  test.Insert(7,7);
  test.Insert(8,8);
  test.Insert(9,9);

  //test.Balance(test.Root_Node);

  for(auto k=test.begin(); k!=test.end();++k)
  {
    std::cout << k->pivot<<std::endl;
  }

  test.Delete(8);
  test.Delete(4);
  std::cout << "DELETE 8"<<std::endl;
  for(auto k=test.begin(); k!=test.end();++k)
  {
    std::cout << k->pivot<<std::endl;
  }
*/



  return 0;
}
