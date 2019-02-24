#ifndef BST_H
#define BST_H

#include "LineSegment.h"
#include <map>
#include <cstdlib>
#include <memory> //Maybe use smart pointers, but a little bit of overhead

/* The big question I have, I am not sure if a smart pointer is useful here or not.
* I know where all created objects are from new here, and delete them accordly in the destructors,
* but what if there is a bad_alloc that gets thrown in the destructor.  I am not sure what to do with this.
* If I use smart pointers, this will make is more exception safe, in that new allocated memory wont leak.
*/

/*
Binary Search tree Templated Class
*This takes in class T (the data), class S (Pivot), and a compare class between elements in T for the std::map
*/

//Is there a way to have a function take in a "empty" object and so we can make the BST just insert the pivot and not the data
// For example, (a,empty) to the node a but not insert anything in to the map.
//I don't want to use pointers for this, as I want it to take in just the element, not the pointers
//For now I just made another overloaded function

//Forward declare the BST class
template<class T,class S>
class BST;

//Binary Search tree for the Event Queue and the Status record
template<class T, class S>
struct BST_Node
{
  friend BST<T,S>;      //Let the BST access its nodes
public:
  S pivot;                                      // pivot point of the node
  std::map<T,T> data;                   //where we store the data for this node
  BST_Node<T,S>* Left_Node;        // pointer to the left node
  BST_Node<T,S>* Right_Node;       //Pointer to the right node
  BST_Node<T,S>* Parent_Node;      //Pointer to the parent node

  //Constructor
  BST_Node():Left_Node(nullptr),Right_Node(nullptr),Parent_Node(nullptr) {};
  //Destructor
  ~BST_Node();
  //Copy constructor (just copies the left and right node, not the parent)
  BST_Node(const BST_Node<T,S> &other);
  //Copy Assignment operator
  BST_Node<T,S>& operator=(const BST_Node<T,S> &other);


  //Iterators



};

template <class T,class S>
class BST
{
public:
  BST_Node<T,S>* Root_Node;       //Root node of the Tree

  //constructor
  BST():Root_Node(nullptr){};
  //Copy constructor
  BST(const BST<T,S> &other);
  // Copy Assignment operator
  BST<T,S>& operator=(const BST<T,S> &other);
  //Destructor
  ~BST();

  //Methods for the (Non-Balancing) BST
  //----------------------
  /* (Non-Balancing) insert
  *  Traverses the tree using the relation from the pivot and inserts it self.
  * This uses the search function below
  */
  void Insert(S pivot, T new_element);      //Insert a new item from the class

  /* (non-Balancing) Overloaded insert
  * Traverses the tree using the relation from the pivot and find the new node
  * if there does not exists any node with the pivot point
  * this does not take any new elements
  */
  void Insert(S pivot);

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
  * for the element with pivot S and searchs in that pivot for the element
  */
  BST_Node<T,S>* Search(BST_Node<T,S>* &node,S pivot, T element);

  /* Checks if the BST is empty or not
  * Just checks if the Root node is not null
  * since if it was null, then this tree empty
  */
  bool Is_Empty();

private:
  /*Search compare point function
  * Takes in a node, which is where we start the search
  * pivot and element which we will insert in to the tree
  * This function does more then search,
  * it searches, then compares which side, and then adds in the new element in to the list
  * and makes sure all pointers are correct
  * this function is recursive
  */
  void Search_Compare_Point(BST_Node<T,S>* &node,S pivot, T element);

  /* Overloaded search compare point function
  * does not insert a new element, just finds the new node (if applicable)
  */
  void Search_Compare_Point(BST_Node<T,S>* &node,S pivot);

  /* Initalize for the copy constructor
  * Used to allocate new BST with the copied information
  * this is recursive
  */
  void _Copy_init_(BST_Node<T,S>* &node, const BST<T,S>* &other);

public:
  //Balancing Methods
  //----------------------

  /*Balanced function
  * Used to take the subtree and rebalance at a specific node so that it satisfies the balanced property for that subtree
  * This is a recursive function
  */
  void Balance(BST_Node<T,S>* node);

