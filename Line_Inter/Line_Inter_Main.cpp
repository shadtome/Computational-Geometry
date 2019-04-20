#include <iostream>
#include "BST.h"
#include "LineSegment.h"
#include "lineinterAlg.h"




int main()
{
  std::vector<Line_Segment> lines;
  lines.push_back(Line_Segment({1.0,1.0},{0.0,0.0}));
  lines.push_back(Line_Segment({1.0,0.0},{0.0,1.0}));
  lines.push_back(Line_Segment({0.0,0.5},{1.0,1.0}));
  lines.push_back(Line_Segment({0.5,0.0},{0.0,0.5}));
  lines.push_back(Line_Segment({0.1,0.7},{2.0,1.34}));
  lines.push_back(Line_Segment({0.762,1.3},{0.762,0.4}));
  lines.push_back(Line_Segment({-0.3,0.4523},{2.3,0.4523}));




  LineIntersections test(lines);

  for(auto k=test.begin(); k!=test.end(); ++k)
  {
    std::cout << k->first.x<<k->first.y<<std::endl;
  }








  return 0;
}
