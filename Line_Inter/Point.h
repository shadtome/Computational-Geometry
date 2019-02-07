#ifndef POINT_H
#define POINT_H

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
