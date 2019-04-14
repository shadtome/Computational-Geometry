#include "LineSegment.h"
#include "LineInterMath.h"
#include <iostream>
#include <cmath>

//Source code for the class LineSegment


Line_Segment::Line_Segment(Point2 point_1, Point2 point_2)
{
  if (point_1>point_2)                          //Make sure to reorder the line segment, so the first endpoint is the most left up endpoint
  {
    this->End_Points.push_back(point_2);
    this->End_Points.push_back(point_1);
  }
  else if(point_1<point_2)
  {
    this->End_Points.push_back(point_1);
    this->End_Points.push_back(point_2);
  }
  else  //This is when both points are the same, so it is a single point.
  {
    this->End_Points.push_back(point_1);
    this->End_Points.push_back(point_2);
  }

  //Set the Sweep_int to be inalized as the upper point, since it will be first point
  // that will intersect the sweep line
  this->sweep_int.first=this->End_Points[0];
  this->sweep_int.second=UPPER;

}
//we are only ordering based on the sweep line, so we just need to check horizontal ordering
//from left to right
/*
* We also need to handle the situation when we are comparing two line segments
* with the same sweep point,(intersection point between them) and change the ordering after
* we past this event point.
*/

//< operator
bool Line_Segment::operator<(const Line_Segment &line)const
{
  //This is when we have two line segments with the same top end point,
  //The way we find the ordering with respect to the sweep line is through their slopes
  // i.e.
  /*
              * * * * *  l_4
      l_1   * * *
          *   *   *     l_3
        *     *     *
              l_2
    l_1<l_2<l_3<l_4, where slope(l_1)>0, slope(l_2)=undefined, slope(l_3)<0, slope(l_4)=0
                    and where angle(l_1)=pi/4, angle(l_2)=pi/2, angle(l_3)=3pi/4, angle(l_4)=pi
    Should I avoid using cos^{-1} and norm to do this? since the easiest way to do this is to
    find the angle of the vector starting at the center with respect to the left (-1,0),
    and hence the ordering is with respect to the angles (0,pi].
    The line segment can never be pointing to the left from the center, since it will contradict the ordering of the
    line end points.
  */


  if(this->End_Points[0]==line.End_Points[0])
  {
    //Vectors for *this and line.
    Point2 vector_1(this->End_Points[1].x-this->End_Points[0].x,this->End_Points[1].y-this->End_Points[0].y);
    Point2 vector_2(line.End_Points[1].x-line.End_Points[0].x,line.End_Points[1].y-line.End_Points[0].y);

    //Next, compute the angles with respect to the vector (-1,0)
    float angle_1=std::acos(-vector_1.x/Norm(vector_1));
    float angle_2=std::acos(-vector_2.x/Norm(vector_2));

    if(angle_1<angle_2)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  //This is the ordinary relation, when the top end point do not equal to each other

  if(std::abs(this->sweep_int.first.x-line.sweep_int.first.x)<0.0001)
  {
    if(this->End_Points[(int)this->sweep_int.second].x<line.End_Points[(int)line.sweep_int.second].x)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else if(this->sweep_int.first.x<line.sweep_int.first.x)
  {
    return true;
  }
  //otherwise
  return false;
}

//<= operator
bool Line_Segment::operator<=(const Line_Segment &line)const
{
  if(*this<line)
  {
    return true;
  }
  else if(*this==line)
  {
    return true;
  }
  else
  {
    return false;
  }
}


bool Line_Segment::operator>(const Line_Segment &line)const
{
  //this is the situation where the top endpoints are the same
  if(this->End_Points[0]==line.End_Points[0])
  {
    //Vectors for *this and line.
    Point2 vector_1(this->End_Points[1].x-this->End_Points[0].x,this->End_Points[1].y-this->End_Points[0].y);
    Point2 vector_2(line.End_Points[1].x-line.End_Points[0].x,line.End_Points[1].y-line.End_Points[0].y);

    //Next, compute the angles with respect to the vector (-1,0)
    float angle_1=std::acos(-vector_1.x/Norm(vector_1));
    float angle_2=std::acos(-vector_2.x/Norm(vector_2));

    if(angle_1>angle_2)
    {
      return true;
    }
    else
    {
      return false;
    }
  }


  //regular situation

  if(std::abs(this->sweep_int.first.x-line.sweep_int.first.x)<0.0001)
  {
    if(this->End_Points[(int)this->sweep_int.second].x>line.End_Points[(int)line.sweep_int.second].x)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else if(this->sweep_int.first.x>line.sweep_int.first.x)
  {
    return true;
  }
  //Otherwise
  return false;
}

//>= operator
bool Line_Segment::operator>=(const Line_Segment &line)const
{
  if(*this>line)
  {
    return true;
  }
  else if(*this==line)
  {
    return true;
  }
  else
  {
    return false;
  }
}


bool Line_Segment::operator==(const Line_Segment &line)const
{
  if(this->End_Points[0]==line.End_Points[0] && this->End_Points[1]==line.End_Points[1] && std::abs(this->sweep_int.first.x-line.sweep_int.first.x)<0.0001)
  {

    return true;
  }
  else
  {
    return false;
  }
}

bool Line_Segment::operator!=(const Line_Segment &line)const
{
  return !(*this==line);
}


//----------------------------------------------------
//Check intersection operator

std::pair<bool,Point2> Line_Segment::Intersection(const Line_Segment &other)const
{
  //To find intersection between two lines, we will project on to the x and y axis and check if those lines intersect.
  // if both projections are intersecting on the x and the y axis then they are intersecting in the plane
  std::vector<float> x_line1_proj;
  std::vector<float> x_line2_proj;
  std::vector<float> y_line1_proj;
  std::vector<float> y_line2_proj;

  x_line1_proj.push_back(this->End_Points[0].x);
  x_line1_proj.push_back(this->End_Points[1].x);
  std::sort(x_line1_proj.begin(),x_line1_proj.end());

  x_line2_proj.push_back(other.End_Points[0].x);
  x_line2_proj.push_back(other.End_Points[1].x);
  std::sort(x_line2_proj.begin(),x_line2_proj.end());

  y_line1_proj.push_back(this->End_Points[0].y);
  y_line1_proj.push_back(this->End_Points[1].y);
  std::sort(y_line1_proj.begin(),y_line1_proj.end());

  y_line2_proj.push_back(other.End_Points[0].y);
  y_line2_proj.push_back(other.End_Points[1].y);
  std::sort(y_line2_proj.begin(),y_line2_proj.end());

  //This check if the x_line_1_proj[1] is between x_line_proj[0] and x_line_proj[1]
  float x_int_1=(x_line1_proj[1]-x_line2_proj[0])*(x_line1_proj[1]-x_line2_proj[1]);
  //This check if the x_line_2_proj[1] is between x_line_proj[0] and x_line_proj[1]
  float x_int_2=(x_line2_proj[1]-x_line1_proj[0])*(x_line2_proj[1]-x_line1_proj[1]);
  //same for the y
  float y_int_1=(y_line1_proj[1]-y_line2_proj[0])*(y_line1_proj[1]-y_line2_proj[1]);
  float y_int_2=(y_line2_proj[1]-y_line1_proj[0])*(y_line2_proj[1]-y_line1_proj[1]);


  if((x_int_1*x_int_2<=0) && (y_int_1*y_int_2<=0))    //This means we do have a intersection (prove this)
  {
    //Slopes of the lines
    if(this->End_Points[0].x!=this->End_Points[1].x)
    {
      float m_1=(this->End_Points[0].y-this->End_Points[1].y)/(this->End_Points[0].x-this->End_Points[1].x);

      if(other.End_Points[0].x!=other.End_Points[1].x)
      {
        float m_2=(other.End_Points[0].y-other.End_Points[1].y)/(other.End_Points[0].x-other.End_Points[1].x);

        //x coordinate of the intersection
        float x;
        float y; //y-coordinate
        if(m_1!=m_2)
        {
          x=(this->End_Points[0].y-other.End_Points[0].y+m_2*other.End_Points[0].x-m_1*this->End_Points[0].x)/(m_2-m_1);
          //y coordinate of the intersection
          y=m_1*(x-this->End_Points[0].x)+this->End_Points[0].y;
        }
        else
        {
          //They can not be intersecting if they are unique
          return std::pair<bool,Point2>(false,Point2(0.0,0.0));
        }
        //We need to make sure the points we found are on the line segment
        //since this is only accounting for if its on the entire line
        Point2 point(x,y);

        return std::pair<bool,Point2>(On_Line(point)&& other.On_Line(point),point);
      }
      else
      {
        float x=other.End_Points[0].x;
        float y=m_1*(x-this->End_Points[0].x)+this->End_Points[0].y;
        Point2 point(x,y);

        return std::pair<bool,Point2>(On_Line(point) && other.On_Line(point),point);
      }
    }
    else
    {
      //First, lets assume the other is not horizontal as well.
      if(other.End_Points[0].x!=other.End_Points[1].x)
      {
        //slope of other line
        float m=(other.End_Points[0].y-other.End_Points[1].y)/(other.End_Points[0].x-other.End_Points[1].x);
        //These represent the intersection line.
        float x;
        float y;
        //since "this" line is vertical, all we need to do is insert the x-coordinate into the equation of the line for other line
        //to get the intersection point.
        x=this->End_Points[0].x;
        y=m*(x-other.End_Points[0].x)+other.End_Points[0].y;

        Point2 point(x,y);

        return std::pair<bool,Point2>(On_Line(point)&&other.On_Line(point),point);
      }
      return std::pair<bool,Point2>(false,Point2(0.0,0.0));
    }

  }
  else    //Other wise they are not intersecting
  {
    return std::pair<bool,Point2>(false,Point2(0.0,0.0));
  }

}


//--------------------------------------------------------------
//Checks if point is on line function
bool Line_Segment::On_Line(const Point2 &p)const
{
  if(this->End_Points[0].x!=this->End_Points[1].x)
  {
    float m=(this->End_Points[0].y-this->End_Points[1].y)/(this->End_Points[0].x-this->End_Points[1].x);
    if(std::abs(m*(p.x-this->End_Points[0].x)+this->End_Points[0].y-p.y)<0.0001)
    {
      //Next, we need to make sure it is between the perpindular lines at the end points
      if(m!=0)
      {
        float perp_m=-1/m;
        if(perp_m*(p.x-this->End_Points[0].x)+this->End_Points[0].y>=p.y && perp_m*(p.x-this->End_Points[1].x)+this->End_Points[1].y<=p.y)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        if(this->End_Points[0].x<=p.x && this->End_Points[1].x>=p.x)
        {
          return true;
        }
        else
        {
          return false;
        }
      }
    }
    else
    {
      return false;
    }
  }
  else
  {

    if(this->End_Points[0].y>=p.y && this->End_Points[1].y<=p.y && std::abs(p.x-this->End_Points[0].x)<0.0001)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}



//Update sweep line function
void Line_Segment::Update_sweep(const Point2 &sweep, Which_Side side)
{
  if(this->End_Points[0].x!=this->End_Points[1].x)
  {
    float m=(this->End_Points[0].y-this->End_Points[1].y)/(this->End_Points[0].x-this->End_Points[1].x);
    if(m!=0)
    {
      this->sweep_int.first.x=(sweep.y-this->End_Points[0].y)/m+this->End_Points[0].x;
      this->sweep_int.first.y=sweep.y;
    }
    //Otherwise, no need to update as the line is horizontal
  }
  //Otherwise, no need to update the sweep_int, as the x part is always the same.

  //Now update if it is UPPER or LOWER
  this->sweep_int.second=side;
}

//--------------------------

//--------------------------
//Find the x value

float Line_Segment::Find_x(const float &y) const
{
  if(this->End_Points[0].x!=this->End_Points[1].x)
  {
    float m=(this->End_Points[0].y-this->End_Points[1].y)/(this->End_Points[0].x-this->End_Points[1].x);
    if(m!=0)
    {
      return (y-this->End_Points[0].y)/m+this->End_Points[0].x;
    }
    else
    {
      //this means they are on the same line and we will ignore this for now, as this means they
      //a infinite number of points on their intersection.
    }
  }
  else
  {
    return this->End_Points[0].x;
  }
  return 0;
}
