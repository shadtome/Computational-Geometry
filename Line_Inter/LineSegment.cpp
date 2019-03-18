#include "LineSegment.h"
#include <iostream>

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

  if(this->sweep_int.first.x<line.sweep_int.first.x)
  {
    return true;
  }
  else if(this->sweep_int.first.x>line.sweep_int.first.x)
  {
    return false;
  }
  else
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

  if(this->sweep_int.first.x>line.sweep_int.first.x)
  {
    return true;
  }
  else if(this->sweep_int.first.x<line.sweep_int.first.x)
  {
    return false;
  }
  else
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
  if(this->End_Points[0]==line.End_Points[0] && this->End_Points[1]==line.End_Points[1] && this->sweep_int.first.x==line.sweep_int.first.x)
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

  //Now check the numbers
  float x_int=(x_line1_proj[0]-x_line2_proj[0])*(x_line1_proj[1]-x_line2_proj[1]);
  float y_int=(y_line1_proj[0]-y_line2_proj[0])*(y_line1_proj[1]-y_line2_proj[1]);

  if(x_int<=0 && y_int<=0)    //This means we do have a intersection (prove this)
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


        std::cout << "x"<< x <<std::endl;
        std::cout << "y" << y<<std::endl;
        return std::pair<bool,Point2>(true,Point2(x,y));
      }
      else
      {
        float x=other.End_Points[0].x;
        float y=m_1*(x-this->End_Points[0].x)+this->End_Points[0].y;

        std::cout << "x"<<x<<std::endl;
        std::cout << "y"<< y <<std::endl;
        return std::pair<bool,Point2>(true,Point2(x,y));
      }
    }
    else
    {
      //This situation we are assuming does not exists (change later to tackle this)
      //This is when they have a infinite number of intersection points.
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
bool Line_Segment::On_Line(Point2 &p)
{
  if(this->End_Points[0].x!=this->End_Points[1].x)
  {
    float m=(this->End_Points[0].y-this->End_Points[1].y)/(this->End_Points[0].x-this->End_Points[1].x);
    if(m*(p.x-this->End_Points[0].x)+this->End_Points[0].y==p.y)
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
    if(this->End_Points[0].y>=p.y && this->End_Points[0].y<=p.y && p.x==this->End_Points[0].x)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
