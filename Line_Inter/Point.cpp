#include "Point.h"


float Point2::operator[](int i)
{
  if(i==0)
  {
    return x;
  }
  else
  {
    return y;
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