  /* Balanced Delete
  * deletes a element, and rebalances the subtree
  * checks to see if the whole tree is still balanced after the delete
  * if it is not balanced, then it uses the balancing function on the whole tree to balance it
  */
  void Balanced_Delete(S pivot, T element);

  /* Balanced insert
  * Insert a element in to the correct spot
  * checks if the whole tree is balanced, if not, use the balancing function on the whole tree
  */
  void Balanced_Insert(S pivot, T new_element);

private:
  /* Is Balanced function
  * walks through the tree on both sides of the node to check if it is balanced,
  *  checks the heights of the left subtree and the right subtree
  * to determine if it satisfies the balanced tree property for the subtree starting at the node
  */
  bool Is_Balanced(BST_Node<T,S>* node);


  /* Node_list function
  * Takes a subtree and concatenates the ordered list from the left tree and right tree with the "root node" in the middle of them
  */
  std::vector<BST_Node<T,S>*> Node_list(BST_Node<T,S>* node);

  /* Balance_Node
  * Takes in a list of nodes that are ordered
  * the root_node is the middle node in the ordered list of nodes
  * middle index corresponds to the middle index of the middle node
  * this is a recursive function
  */
  void Balance_Node(std::vector<BST_Node<T,S>*> &nodes, BST_Node<T,S>* root_node,int &middle_index);

  /* Depth Function
  * determines the largest depth as it walks down the Tree from this node
  * this is recursive as it goes through both left and right
  * and finds the max.
  */
  int Depth(BST_Node<T,S>* node);

};


//BST_Node Methods
//----------------------------------------------------
//Copy constructor
template<class T,class S>
inline BST_Node<T,S>::BST_Node(const BST_Node<T,S> &other):Left_Node(nullptr),Right_Node(nullptr),Parent_Node(nullptr)
{
  //Set the data as the same
  this->data=other.data;

}

//Copy Assignment operator
template<class T,class S>
inline BST_Node<T,S>& BST_Node<T,S>::operator=(const BST_Node<T,S> &other)
{
  //assign the data
  this->data=other.data;

  //Assign the pointers to the correct pointers
  this->Parent_Node=other.Parent_Node;
  this->Right_Node=other.Right_Node;
  this->Left_Node=other.Left_Node;

  return *this;
}

//Destructor
template<class T,class S>
inline BST_Node<T,S>::~BST_Node()
{
  if(this->Left_Node!=nullptr)
  {
    delete this->Left_Node;
    //redefine the pointer to be NULL
    this->Left_Node=nullptr;
  }
  if(this->Right_Node!=nullptr)
  {
    delete this->Right_Node;
    this->Right_Node=nullptr;
  }
}




//BST Methods
//-----------------------------------------------------
//Copy Constructor
template<class T,class S>
inline BST<T,S>::BST(const BST<T,S> &other)
{
  //Initilize new memory for the root
  BST_Node<T,S>* temp_root=new BST_Node<T,S>;
  //copy the data
  temp_root->data=other.Root_Node->data;
  this->Root_Node=temp_root;

  //Start the process of copy the children over
  _Copy_init_(this->Root_Node,other.Root_Node);

}

//copy Assignment operator
template<class T,class S>
inline BST<T,S>& BST<T,S>::operator=(const BST<T,S> &other)
{
  this->Root_Node=other.Root_Node;

  return *this;
}


//Deconstructor
template<class T,class S>
inline BST<T,S>::~BST()
{
  /* This is recursive,
  * once we delete the root node, the destructor will be called on the pointers, and delete objects they are pointing
  * to, and so on.
  */
  if(Root_Node!=nullptr)
  {
    delete Root_Node;
    Root_Node=nullptr;     //Whenever deleting something, make it null to make sure we don't get any errors
  }
  //otherwise do nothing, since it is already deleted

}

//Methods
//----------------------------------------

