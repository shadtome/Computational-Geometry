
#include "LineInterMath.h"
#include "lineinterAlg.h"
#include <iostream>
#include <set>
#include <algorithm>



//Constructor
LineIntersections::LineIntersections(std::vector<Line_Segment> lines)
{
  Find_Intersection(lines);
}


//Main Algorithm!

void LineIntersections::Find_Intersection(std::vector<Line_Segment> lines)
{

  /* First, define the event queue
  * This holds the points in order as the pivot points
  * and holds the line_segments that have this point as its upper endpoint
  */
  Queue Q;

  /* Second, define the status BST
  * This holds a ordered tree of all the line segments
  * that intersect the sweep line (y=some constant number)
  * So if a line segment does not intersect the sweep line, it
  * must be deleted.  On the other hand, a new line segment that intersects
  * the sweep line must be added in
  */
  Status T;

  /*Next, lets insert all the relevent points in to Q
  * i.e. the end points of the line line_segments
  * But only store the line segment witht the point
  * iff it is the largest point in the line segment
  */

  for(unsigned int k=0; k<lines.size(); ++k)
  {
    Q.Balanced_Insert(lines[k].End_Points[0],lines[k]);  //Insert the pivot point as the upper left most point, and the connected line segment
    Q.Balanced_Insert(lines[k].End_Points[1]);           //Just insert the pivot point, with no data added to it
  }

  while(Q.Is_Empty()==false)
  {
    //Determine the new event point
    //to do this, we need to find the ordered list of events in Q
    std::vector<Queue_Node*> ordered_events=Q.Node_list(Q.Root_Node);

    //Event point, which is the first elemnt of this list
    Queue_Node* event_point=ordered_events[0];

    //Next, process this event point
    //This is the meat of the algo
    HandleEventPoint(event_point,Q,T);

    Q.Balanced_Delete(event_point->pivot);

  }

}





