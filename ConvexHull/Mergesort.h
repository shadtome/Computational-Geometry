#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
typedef std::vector<std::vector<float>> Points;

//Merge Sort



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



#endif
