#ifndef POINT_H
#define POINT_H

/*
*Contains the x and y coordinates of the point in R^2
*Also, has relational operators based on the lexographical ordering (x,y)< (z,w) iff y>w or y=b and x<z
*/



class Point2
{
public:
  float x;
  float y;

  //Methods
  float operator[](int i);
  bool operator<(const Point2 point)const ;   // All the relation here is based on LexoGraphic ordering with respect to biggest y
  bool operator<=(const Point2 point)const;   // meaning (x,y)<(a,b) iff y>b or y=b and x<a
  bool operator>(const Point2 point)const;
  bool operator>=(const Point2 point)const;
  bool operator==(const Point2 point)const;
};



#endif
