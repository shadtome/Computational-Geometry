#include <iostream>
#include <vector>

typedef std::vector<std::vector<float>> Points;

//Determinant of a 2x2 matrix
float Det_2(float M[2][2])
{
  return M[0][0]*M[1][1]-M[0][1]*M[1][0];
}

//Determinant of a 3x3 matrix
float Det_3(float M[3][3])
{
  return M[0][0]*(M[1][1]*M[2][2])-M[1][0]*(M[0][1]*M[2][2]-M[2][1]*M[0][2])+M[2][0]*(M[0][1]*M[1][2]-M[1][1]*M[0][2]);
}

// Determines which point P<Q in the Lexographic ordering meaning (x,y)<(z,w) if x<z, or x=z and y<w
bool Lexo_Order(std::vector<float> P, std::vector<float> Q)
{
  if(P[0]<Q[0])
  {
    return true;
  }

  if(P[0]==Q[0])
  {
    if(P[1]<Q[1])
    {
      return true;
    }
    else
    {
      return true; //THis is when both points are the same
    }
  }
  return false; //This means that P>Q

}
//-----------------------------------------------------------------------
//Divide and Conquer (merge sort using Lexographic ordering) From Wikipedia on Merge sort
void LexMerge(Points &A, unsigned int iBegin, unsigned int iMiddle, unsigned int iEnd, Points &B);
void SplitMergeLex(Points &B, unsigned int iBegin, unsigned int iEnd, Points &A);

//Lets take a collection of points and Order them using Lexographic (maybe even generalize this functino to any ordering)

//Vector A is the item sort and vector B is the work arra
void LexMergeSort(Points &A)
{
  Points B=A;//Copy points
  SplitMergeLex(B,0,A.size(),A);
}

//Sort the given run of array A using array B as a source
//iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set)
void SplitMergeLex(Points &B, unsigned int iBegin, unsigned int iEnd, Points &A)
{
  if(iEnd-iBegin<2) // run size ==1
    return;

  //Split the run longer then 1 item into halves
  unsigned int iMiddle = (iEnd+iBegin)/2;   //the midpoint
  //Revursively sort both runs from vector A into vector B
  SplitMergeLex(A,iBegin,iMiddle, B);       //Sort the left run
  SplitMergeLex(A, iMiddle, iEnd, B);       //Sort the right runs



  //Merge the resulting runs from vector B into vector A
  LexMerge(B,iBegin,iMiddle,iEnd,A);
}


//Left source half is A[iBegin: iMiddle-1]
// Right source half is A[iMiddle:iEnd-1]
//Result is B[Begin:iEnd-1]
void LexMerge(Points &A, unsigned int iBegin, unsigned int iMiddle, unsigned int iEnd, Points &B)
{
  unsigned int i=iBegin, j=iMiddle;
  //While there are elements in the left or right runs
  for (int k=iBegin; k<iEnd; ++k)
  {
    //If left run head exists and is <= // Had to do this for now because of the segmentation fault 11
    if(i<iMiddle && j>=iEnd)
    {

      B[k]=A[i];
      i=i+1;
    }
    else if(i<iMiddle && j<iEnd)
    {
      if(Lexo_Order(A[i],A[j]))
      {
        B[k]=A[i];
        i=i+1;
      }
      else
      {
        B[k]=A[j];
        j=j+1;
      }
    }
    else
    {
      B[k]=A[j];
      j=j+1;
    }
  }

}




//----------------------------------------------------------
enum Side
{
  LEFT=1,
  RIGHT=0,
  COLINEAR=1
};


//Determines which side the point R is with respect to the line segment PQ
Side Side_of_line(std::vector<float> P,std::vector<float> Q,std::vector<float> R)
{
  float result=(Q[0]*R[1]-Q[1]*R[0])-(P[0]*R[1]-P[1]*R[0])+(P[0]*Q[1]-P[1]*Q[0]);

  if(result>0)
    return LEFT; //This means that R is on the left side of the line segment from P to Q

  if(result<0)
    return RIGHT; //This means that R is on the right side of the line Segment from P to Q

  return COLINEAR; // meaning they are on the same line
}






//-------------------------------------------------------------------
//Polygon Class

class Polygon
{
public:
  //Vertices of the polygon // just use this for now, I can make it better later if I need this, just to make it easy to test
  Points Vertices; // vertices of a polygon in clockwise order
  //Default Constructor
  Polygon();
  //Constructor: finds the polygonal convex hull that contains the points
  Polygon(Points &points);





};

Polygon::Polygon()
{
  this->Vertices={{0,0}};
}