//-----------------------------------------------------
//Handle event point function
void LineIntersections::HandleEventPoint(Queue_Node* p,Queue &Q, Status &T)
{
  //Collection of line_segments that intersect p.
  std::vector<Line_Segment> result;
  //This is the collection of line_segments that contain the point p as a upper point
  std::vector<Line_Segment> U_p;

  //Input the data in to U_p from p.
  for(auto it=p->data.begin(); it != p->data.end(); ++it)
  {
    U_p.push_back(it->second);
  }
  //This is the collection of line_segments in T that contain p as a lower end point
  std::vector<Line_Segment> L_p;

  //This is the collection of line segments in T that contain p in the interior
  std::vector<Line_Segment> C_p;


  //THis is the list of nodes in T that don't intersect p, and we need to update their
  // sweep_int to make the ordering correct.
  std::vector<Line_Segment> Does_not_int_p;
  //Next, we need to process through the status T for all the line segments that contain the point p
  // and put the correct line segments in to L_p and C_p.
  for(auto key=T.begin(); key!=T.end(); ++key)//Search through the status
  {

    Line_Segment nodedata=key->pivot;  //This first element of the map
    bool on_line=nodedata.On_Line(p->pivot);


    //Check if any elements of T have p as a lower endpoint or in the interior.
    if(on_line)
    {
      if( p->pivot==nodedata.End_Points[1]) //Check if a line_segment has p as its lower endpoint
      {
        L_p.push_back(nodedata);
      }
      else if(p->pivot!=nodedata.End_Points[0]) //Dont want to include the ones that have p as its upper endpoint
      {
        C_p.push_back(nodedata);
      }
    }
    else
    {
      //If it does not contain the point p, then we need to delete it
      // Change the sweep_int for the sweep line
      // then re insert it in.
      //Find a better way to do this later
      Does_not_int_p.push_back(nodedata);

    }
  }

    //Now delete all the elements in Dont_Int_p change their sweep_int and reinsert them
  for(unsigned int k=0; k<Does_not_int_p.size(); ++k)
  {
    T.Balanced_Delete(Does_not_int_p[k]);
    Does_not_int_p[k].Update_sweep(p->pivot,UPPER);
    T.Balanced_Insert(Does_not_int_p[k]);
  }


  //Next, we need to check if U_p\cup L_p\cup C_p contain more then one line segment
  //Since L_p, C_p, and U_p are disjoint by definition, it suffices to see what the total size of these
  //sets are by adding the sizes.
  if(L_p.size()+C_p.size()+U_p.size()>1)
  {
    //This means that there is a intersection point.
    auto it=result.begin();
    if(L_p.size()>0)
    {
      result.insert(it,L_p.begin(),L_p.end());
    }

    if(U_p.size()>0)
    {
      it=result.end();
      result.insert(it,U_p.begin(),U_p.end());
    }
    if(C_p.size()>0)
    {
      it=result.end();
      result.insert(it,C_p.begin(),C_p.end());
    }
    //Now put in the line_segment and the point into the intersection map
    Intersection_Point collection_p_inter(p->pivot,result);
    this->intersections[p->pivot]=collection_p_inter;
  }



  //Now delete the elements L_p\cup C_p from T
  // and change the C_p ordering from upper to lower, this is to handle the switching across the sweep line
  for(unsigned int k=0; k<L_p.size(); ++k)
  {
    T.Balanced_Delete(L_p[k]);
  }
  for(unsigned int k=0; k<C_p.size(); ++k)
  {
    T.Balanced_Delete(C_p[k]);
  }

  // Then insert U_p and C_p in to T,
  for(unsigned int k=0; k<U_p.size(); ++k)
  {
    T.Balanced_Insert(U_p[k]);
  }
  for(unsigned int k=0; k<C_p.size(); ++k)
  {
    //Before we put it in, we need to make sure we define a new sweep_int point, so we can distinguish it from
    // other lines that might have the same x-coordinate for its upper point that are in U_p.
    C_p[k].Update_sweep(p->pivot,LOWER);
    T.Balanced_Insert(C_p[k]);
  }


  //Next, we need to find new event points for our Queue
  // i.e. check for new intersections with our new ordering of line_segments
  // on the sweep line
  if(C_p.size()+U_p.size()==0)
  {

    /* THis is the case where there is no new lines that intersect p after the sweep line.
    * So we need to check intersections of the two nearest neighbors of p still intersecting the sweep line ,
    * but are now neighbords under the sweep line.
    */
    Line_Segment S_l; //Left neighbor to p
    Line_Segment S_r; //right neighbor to p

    Line_Segment Point_P(p->pivot,p->pivot); //Line segment representing p, so we can compare the
                          // line segments in T with this point.

    T.Insert(Point_P);    //Insert the point p in to the T, so we can find the left and right neighbor of p

    auto it=T.begin();
    auto it_2=T.begin();  //This is to told the information of the iterator before it ++.

    if(it!=T.end())
    {
      while(it->pivot!=Point_P)  //it->pivot!=Point_P
      {

        it_2=it++;            //This looks through the Tree and keeps a node right before the iterator was iterated

        if(it==T.end())
        {
          break;
        }
      }
    }


    if(it!=it_2)          //If the first iterator did not move, then the first spot is where P is
    {
      if(it_2!=T.end())
      {

        S_l=it_2->pivot;    //This is the left line segment of P

        ++it;

        if(it!=T.end())
        {
          S_r=it->pivot;      //This is the right line segment of P
          //Find new intersection points between these new neighbors
          Find_New_Event(S_l,S_r,p->pivot,Q);
        }
      }


    }
    T.Delete(Point_P);

  }
  else
  {

    //This is the situation where we still have line segments intersecting p and the ordering of them has changed
    // So we need to check the intersections of the new neighbors to the left of all elements in U_p\cup C_p and to the right.
    Line_Segment l_p;  //Left most linesegment of C_p\cup U_p.
    Line_Segment r_p;  //Right most line segment of C_p\cup U_p
    Line_Segment S_l;  //left neighbor of l_p;
    Line_Segment S_r;  //right neighbor of r_p;

    //First, lets find l_p, and r_p (which exists becuase C_p\cup U_p is not empty)
    //So we will put both C_p and U_p together and use the sort algorthm on it
    std::vector<Line_Segment> C_U;

    C_U.insert(C_U.begin(),C_p.begin(),C_p.end());
    C_U.insert(C_U.end(),U_p.begin(),U_p.end());
    std::sort(C_U.begin(),C_U.end());           //We need to sort the elements to find the first and last.
    l_p=C_U.front();
    r_p=C_U.back();


    //Next, we need to find the S_l, and S_r, (in the same way we did C_p\cup U_p=empty case, with out the point p)
    auto it=T.begin();
    auto it_2(it);


    if(it!=T.end())
    {
      while(it->pivot!=l_p) //it->pivot!=l_p
      {

        it_2=(it++);

        if(it==T.end())
        {
          break;
        }

      }
    }


    if(it!=it_2)
    {
      if(it_2!=T.end())
      {
        S_l=it_2->pivot;
        Find_New_Event(S_l,l_p,p->pivot,Q);

      }


    }

    for(auto key=T.begin(); key!=T.end(); ++key)
    {
      if(key->pivot==r_p)
      {

        ++key;

        if(key!=T.end())
        {
          S_r=key->pivot;
          Find_New_Event(r_p,S_r,p->pivot,Q);

        }
        break;
      }
    }



  }

  //Last thing we do, is handle all the lines that are horizontal.
  //since a horizontal line has its upper end point to the left, then all
  //we need look at all the elements in T that is right of this line
  // up to the end of the linesegment and those will all intersect
  for(auto k=U_p.begin(); k!=U_p.end(); ++k)
  {
    //Horizontal lines
    if(k->End_Points[0].y==k->End_Points[1].y)
    {
      //First, lets start at k in T.
      auto it=T.begin();
      while(it->pivot!=*k)
      {
        ++it;
      }

      //Next, go through all the elements in T that are right of this "it"
      // and check if their x-value is less then the x value of the last endpoint of the line "k"
      while(it!=T.end())
      {
        if(it->pivot.sweep_int.first.x<=k->End_Points[1].x)
        {
          //New Event point!
          float x=it->pivot.Find_x(k->End_Points[0].y);
          Point2 new_point(x,k->End_Points[0].y);
          Q.Balanced_Insert(new_point);
        }
        ++it;
      }
    }
  }



}


//-----------------------------------------------------
//Find New Event point function


void LineIntersections::Find_New_Event(Line_Segment &l_1,Line_Segment &l_2, Point2 &point,Queue &Q)
{
  //FInd if there are any intersection points between these two lines
  std::pair<bool,Point2> inter_point;

  if(l_1.End_Points[0]!=l_2.End_Points[0] && l_1.End_Points[1]!=l_2.End_Points[1])//l_1!=l_2
  {
    inter_point=l_1.Intersection(l_2);
  }
  else
  {
    inter_point.first=false;
  }


  if(inter_point.first)
  {
    //If one exists, we need to make sure we did not account for this intersection already
    auto check_point=this->intersections.find(inter_point.second);
    if(check_point!=this->intersections.end())
    {
      return;     //This means that the intersection point already exists in our collection of intersection points
                  // we don't want to check the same point agian.
    }
    else
    {
      Q.Balanced_Insert(inter_point.second);
    }

  }
  else
  {
    return;
  }
}
