
#include "Point.h"
#include <iostream>
#include <stdexcept>


float Point2::operator[](int i)
{
  if(i==0)
  {
    return x;
  }
  else if(i==1)
  {
    return y;
  }
  else
  {
    throw std::runtime_error("Point2::index out of range");
  }

}


bool Point2::operator<(const Point2 point)const
{
  if(this->y>point.y)
  {
    return true;
  }

  if(this->y==point.y)
  {
    if(this->x<point.x)
    {
      return true;
    }
    else
    {
        return false;
    }
  }
  return false;
}

bool Point2::operator<=(const Point2 point)const
{
  if(this->y>point.y)
  {
    return true;
  }

  if(this->y==point.y)
  {
    if(this->x<=point.x)
    {
      return true;
    }
    else
    {
        return false;
    }
  }
  return false;
}

bool Point2::operator>(const Point2 point)const
{
  if(this->y<point.y)
  {
    return true;
  }

  if(this->y==point.y)
  {
    if(this->x>point.x)
    {
      return true;
    }
    else
    {
        return false;
    }
  }
  return false;
}

bool Point2::operator>=(const Point2 point)const
{
  if(this->y<point.y)
  {
    return true;
  }

  if(this->y==point.y)
  {
    if(this->x>=point.x)
    {
      return true;
    }
    else
    {
        return false;
    }
  }
  return false;
}

bool Point2::operator==(const Point2 point)const
{
  if(point.x==this->x && point.y==this->y)
  {
    return true;
  }
  return false;
}

bool Point2::operator!=(const Point2 point)const
{
  return !(*this==point);
}
