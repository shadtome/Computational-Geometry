#ifndef BST_H
#define BST_H

#include "LineSegment.h"
#include <map>

/*
Binary Search tree Templated Class
*This takes in class T (the data), class S (Pivot), and a compare class between elements in T for the std::map 
*/



//Binary Search tree for the Event Queue and the Status record
template<class T, class S,class Compare>
struct BST_Node
{
public:
  S pivot;                                      // pivot point of the node
  std::map<T,T,Compare> data;                   //where we store the data for this node
  BST_Node<T,S,Compare>* Left_Node=NULL;        // pointer to the left node
  BST_Node<T,S,Compare>* Right_Node=NULL;       //Pointer to the right node
  BST_Node<T,S,Compare>* Parent_Node=NULL;      //Pointer to the parent node

};

template <class T,class S,class Compare>
class BST
{
public:
  BST_Node<T,S,Compare>* Root_Node;       //Root node of the Tree

  //constructor
  BST():Root_Node(NULL){};

  //Methods for the BST
  void Insert(S pivot, T new_element);      //Insert a new item from the class
  void Delete(S pivot, T element);          // Delete element in a node or the entire node if it is the last element of the node, also change pointers
  BST_Node<T,S,Compare>* Search(BST_Node<T,S,Compare> &node,S pivot, T element);       // Search for this element in the tree to see if it exists
  void Search_Compare_Point(BST_Node<T,S,Compare> &node,S pivot, T element);      //go through the tree till we can find the spot where the new node will be put into

};

//Methods
template<class T, class S,class Compare>
void BST<T,S,Compare>::Insert(S pivot, T new_element)
{
    if(this->Root_Node==NULL)                        //if the root node is empty, put the first element there
    {
      BST_Node<T,S,Compare>* temp_pointer = new BST_Node<T,S,Compare>;
      temp_pointer->pivot=pivot;
      temp_pointer->data[new_element]=new_element;
      Root_Node=temp_pointer;
    }
    else
    {
      Search_Compare_Point(*Root_Node,pivot,new_element);  //otherwise go to the left or right of the node
    }
}


template<class T, class S, class Compare>
void BST<T,S,Compare>::Delete(S pivot,T element)
{
  BST_Node<T,S,Compare>* to_be_deleted;
  to_be_deleted=Search(*Root_Node,pivot,element);        //Search for the node that we are going to delete

  //Next, we need to search in the right children tree for the smallest element with the given ordering to replace the spot we deleted
  if(to_be_deleted->Right_Node==NULL)                      //Check if the left node has anything, if not, then less operations we need to do when deleting
  {
    if(to_be_deleted->Left_Node==NULL)                //check to see if we need to do anything extra when we delete
    {
      delete to_be_deleted;                           //delete the node and do nothing
      return;
    }
    else
    {
      if(to_be_deleted->Parent_Node->Left_Node == to_be_deleted)               //we need to check which side of the parent node to_be_deleted is on
      {
        to_be_deleted->Parent_Node->Left_Node=to_be_deleted->Left_Node;        //If its the left node, then replace that pointer with the to_be_deleted pointer to its children on the left side
        delete to_be_deleted;
        return;
      }
      else
      {
        to_be_deleted->Parent_Node->Right_Node=to_be_deleted->Left_Node;       //Same thing, but on the right node pointer for its parent
        delete to_be_deleted;
        return;
      }
    }
  }
  else
  {
    //when there is children in the right node, we need to search for the smallest node, which means we need to travel through the left turns beginning at the first right node child of to_be_deleted
    BST_Node<T,S,Compare>* iterator = to_be_deleted->Right_Node;
    while(iterator->Left_Node != NULL)
    {
      iterator= iterator->Left_Node;          //search through the Left_Node till we get to one that has null left node pointer
    }

    if(iterator->Right_Node==NULL)
    {
      to_be_deleted->data = iterator->data;     //repplace the to_be_delete data
      delete iterator;                         //delete what it is pointing to
    }
    else
    {
      to_be_deleted->data = iterator->data;
      iterator->Parent_Node->Left_Node=iterator->Right_Node;           //Let the parent node of the iterator point to the right node of the iterator, so we dont lose this connection
      delete iterator;
    }
  }
}


template<class T, class S, class Compare>
BST_Node<T,S,Compare>* BST<T,S,Compare>::Search(BST_Node<T,S,Compare> &node, S pivot,T element)
{

    if(node.pivot>pivot && node.Left_Node != NULL)
    {
      return Search(*node.Left_Node, pivot, element);
    }
    else if(node.pivot < pivot && node.Right_Node != NULL)
    {
      return Search(*node.Right_Node,pivot,element);
    }
    else if(node.pivot == pivot)
    {
      return &node;
    }
    else
    {
      std::cout << "No such node exists"<< std::endl;
      return NULL;
    }
}




template<class T, class S,class Compare>
void BST<T,S,Compare>::Search_Compare_Point(BST_Node<T,S,Compare> &node,S pivot, T element)
{
  if(node.pivot> pivot)          //If the element is less then the data of node, then search left of the node for a spot
  {
    if(node.Left_Node==NULL)
    {
      BST_Node<T,S,Compare>* node_p= new BST_Node<T,S,Compare>;          //Make new node pointer
      node_p->data[element]=element;
      node_p->pivot=pivot;                                 //Input the data for new node
      node.Left_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(*node.Left_Node,pivot,element);
  }

  if(node.pivot<pivot)          //If the element is greater then the data of node, then search right of the node for a spot
  {
    if(node.Right_Node==NULL)
    {
      BST_Node<T,S,Compare>* node_p= new BST_Node<T,S,Compare>;          //Make new node pointer
      node_p->data[element]=element;
      node_p->pivot=pivot;                                 //Input the data for new node
      node.Right_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(*node.Right_Node,pivot,element);
  }
  if(node.pivot==pivot)                                                   //If the pivot is the same, then add the data in the same spot
  {
    node.data[element]=element;
  }
}




#endif
