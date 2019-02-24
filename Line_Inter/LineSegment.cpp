#include "LineSegment.h"

//Source code for the class LineSegment


Line_Segment::Line_Segment(Point2 point_1, Point2 point_2)
{
  if (point_1>point_2)                          //Make sure to reorder the line segment, so the first endpoint is the most left up endpoint
  {
    this->End_Points.push_back(point_1);
    this->End_Points.push_back(point_2);
  }
  else
  {
    this->End_Points.push_back(point_2);
    this->End_Points.push_back(point_1);
  }

}

bool Line_Segment::operator<(const Line_Segment &line)const
{
  if(this->End_Points[1] > line.End_Points[1])
  {
    return true;
  }
  if(this->End_Points[1] == line.End_Points[1])
  {
    if(this->End_Points[0]<line.End_Points[0])
    {
      return true;
    }
    else
      return false;
  }
  return false;
}

bool Line_Segment::operator>(const Line_Segment &line)const
{
  if(this->End_Points[1] < line.End_Points[1])
  {
    return true;
  }
  if(this->End_Points[1] == line.End_Points[1])
  {
    if(this->End_Points[0]>line.End_Points[0])
    {
      return true;
    }
    else
      return false;
  }
  return false;
}


bool Line_Segment::operator==(const Line_Segment &line)const
{
  return this->End_Points[0]==line.End_Points[0] && this->End_Points[1]==line.End_Points[1];
}




//Class Compare Methods
constexpr bool std::less<Line_Segment>::operator()( const Line_Segment &line1, const Line_Segment &line2)const
{
  return line1<line2;
}
