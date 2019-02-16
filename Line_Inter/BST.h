#ifndef BST_H
#define BST_H

#include "LineSegment.h"
#include <map>

/*
Binary Search tree Templated Class
*This takes in class T (the data), class S (Pivot), and a compare class between elements in T for the std::map
*/



//Binary Search tree for the Event Queue and the Status record
template<class T, class S>
struct BST_Node
{
public:
  S pivot;                                      // pivot point of the node
  std::map<T,T> data;                   //where we store the data for this node
  BST_Node<T,S>* Left_Node=NULL;        // pointer to the left node
  BST_Node<T,S>* Right_Node=NULL;       //Pointer to the right node
  BST_Node<T,S>* Parent_Node=NULL;      //Pointer to the parent node

};

template <class T,class S>
class BST
{
public:
  BST_Node<T,S>* Root_Node;       //Root node of the Tree

  //constructor
  BST():Root_Node(NULL){};

  //Methods for the (Non-Balancing) BST
  //----------------------
  /* (Non-Balancing) insert
  *  Traverses the tree using the relation from the pivot and inserts it self
  */
  void Insert(S pivot, T new_element);      //Insert a new item from the class

  /* (Non-Balancing) delete
  * Deletes the node corresponding to the pivot and elements
  * by just finding the most left element in the right subtree
  * from the spot we deleted and replaces the deleted spot by this element we found
  */
  void Delete(S pivot, T element);

  //Search Function
  /*
  * Node is where the search starts
  * Then check left and right subtrees starting from this node
  */
  BST_Node<T,S>* Search(BST_Node<T,S> *node,S pivot, T element);
  void Search_Compare_Point(BST_Node<T,S> *node,S pivot, T element);      //go through the tree till we can find the spot where the new node will be put into

  //Balancing Methods
  //----------------------

  /* Node_list function
  * Takes a subtree and concatenates the ordered list from the left tree and right tree with the "root node" in the middle of them
  */
  std::vector<BST_Node<T,S>*> Node_list(BST_Node<T,S>* node);

  /*Balanced function
  * Used to take the subtree and rebalance at a specific node so that it satisfies the balanced property for that subtree
  */
  void Balance(BST_Node<T,S>* node);

  /* Balanced Delete
  * deletes a element, and rebalances the subtree so that the whole tree is still balanced
  */
  void Balanced_Delete(S pivot, T element);

  /* Balanced insert
  * Insert a element in the correct spot, but balances the subtree so that the whole tree is balanced
  */
  void Balanced_Insert(S pivot, T new_element);

private:
  /* Self Balancing function given the list of Nodes
  * That will balance just these Nodes
  */
  void Balance_Node(std::vector<BST_Node<T,S>*> &nodes, BST_Node<T,S>* root_node);

};

//Methods
template<class T, class S>
void BST<T,S>::Insert(S pivot, T new_element)
{
    if(this->Root_Node==NULL)                        //if the root node is empty, put the first element there
    {
      BST_Node<T,S>* temp_pointer = new BST_Node<T,S>;
      temp_pointer->pivot=pivot;
      temp_pointer->data[new_element]=new_element;
      Root_Node=temp_pointer;
    }
    else
    {
      Search_Compare_Point(Root_Node,pivot,new_element);  //otherwise go to the left or right of the node
    }
}