//(non-balancing) insert function
template<class T, class S>
void BST<T,S>::Insert(S pivot, T new_element)
{
    if(this->Root_Node==nullptr)                        //if the root node is empty, put the first element there
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

//(non-balancing) overloaded insert function with no new element
template<class T,class S>
void BST<T,S>::Insert(S pivot)
{
  if(this->Root_Node==nullptr)                        //if the root node is empty, put the first element there
  {
    BST_Node<T,S>* temp_pointer = new BST_Node<T,S>;
    temp_pointer->pivot=pivot;
    Root_Node=temp_pointer;
  }
  else
  {
    Search_Compare_Point(Root_Node,pivot);  //otherwise go to the left or right of the node
  }
}



//---------------------------------------------------------------
//(non-balancing) delete function
template<class T, class S>
void BST<T,S>::Delete(S pivot,T element)
{
  BST_Node<T,S>* to_be_deleted;
  to_be_deleted=Search(Root_Node,pivot,element);        //Search for the node that we are going to delete





  //Next, we need to search in the right children tree for the smallest element with the given ordering to replace the spot we deleted
  if(to_be_deleted->Right_Node==nullptr)                      //Check if the left node has anything, if not, then less operations we need to do when deleting
  {
    if(to_be_deleted->Left_Node==nullptr)                //check to see if we need to do anything extra when we delete
    {
      delete to_be_deleted;                           //delete the node and do nothing
      return;
    }
    else
    {
      if(to_be_deleted->Parent_Node->Left_Node == to_be_deleted)               //we need to check which side of the parent node to_be_deleted is on
      {
        to_be_deleted->Parent_Node->Left_Node=to_be_deleted->Left_Node;        //If its the left node, then replace that pointer with the to_be_deleted pointer to its children on the left side

        to_be_deleted->Left_Node=nullptr;     //Make sure we don't delete everything under it
        to_be_deleted->Right_Node=nullptr;    //Since the destructor will delete them recursivly
        delete to_be_deleted;
        return;
      }
      else
      {
        to_be_deleted->Parent_Node->Right_Node=to_be_deleted->Left_Node;       //Same thing, but on the right node pointer for its parent

        to_be_deleted->Left_Node=nullptr;      //Make sure we don't delete everything under it
        to_be_deleted->Right_Node=nullptr;    //Since the destructor will delete them recursivly
        delete to_be_deleted;
        return;
      }
    }
  }
  else
  {
    //when there is children in the right node, we need to search for the smallest node, which means we need to travel through the left turns beginning at the first right node child of to_be_deleted
    BST_Node<T,S>* iterator = to_be_deleted->Right_Node;
    //walk through the left nodes till we stop
    //There is a case where there is no left turns, which we handle below
    while(iterator->Left_Node != nullptr)
    {
      iterator= iterator->Left_Node;
    }

    //If the right node is null, then just replace the deleted spot by this most left node
    if(iterator->Right_Node==nullptr)
    {
      to_be_deleted->data = iterator->data;

      iterator->Left_Node=nullptr;            //Make sure we do not delete everything under the node that this points to
      iterator->Right_Node=nullptr;           //since the destructor is recursive
      delete iterator;

    }
    else if(iterator!=to_be_deleted->Right_Node)           //Otherwise, we have to connected its right node stuff to the parent of the iterator spot
    {
      to_be_deleted->data = iterator->data;
      iterator->Parent_Node->Left_Node=iterator->Right_Node;           //Let the parent node of the iterator point to the right node of the iterator, so we dont lose this connection

      iterator->Left_Node=nullptr;            //Make sure we do not delete everything under the node that this points to
      iterator->Right_Node=nullptr;           //since the destructor is recursive
      delete iterator;

    }
    else      //This is the case, where the iterator did not even move (which means the right node of the to be deleted does not have a left node)
    {
      //replace the to be deleted by its right node


      iterator->Left_Node=iterator->Parent_Node->Left_Node;   //Make sure we dont lose all the nodes on the left

      iterator->Parent_Node=iterator->Parent_Node->Parent_Node; //connect this node to the parent of the to_be_deleted

      if(iterator->Parent_Node==nullptr)
      {
        this->Root_Node=iterator;         //this is the case when we are deleting the main root node
      }

      to_be_deleted->Left_Node=nullptr;      //Make sure we don't delete everything under it
      to_be_deleted->Right_Node=nullptr;    //Since the destructor will delete them recursivly
      delete to_be_deleted;

    }
  }
}


//-----------------------------------------------------
//Search function
template<class T, class S>
BST_Node<T,S>* BST<T,S>::Search(BST_Node<T,S>* &node, S pivot,T element)
{

    if(node->pivot>pivot && node->Left_Node != nullptr)
    {
      return Search(node->Left_Node, pivot, element);
    }
    else if(node->pivot < pivot && node->Right_Node != nullptr)
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
      return nullptr;
    }
}


