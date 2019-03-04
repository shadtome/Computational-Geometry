#include <iostream>
#include "BST.h"
#include "LineSegment.h"




int main()
{
  BST<int,int> Test;
  Test.Insert(1,1);
  Test.Insert(2,2);
  Test.Insert(3,3);
  Test.Insert(4,4);
  Test.Insert(5,5);
  Test.Insert(6,6);
  Test.Insert(19,19);
  Test.Insert(-4,-4);
  Test.Balance(Test.Root_Node);
  Test.Balanced_Delete(3,3);
  //Test.Delete(5,5);
  //Test.Balance(Test.Root_Node);
  Test.Balanced_Delete(5,5);
  for(auto key=Test.begin();key!=Test.end(); ++key )
  {
    std::cout << (*key).pivot<<std::endl;
  }
  Test.Balanced_Insert(3,3);
  Test.Balanced_Delete(5,5);
  Test.Balanced_Delete(1,1);
  for(auto key=Test.begin();key!=Test.end(); ++key )
  {
    std::cout << (*key).pivot<<std::endl;
  }
  std::cout << "hmmm"<<std::endl;
  return 0;
}
