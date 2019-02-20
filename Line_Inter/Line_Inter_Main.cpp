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
  Test.Insert(7,7);
  Test.Insert(8,8);




  //std::cout << Test.Is_Balanced(Test.Root_Node)<<std::endl;

  for(auto key=Test.Root_Node->data.begin(); key!= Test.Root_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Right_Node->Right_Node->data.begin(); key!= Test.Root_Node->Right_Node->Right_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Right_Node->data.begin(); key!= Test.Root_Node->Right_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }

  //Test.Balance(Test.Root_Node);
  std::cout << Test.Is_Balanced(Test.Root_Node)<<std::endl;

  /*for(auto key=Test.Root_Node->data.begin(); key!= Test.Root_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Left_Node->data.begin(); key!= Test.Root_Node->Left_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Right_Node->data.begin(); key!= Test.Root_Node->Right_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Right_Node->Left_Node->data.begin(); key!= Test.Root_Node->Right_Node->Left_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }*/



  Test.Balanced_Delete(5,5);
  Test.Balanced_Delete(4,4);
  Test.Balanced_Insert(5,5);
  Test.Balanced_Insert(4,4);
  //std::cout << Test.Is_Balanced(Test.Root_Node)<<std::endl;
  //Test.Delete(3,3);
  //std::cout << Test.Is_Balanced(Test.Root_Node)<<std::endl;
  //Test.Delete(2,2);
  for(auto key=Test.Root_Node->data.begin(); key!= Test.Root_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Left_Node->data.begin(); key!= Test.Root_Node->Left_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Right_Node->data.begin(); key!= Test.Root_Node->Right_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }
  for(auto key=Test.Root_Node->Left_Node->Right_Node->data.begin(); key!= Test.Root_Node->Left_Node->Right_Node->data.end(); ++key)
  {
    std::cout << key->second << std::endl;
  }





  return 0;
}
