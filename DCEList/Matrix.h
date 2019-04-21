#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

/* Header file to make any size matrix, and the usual operations for a matrix.
* Can make it over any field (C,R,Z_p, ect..)
*/

/*F is the field, and its a matrix of size n x m.
* This matrix is row-major a matrix
*
*         a_1 a_2 a_3
*         a_4 a_5 a_6
*         a_7 a_8 a_9
* is aligned in memory as a_1 a_2 ... a_9.
*/
template<class F,int n,int m>
class Matrix
{
  //The matrix in memory
  std::vector<F> elements;

public:
  //constructors
  //The default constructor will will make a identity matrix
  Matrix();

  //Constructor with rows.


};


template<class F,int m>
class RowVec
{
private:
  //The row vector elements
  std::vector<F> Row_elements;

public:
  //Constructors
  //default creates a zero row vector
  RowVec();

  //With entries in
  RowVec(std::vector<F> vec);
};



//-----------------------------------
//RowVec functions

//  - - - - - - - - - - - - - - - - -
//Constructor
template<class F,int m>
RowVec<F,m>::RowVec(std::vector<F> vec)
{
  if(vec.size()==m)
  {
    this->Row_elements=vec;
  }
  else if(vec.size()<m)
  {
    this->Row_elements=vec;
    this->Row_elements.insert(this->Row_elements.end(),m-vec.size(),0);
  }
  else
  {
    throw std::range_error("number of elements inputing is greater then "+m);
  }
}


#endif
