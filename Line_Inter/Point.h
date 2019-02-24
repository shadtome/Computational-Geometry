#ifndef POINT_H
#define POINT_H

#include <map>

/*
*Contains the x and y coordinates of the point in R^2
*Also, has relational operators based on the lexographical ordering (x,y)< (z,w) iff y>w or y=b and x<z
*/



class Point2
{
public:
  float x;
  float y;

  //Constructors
  //Default constructor
  Point2(){};
  //two points initalized contstructor
  Point2(float x, float y):x(x),y(y){};

  //Methods
  float operator[](int i);                    // takes int between 0 or 1, corresponding to x and y.
  bool operator<(const Point2 point)const ;   // All the relation here is based on LexoGraphic ordering with respect to biggest y
  bool operator<=(const Point2 point)const;   // meaning (x,y)<(a,b) iff y>b or y=b and x<a
  bool operator>(const Point2 point)const;
  bool operator>=(const Point2 point)const;
  bool operator==(const Point2 point)const;
};

//Compare function for std::map
template<>
struct std::less <Point2>   //compare class for input in to the std::map
{
public:
  constexpr bool operator()( const Point2 &point1,const Point2 &point2)const;
};

#endif
