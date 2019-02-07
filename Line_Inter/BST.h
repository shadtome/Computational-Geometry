#ifndef BST_H
#define BST_H

#include "LineSegment.h"
#include <map>

// Might not be able to do template in a easy way.  So to make my life easier mgiht just use on template,
// Unless I can find a way to template it



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
  BST_Node<T,S,Compare> Root_Node;       //Root node of the Tree

  //Methods for the BST
  void Insert(S pivot, T new_element);      //Insert a new item from the class
  void Delete(S pivot, T element);          // Delete element in a node or the entire node if it is the last element of the node, also change pointers
  BST_Node<T,S,Compare> Search(BST_Node<T,S,Compare> &node,S pivot, T element);       // Search for this element in the tree to see if it exists
  void Search_Compare_Point(BST_Node<T,S,Compare> &node,S pivot, T element);      //go through the tree till we can find the spot where the new node will be put into

};

//Methods
template<class T, class S,class Compare>
void BST<T,S,Compare>::Insert(S pivot, T new_element)
{
    if(Root_Node.data.size()==0)                        //if the root node is empty, put the first element there
    {
      Root_Node.pivot=pivot;
      Root_Node.data[new_element]=new_element;
    }
    else
    {
      Search_Compare_Point(Root_Node,pivot,new_element);  //otherwise go to the left or right of the node
    }
}


template<class T, class S, class Compare>
void BST<T,S,Compare>::Delete(S pivot,T element)
{
  BST_Node<T,S,Compare> to_be_deleted;
  to_be_deleted=Search(Root_Node,pivot,element);
  //Need to finish this: This is hard! lots of things to do
}


template<class T, class S, class Compare>
BST_Node<T,S,Compare> BST<T,S,Compare>::Search(BST_Node<T,S,Compare> &node, S pivot,T element)
{
    if(node.pivot>pivot)
    {
      return Search(*node.Left_Node, pivot, element);
    }
    else if(node.pivot < pivot)
    {
      return Search(*node.Right_Node,pivot,element);
    }
    else
      return node;
}




template<class T, class S,class Compare>
void BST<T,S,Compare>::Search_Compare_Point(BST_Node<T,S,Compare> &node,S pivot, T element)
{
  if(node.pivot> pivot)          //If the element is less then the data of node, then search left of the node for a spot
  {
    if(node.Left_Node==NULL)
    {
      BST_Node<T,S,Compare>* node_p= new BST_Node<T,S,Compare>;          //Make new node pointer
      node_p->data[element]=element;                                  //Input the data for new node
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
      node_p->data[element]=element;                                  //Input the data for new node
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