//---------------------------------------------
//Is Empty Function
template<class T,class S>
inline bool BST<T,S>::Is_Empty()
{
  if(this->Root_Node!=nullptr)
  {
    return false;
  }
  else
    return true;
}



//-----------------------------------------------------
//Search_Compare_Point function
template<class T, class S>
void BST<T,S>::Search_Compare_Point(BST_Node<T,S>* &node,S pivot, T element)
{
  if(node->pivot> pivot)          //If the element is less then the data of node, then search left of the node for a spot
  {
    if(node->Left_Node==nullptr)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->data[element]=element;
      node_p->pivot=pivot;
      node_p->Parent_Node=node;                                //Input the data for new node
      node->Left_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(node->Left_Node,pivot,element);
  }

  if(node->pivot<pivot)          //If the element is greater then the data of node, then search right of the node for a spot
  {
    if(node->Right_Node==nullptr)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->data[element]=element;
      node_p->pivot=pivot;
      node_p->Parent_Node=node;                               //Input the data for new node
      node->Right_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(node->Right_Node,pivot,element);
  }
  if(node->pivot==pivot)                                                   //If the pivot is the same, then add the data in the same spot
  {
    node->data[element]=element;
    return;
  }
}





//--------------------------------------------------
//Overloaded Search compare point function that does not add new elements
template<class T, class S>
void BST<T,S>::Search_Compare_Point(BST_Node<T,S>* &node,S pivot)
{
  if(node->pivot> pivot)          //If the element is less then the data of node, then search left of the node for a spot
  {
    if(node->Left_Node==nullptr)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->pivot=pivot;
      node_p->Parent_Node=node;                                //Input the data for new node
      node->Left_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(node->Left_Node,pivot);
  }

  if(node->pivot<pivot)          //If the element is greater then the data of node, then search right of the node for a spot
  {
    if(node->Right_Node==nullptr)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->pivot=pivot;
      node_p->Parent_Node=node;                               //Input the data for new node
      node->Right_Node=node_p;
      return;
    }
    else
      Search_Compare_Point(node->Right_Node,pivot);
  }
  if(node->pivot==pivot)                                                   //If the pivot is the same, then add the data in the same spot
  {
    return;
  }
}


//-------------------------------------------------
//Copy initilzer function
template<class T,class S>
void _Copy_init_(BST_Node<T,S>* &node,const BST_Node<T,S>* &other)
{
  //First, node has already been allocated in the last step and connected with its newly allocated parent as well
  //process the left node
  if(other->Left_Node!=nullptr)
  {
    //Initalize new memory for the new left node
    BST_Node<T,S>* left_temp=new BST_Node<T,S>;
    left_temp->data=other->Left_Node->data;
    //Point to the parent node
    left_temp->Parent_Node=&node;
    //Set the left node pointer as this new pointer
    node->Left_Node=left_temp;

    //do the same for its children
    _Copy_init_(node->Left_Node,other->Left_Node);


  }
  //process the right node
  if(other->Right_Node!=nullptr)
  {
    //Initalize new memory for the new left node
    BST_Node<T,S>* right_temp=new BST_Node<T,S>;
    right_temp->data=other->Right_Node->data;
    //Point to the parent node
    right_temp->Parent_Node=&node;
    //Set the left node pointer as this new pointer
    node->Right_Node=right_temp;

    //Do the same for its children
    _Copy_init_(node->Right_Node,other->Right_Node);

  }

  return;

}


