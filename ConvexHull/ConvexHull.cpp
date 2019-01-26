

#include <iostream>
#include <vector>
#include "Polygon.h"
#include "ConvexUnion.h"
#include "DivideConquerConvex.h"



int main()
{
  Points Test={{1,4}, {7,1}, {4,5}, {4,3}, {2,2}, {5,1}, {6,6},{1,7},{6,4}};

  Polygon result = ConvexHull_DAC(Test);
  for(int k=0; k<result.size(); ++k)
  {
    std::cout <<"::"<< result.Vertices[k][0]<< "::" << result.Vertices[k][1] << std::endl;
  }
  return 0;
}
