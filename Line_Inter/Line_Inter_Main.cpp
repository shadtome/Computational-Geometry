#include <iostream>
#include "BST.h"
#include "LineSegment.h"
#include "lineinterAlg.h"




int main()
{
  std::vector<Line_Segment> lines;
  lines.push_back(Line_Segment({1.23,10.1},{-1.30,7.0}));
  lines.push_back(Line_Segment({4.21,-3.5},{5.6,-14.0}));
  lines.push_back(Line_Segment({10.4,2.5},{1.3,3.5}));
  lines.push_back(Line_Segment({-5.4,2.1},{6.702,30.41}));






  std::map<Point2,Intersection_Point> inter=Find_Intersection(lines);
  std::cout << inter.size()<<std::endl;
  for(auto k=inter.begin(); k!=inter.end(); ++k)
  {
    std::cout << k->first.x << "::"<<k->first.y<<std::endl;
  }








  return 0;
}