//Balancing Functions
//-----------------------------------
//Node_list function
template<class T, class S>
std::vector<BST_Node<T,S>*> BST<T,S>::Node_list(BST_Node<T,S>* node)
{
  std::vector<BST_Node<T,S>*> result;            //Resulting list that we will send up through the tree


  if(node->Left_Node != nullptr)
  {
    std::vector<BST_Node<T,S>*> left_result;
    left_result=Node_list(node->Left_Node);

    //We will be inserting the left_result information at the end of the result list.
    auto it=result.end();
    result.insert(it, left_result.begin(), left_result.end());

  }

  //Insert the main node in the middle of the list
  result.push_back(node);

  if(node->Right_Node != nullptr)
  {
    std::vector<BST_Node<T,S>*> right_result;
    right_result = Node_list(node->Right_Node);

    //Insert the right_result information at the end of the result list
    auto it=result.end();
    result.insert(it,right_result.begin(),right_result.end());
  }

  return result;
}

//-------------------------------------------
//Balancing function
template<class T,class S>
void BST<T,S>::Balance(BST_Node<T,S>* node)
{
  std::vector<BST_Node<T,S>*> ordered_list;

  //First, find the ordered list from smallest to largest for the subtree with "root node" at node
  ordered_list=Node_list(node);
  int middle_index = (int)ordered_list.size()/2;

  //If the node we put in is the root node, we need to do something more special
  //since the Root_Node element is a pointer, so we need to actually change this pointer
  //otherwise, we will lose the entire Tree
  if(node==this->Root_Node)
  {
    //Set this parents node to NULL
    ordered_list[middle_index]->Parent_Node=nullptr;
    //look for the middle one, and set it equal to this pointer
    this->Root_Node=ordered_list[middle_index];
    Balance_Node(ordered_list,this->Root_Node,middle_index);
  }
  else
  {
    //Set the parent of the new "rood node" to be the parent of the old "rood node"
    ordered_list[middle_index]->Parent_Node=node->Parent_Node;

    //Next, point the correct left or right node of the parent to the new "rood node"
    if(node->Parent_Node->Left_Node==node)
    {
      ordered_list[middle_index]->Parent_Node->Left_Node=ordered_list[middle_index];
    }
    else
    {
      ordered_list[middle_index]->Parent_Node->Right_Node=ordered_list[middle_index];
    }
    //Next, Balance the node
    Balance_Node(ordered_list,ordered_list[middle_index],middle_index);
  }


}


//---------------------------------------------------
//Balancing function at a node
template<class T,class S>
void BST<T,S>::Balance_Node(std::vector<BST_Node<T,S>*> &nodes,BST_Node<T,S>* root_node,int &middle_index)
{

  //The "root node" for the left subtree
  int left_middle_index=(int)(middle_index)/2;

  //the "root node" for the right subtree
  int right_middle_index=(int)(nodes.size()+middle_index)/2;


  if(left_middle_index != middle_index)                  //Check if there is anymore elements to the left of the middle element
  {
    //point the "root nodes" left child to middle of the left section of the list
    root_node->Left_Node=nodes[left_middle_index];
    nodes[left_middle_index]->Parent_Node=root_node;


    std::vector<BST_Node<T,S>*> left_section_nodes;
    auto it_l = left_section_nodes.begin();
    //insert the right section of the whole list in to this new list
    left_section_nodes.insert(it_l,nodes.begin(), nodes.begin()+middle_index);
    //Process through the same function, but now for the elements less then the middle element
    Balance_Node(left_section_nodes,root_node->Left_Node,left_middle_index);
  }
  else
  {
    root_node->Left_Node=nullptr;
  }


  if(right_middle_index != middle_index)              //check if there is anymore elements to the right of the middle element
  {
    //point the "root node" right child to the middle of the right section of the list
    root_node->Right_Node=nodes[right_middle_index];
    nodes[right_middle_index]->Parent_Node=root_node;

    //Also, do the same for the right section
    std::vector<BST_Node<T,S>*> right_section_nodes;
    auto it_r = right_section_nodes.begin();
    //Process through the same function, but now for the elements greater then the middle element

    //Now construct a new list of ordered nodes, starting from the right neighbor of the middle index node
    right_section_nodes.insert(it_r,nodes.begin()+middle_index+1, nodes.end());
    //We need to change the location of the right middle index, since we tranlsated the right section the old nodes list by middle_index+1 to the left
    right_middle_index=right_middle_index-middle_index-1;
    //NOw process this new right subtree
    Balance_Node(right_section_nodes,root_node->Right_Node,right_middle_index);
  }
  else
  {
    root_node->Right_Node=nullptr;
  }


}