Polygon::Polygon(Points &points)
{
  //Sort the points
  LexMergeSort(points);


  //Temporary list of points
  std::vector<float> List_Upper[points.size()];
  std::vector<float> List_Lower[points.size()];

  //Put in the first two points of the sorted list of points;

  List_Upper[0]=points[0];
  List_Upper[1]=points[1];

  //Current locaiton in upper or lower index where we are changing the points
  unsigned int isize_U=1;

  for (int k=2; k<points.size(); ++k)
  {
    //Append the p_kth point in to the List_Upper
    isize_U=isize_U+1;
    List_Upper[isize_U]=points[k];


    if(isize_U>1)
    {
      while(Side_of_line(List_Upper[isize_U-2],List_Upper[isize_U-1],List_Upper[isize_U])==LEFT)
      {
        //Delete the middle of the last three points, and move the list back to and the isize back by 1
        //if the last three points do not curve right
        List_Upper[isize_U-1]=List_Upper[isize_U];
        isize_U=isize_U-1;
        if(isize_U<=1)
        {
          break;
        }
      }
    }
  }
  //Now for the List_Lower part
  int size=points.size();
  List_Lower[0]=points[size-1];
  List_Lower[1]=points[size-2];
  int isize_L=1;

  for (int k=2; k<size-1; ++k)
  {
    //Append the p_n-kth point in to the List_low
    isize_L=isize_L+1;
    List_Lower[isize_L]=points[size-1-k];

    if(isize_L>1)
    {
      while(Side_of_line(List_Lower[isize_L-2],List_Lower[isize_L-1],List_Lower[isize_L])==LEFT)
      {
        //Delete the middle of the last three points, and move the list back to and the isize back by 1
        //if the last three points dont curve right
        List_Lower[isize_L-1]=List_Lower[isize_L];
        isize_L=isize_L-1;
        if(isize_L<=1)
        {
          break;
        }
      }
    }

  }

  //Finished with completeing Upper and Lower vertices, now we need to put them all in order in to the Vertices
  for(int k=0; k<isize_U+1; ++k)
  {
    Vertices.push_back(List_Upper[k]);
  }
  //Put in the LIst_Lower but ignore the first and lasst one, since those are already in it
  for(int k=1; k<isize_L; ++k)
  {
    Vertices.push_back(List_Lower[k]);
  }
}


//------------------------------------------------------------------------------
// Now lets find the convex hull for the union of two convex polygons

Polygon Convex_Union(Polygon &poly1, Polygon &poly2)
{
  Points* Vertices[2]={ &poly1.Vertices, &poly2.Vertices};
  // Make enough room for all the vertices
  std::vector<float> ConvUnion[poly1.Vertices.size()+poly2.Vertices.size()]; // the resulting list of vertices that will make the convex polygon
  ConvUnion[0]=poly1.Vertices[0];
  ConvUnion[1]=poly1.Vertices[1];

  int index[2]={2,0}; //current vertex for polygon 2

  int flip =1;  // which polygon to choose a vertex from opposite from the last one we put in to the List

  int j=1;  // Which index of the list ConvUnion we are putting the next vertex in to.

  while(index[0] < poly1.Vertices.size() || index[1] < poly2.Vertices.size())
  {
    bool did_delete=false;                        // tell if we deleted vertices, which means, don't flip
    j += 1;
    ConvUnion[j]= (*Vertices[flip])[index[flip]]; // plug in the vertex for poly in to the jth spot
    index[flip] += 1;                             // increment the index for this polygon

    if(j>1)
    {
      while(Side_of_line(ConvUnion[j-2],ConvUnion[j-1],ConvUnion[j])==LEFT ) // Check if the three points are turn left, which is what we dont want
      {
        did_delete=true;              // if deleted, we wont swich the flip, but continue on
        ConvUnion[j-1]=ConvUnion[j]; // delate the middle point out of these three
        j -=1;                       // go back on which vertex we want to put in, since we deleted one

        if(j<=1)
          break;                    // if we go back to 2 elements, break out of this loop
      }
      if(did_delete==false)
      {
        flip = (flip+1) %2;                           // change the flip so we can check the other polygon
      }
      if(index[0]==poly1.Vertices.size())   //if we finished this polygon, just stay on the other polygon till the end
      {
        flip = 1;
      }
      if(index[1] == poly2.Vertices.size())
      {
        flip =0;
      }
    }
  }
  Polygon result;
  result.Vertices[0]=ConvUnion[0];
  for (int k=1; k<j+1; ++k)
  {
    result.Vertices.push_back(ConvUnion[k]);
  }
  return result;
}






int main()
{
  Points Vertices1 = {{1,2},{2,5},{4,3},{3,1}};
  Points Vertices2 = {{4,5},{6,8},{7,1}};

  Polygon test1(Vertices1);
  Polygon test2(Vertices2);

  Polygon union_test=Convex_Union(test1, test2);

  /*for(int k=0; k<test1.Vertices.size(); ++k)
  {
    std::cout << test1.Vertices[k][0] << "::" << test1.Vertices[k][1] << std::endl;
  }
  for(int k=0; k<test2.Vertices.size(); ++k)
  {
    std::cout << test2.Vertices[k][0] << "::" << test2.Vertices[k][1] << std::endl;
  }*/
  for(int k=0; k<union_test.Vertices.size(); ++k)
  {
    std::cout << union_test.Vertices[k][0] << "::" << union_test.Vertices[k][1] << std::endl;
  }


  return 0;
}