template<class T, class S>
void BST<T,S>::Delete(S pivot,T element)
{
  BST_Node<T,S>* to_be_deleted;
  to_be_deleted=Search(Root_Node,pivot,element);        //Search for the node that we are going to delete

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
    BST_Node<T,S>* iterator = to_be_deleted->Right_Node;
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


template<class T, class S>
BST_Node<T,S>* BST<T,S>::Search(BST_Node<T,S>* node, S pivot,T element)
{

    if(node->pivot>pivot && node->Left_Node != NULL)
    {
      return Search(node->Left_Node, pivot, element);
    }
    else if(node->pivot < pivot && node->Right_Node != NULL)
    {
      return Search(node->Right_Node,pivot,element);
    }
    else if(node->pivot == pivot)
    {
      return node;
    }
    else
    {
      std::cout << "No such node exists"<< std::endl;
      return NULL;
    }
}




template<class T, class S>
void BST<T,S>::Search_Compare_Point(BST_Node<T,S>* node,S pivot, T element)
{
  if(node->pivot> pivot)          //If the element is less then the data of node, then search left of the node for a spot
  {
    if(node->Left_Node==NULL)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->data[element]=element;
      node_p->pivot=pivot;                                 //Input the data for new node
      node->Left_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(node->Left_Node,pivot,element);
  }

  if(node->pivot<pivot)          //If the element is greater then the data of node, then search right of the node for a spot
  {
    if(node->Right_Node==NULL)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->data[element]=element;
      node_p->pivot=pivot;                                 //Input the data for new node
      node->Right_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(node->Right_Node,pivot,element);
  }
  if(node->pivot==pivot)                                                   //If the pivot is the same, then add the data in the same spot
  {
    node->data[element]=element;
  }
}


//Balancing Functions
//-----------------------------------
template<class T, class S>
std::vector<BST_Node<T,S>*> BST<T,S>::Node_list(BST_Node<T,S>* node)
{
  std::vector<BST_Node<T,S>*> result;            //Resulting list that we will send up through the tree


  if(node->Left_Node != NULL)
  {
    std::vector<BST_Node<T,S>*> left_result;
    left_result=Node_list(node->Left_Node);

    //We will be inserting the left_result information at the end of the result list.
    auto it=result.end();
    result.insert(it, left_result.begin(), left_result.end());

  }

  //Insert the main node in the middle of the list
  result.push_back(node);

  if(node->Right_Node != NULL)
  {
    std::vector<BST_Node<T,S>*> right_result;
    right_result = Node_list(node->Right_Node);

    //Insert the right_result information at the end of the result list
    auto it=result.end();
    result.insert(it,right_result.begin(),right_result.end());
  }

  return result;
}


template<class T,class S>
void BST<T,S>::Balance(BST_Node<T,S>* node)
{
  std::vector<BST_Node<T,S>*> ordered_list;

  //First, find the ordered list from smallest to largest for the subtree with "root node" at node
  ordered_list=Node_list(node);

  //If the node we put in is the root node, we need to do something more special
  //since the Root_Node element is a pointer, so we need to actually change this pointer
  //otherwise, we will lose the entire Tree
  if(node==this->Root_Node)
  {
    //look for the middle one, and set it equal to this pointer
    int middle_index = (int)ordered_list.size()/2;
    this->Root_Node=ordered_list[middle_index];
    Balance_Node(ordered_list,this->Root_Node);
  }
  else
  {
    //Next, Balance the node
    Balance_Node(ordered_list,node);
  }


}



template<class T,class S>
void BST<T,S>::Balance_Node(std::vector<BST_Node<T,S>*> &nodes,BST_Node<T,S>* root_node)
{
  //Set our new "root node" as the middle of this list
  int middle_index = (int)nodes.size()/2;

  //The "root node" for the left subtree
  int left_middle_index=(int)(middle_index)/2;

  //the "root node" for the right subtree
  int right_middle_index=(int)(nodes.size()+middle_index)/2;

  //Point the middle node in this list to the "root node"
  nodes[middle_index]->Parent_Node=root_node;

  if(left_middle_index != middle_index)                  //Check if there is anymore elements to the left of the middle element
  {
    //point the "root nodes" left child to middle of the left section of the list
    root_node->Left_Node=nodes[left_middle_index];


    std::vector<BST_Node<T,S>*> left_section_nodes;
    auto it_l = left_section_nodes.begin();
    //insert the right section of the whole list in to this new list
    left_section_nodes.insert(it_l,nodes.begin(), nodes.begin()+middle_index);
    //Process through the same function, but now for the elements less then the middle element
    Balance_Node(left_section_nodes,root_node->Left_Node);
  }
  else
  {
    root_node->Left_Node=NULL;
  }


  if(right_middle_index != middle_index)              //check if there is anymore elements to the right of the middle element
  {
    //point the "root node" right child to the middle of the right section of the list
    root_node->Right_Node=nodes[right_middle_index];

    //Also, do the same for the right section
    std::vector<BST_Node<T,S>*> right_section_nodes;
    auto it_r = right_section_nodes.begin();
    //Process through the same function, but now for the elements greater then the middle element
    right_section_nodes.insert(it_r,nodes.begin()+middle_index+1, nodes.end());
    Balance_Node(right_section_nodes,root_node->Right_Node);
  }
  else
  {
    root_node->Right_Node=NULL;
  }

}



#endif