//----------------------------------------------------
//Balanced deleting function
template<class T,class S>
void BST<T,S>::Balanced_Delete(S pivot, T element)
{

  //Search for the node where this pivot and element is
  BST_Node<T,S>* node=Search(this->Root_Node,pivot,element);

  //order the list of nodes under this node
  std::vector<BST_Node<T,S>*> list=Node_list(node);

  //Next, remove the node that corresponds to the original node
  int counter=0;
  while(list[counter] != node)
  {
    counter+=1;
  }

  //Delete the node corresponding to the counter
  std::vector<BST_Node<T,S>*> new_list;
  new_list.reserve(list.size()-1);
  if(counter==0)
  {
    auto it=new_list.begin();
    new_list.insert(it,list.begin()+1,list.end());
  }
  else
  {
    auto it=new_list.begin();
    new_list.insert(it,list.begin(),list.begin()+counter);
    it=new_list.begin();
    new_list.insert(it+counter,list.begin()+counter+1,list.end());
  }

  //FInd the middle index of this new list, which will become the new "root node"
  int middle_index =(int)new_list.size()/2;

  //connect the parent nodes between the original "root node" and the original which is going to be deleted
  new_list[middle_index]->Parent_Node=node->Parent_Node;
  //also, we need to make sure the parent nodes correctly points to the new "root node"
  if(node->Parent_Node!=nullptr)
  {
    if(node->Parent_Node->Left_Node==node)
    {
      new_list[middle_index]->Parent_Node->Left_Node=new_list[middle_index];
    }
    else
    {
      new_list[middle_index]->Parent_Node->Right_Node=new_list[middle_index];
    }
  }
  else
  {
    //This implies it is the root node of the entire tree, hence, we need to make sure the rootnode of BST points to the correct spt
    this->Root_Node=new_list[middle_index];
  }
  //Now, we can delete the original node, since we have passed on all of the important pointers we needed
  delete node;
  //now, we can balance the subtree with new "root node"
  Balance_Node(new_list,new_list[middle_index],middle_index);

  if(Is_Balanced(this->Root_Node)==false)
    Balance(this->Root_Node);

}



//--------------------------------------------------
//Balanced Insertion function
template<class T,class S>
void BST<T,S>::Balanced_Insert(S pivot, T element)
{
  Insert(pivot,element);
  if(Is_Balanced(this->Root_Node)==false)
    Balance(this->Root_Node);

}

template<class T,class S>
int BST<T,S>::Depth(BST_Node<T,S>* node)
{
  int max_depth=0;
  int left_depth=0;
  int right_depth=0;

  if(node!= nullptr)
  {
    if(node->Left_Node != nullptr)             //find the depth of the left node
    {
      left_depth=Depth(node->Left_Node);
    }
    if(node->Right_Node != nullptr)            //find the depth for the right node
    {
      right_depth=Depth(node->Right_Node);
    }

    if(left_depth>=right_depth)         //Determine which one is bigger and add one to it to get the max_depth;
    {
      max_depth=left_depth+1;
    }
    else
    {
      max_depth=right_depth+1;
    }
    return max_depth;

  }
  else
  {
    return 0;
  }

}


//------------------------------------
//Checks if the subtree is balanced function
template<class T,class S>
bool BST<T,S>::Is_Balanced(BST_Node<T,S>* node)
{
  bool left_tree=true;
  bool right_tree=true;

  if(node!=nullptr)
  {
    //Check both subtrees, so see if those are balanced
    if(node->Left_Node!=nullptr)
    {
      left_tree=Is_Balanced(node->Left_Node);
    }
    if(node->Right_Node!=nullptr)
    {
      right_tree=Is_Balanced(node->Right_Node);
    }


    if((right_tree==false) || (left_tree==false))
    {
      return false;
    }
    else if(std::abs(Depth(node->Left_Node)-Depth(node->Right_Node))>=2)
    {
      return false;
    }
    else
    {
      return true;
    }
  }
  else
  {
    return true;
  }


}


#endif
