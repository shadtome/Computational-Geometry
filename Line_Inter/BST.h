#ifndef BST_H
#define BST_H


#include <iostream>
#include <map>
#include <cstdlib>
#include <stack>
#include <memory> //Maybe use smart pointers, but a little bit of overhead




/* The big question I have, I am not sure if a smart pointer is useful here or not.
* I know where all created objects are from new here, and delete them accordly in the destructors,
* but what if there is a bad_alloc that gets thrown in the destructor.  I am not sure what to do with this.
* If I use smart pointers, this will make is more exception safe, in that new allocated memory wont leak.
*/

/*
Binary Search tree Templated Class
*This takes in class T (the data), class S (Pivot), and a compare class between elements in T for the std::map
* Has functions for balancing and not balancing for insert and delete.
*/



//Forward declare the BST class
//and the iterator class
template<class T,class S>
class BST;
template<class T,class S>
class BSTIterator;

enum Side_of_Tree { CENTER_T,LEFT_T,RIGHT_T };

//Binary Search tree for the Event Queue and the Status record
template<class T, class S>
struct BST_Node
{
  friend BST<T,S>;                 //Let the BST access its nodes
public:
  S pivot;                         // pivot point of the node
  std::map<T,T> data;              //where we store the data for this node
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

};

template <class T,class S>
class BST
{
  friend BSTIterator<T,S>;     //Iterator class
  //declare types this class uses
  typedef BSTIterator<T,S> iterator;
  typedef const BSTIterator<T,S> const_iterator;

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
  Side_of_Tree Insert(S pivot);

  /* (Non-Balancing) delete
  * Deletes element in the node from the specified pivot.
  * by just finding the most left element in the right subtree
  * DOES NOT DELETE THE NODE
  */
  void Delete(S pivot, T element);

  /* (non-Balancing) delete (overloaded)
  * Deletes the node corresponding to this pivot element
  */
  Side_of_Tree Delete(S pivot);

  //Search Function
  /*
  * Node is where the search starts
  * Then check left and right subtrees starting from this node
  * for the element with pivot S and searchs in that pivot for the element
  */
  BST_Node<T,S>* Search(BST_Node<T,S>* &node,S pivot, T element);

  /* Search function
  * Finds the node with a certain pivot
  * Node is where the search starts
  * Then check left and right subtrees starting from this node
  * for the elemtn with pivot S
  */
  BST_Node<T,S>* Search(BST_Node<T,S>* &node,S pivot);

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
  Side_of_Tree Search_Compare_Point(BST_Node<T,S>* &node,S pivot);

  /* Initalize for the copy constructor
  * Used to allocate new BST with the copied information
  * this is recursive
  */
  void _Copy_init_(BST_Node<T,S>* &node,const BST_Node<T,S>* &other);

public:
  //Balancing Methods
  //----------------------

  /*Balanced function
  * Used to take the subtree and rebalance at a specific node so that it satisfies the balanced property for that subtree
  * This is a recursive function
  */
  void Balance(BST_Node<T,S>* node);

  /* Balanced Delete
  * deletes a element
  * DOES NOT DELETE NODE
  * so hence it is balanced already.
  */
  void Balanced_Delete(S pivot, T element);

  /* Overloaded Balanced Delete
  * Deletes a node
  i.e.        7
          5       9
      3     6   8  <--- deleted.
    2   4

  then apply chain method
              5
          3       7
        2   4   6     9


  Then move the chain like so
  */
  void Balanced_Delete(S pivot);

  /* Balanced insert
  * Insert a element in to the correct spot
  * If no node exists, then insert a new node and balances it using chain method
  */
  void Balanced_Insert(S pivot, T new_element);

  /* Overloaded Balanced insert
  * Inserts a new node
  * Checks if the whole tree is balanced, if not, then use the chain trick and move the chain of trees away from the inserted spot.
  * i.e.      7
          5       9
      3     6   8     10
    2   4
  1  <--newly inserted

  Then move the chain like so
              5
          3       7
      2     4   6     9
    1               8    10
* this gets us a balanced tree.
*/
void Balanced_Insert(S pivot);


  /* Node_list function
  * Takes a subtree and concatenates the ordered list from the left tree and right tree with the "root node" in the middle of them
  */
  std::vector<BST_Node<T,S>*> Node_list(BST_Node<T,S>* &node);

private:
  /* Is Balanced function
  * walks through the tree on both sides of the node to check if it is balanced,
  *  checks the heights of the left subtree and the right subtree
  * to determine if it satisfies the balanced tree property for the subtree starting at the node
  */
  bool Is_Balanced(BST_Node<T,S>* node);



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

public:
  //Iterator functions

  //Points to beginning
  iterator begin()
  {
    return BSTIterator<T,S>(this->Root_Node);
  }

  //Const iterator
  const_iterator cbegin()const
  {
    const BSTIterator<T,S> temp(this->Root_Node);
    return temp;
  }

  //points to the end
  iterator end()const
  {
    return BSTIterator<T,S>(nullptr);
  }

  //points to the end
  const_iterator cend()const
  {
    const BSTIterator<T,S> temp(nullptr);
    return temp;
  }
};



//--------------------------------------
/*
* This is the BST iterator class, which uses inorder traversal with stacks.
*/
template<class T,class S>
class BSTIterator
{

  //Stack for the iterator
  std::stack<BST_Node<T,S>*> stack;
  //Pointer to the location of the node
  BST_Node<T,S>* cur_node;
public:
  //Constructor
  BSTIterator(BST_Node<T,S>* p);
  //Copy Constructor
  BSTIterator(const BSTIterator &other):cur_node(other.cur_node),stack(other.stack){};
  //preiterate operator
  BSTIterator& operator++();

  //Post iterate operator
  BSTIterator operator++(int)
  {
    BSTIterator temp(*this);
    ++(*this);
    return temp;
  }

  //Equality relation
  bool operator==(const BSTIterator& other)const;
  //Not equal relation
  bool operator!=(const BSTIterator& other)const;
  //dereference operator
  BST_Node<T,S>& operator*()const;
  //Arrow operator
  BST_Node<T,S>* operator->()const;


};


//-------------------------------------------------------------------
//End of Class decelerations



//BST_Node Methods
//----------------------------------------------------
//Copy constructor
template<class T,class S>
BST_Node<T,S>::BST_Node(const BST_Node<T,S> &other):Left_Node(nullptr),Right_Node(nullptr),Parent_Node(nullptr)
{
  //Set the data as the same
  this->data=other.data;

}

//Copy Assignment operator
template<class T,class S>
BST_Node<T,S>& BST_Node<T,S>::operator=(const BST_Node<T,S> &other)
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
BST_Node<T,S>::~BST_Node()
{
  //Delete the contents of this node
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

//-----------------------------------------------------
//End of BST_Node functions


//BST Methods
//-----------------------------------------------------
//Copy Constructor
template<class T,class S>
BST<T,S>::BST(const BST<T,S> &other)
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
BST<T,S>& BST<T,S>::operator=(const BST<T,S> &other)
{
  this->Root_Node=other.Root_Node;

  return *this;
}


//Deconstructor
template<class T,class S>
BST<T,S>::~BST()
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
Side_of_Tree BST<T,S>::Insert(S pivot)
{
  if(this->Root_Node==nullptr)                        //if the root node is empty, put the first element there
  {
    BST_Node<T,S>* temp_pointer = new BST_Node<T,S>;
    temp_pointer->pivot=pivot;
    Root_Node=temp_pointer;
    return CENTER_T;
  }
  else
  {
    return Search_Compare_Point(Root_Node,pivot);  //otherwise go to the left or right of the node
  }
}



//---------------------------------------------------------------
//(non-balancing) delete function
template<class T, class S>
void BST<T,S>::Delete(S pivot,T element)
{
  BST_Node<T,S>* to_be_deleted;
  to_be_deleted=Search(Root_Node,pivot,element);        //Search for the node that we are going to delete

  if(to_be_deleted != nullptr)      //If it is null skip the enire delete and output exception handling
  {
    to_be_deleted->data.erase(element); //I don't want to delete the node (nodes with pivots but no data is fine)
  }


}

//-----------------------------------------------------
//Delete function for the entire Node
template<class T,class S>
Side_of_Tree BST<T,S>::Delete(S pivot)
{
  BST_Node<T,S>* to_be_deleted;
  to_be_deleted=Search(Root_Node,pivot);        //Search for the node that we are going to delete

  //Check which side of the tree this node is on.  This is for the balanced delete
  Side_of_Tree side;
  if(to_be_deleted->pivot<this->Root_Node->pivot)
  {
    side=LEFT_T;
  }
  else if(to_be_deleted->pivot>this->Root_Node->pivot)
  {
    side=RIGHT_T;
  }
  else
  {
    side=CENTER_T;
  }


  if(to_be_deleted!=nullptr)
  {
    if(to_be_deleted->Right_Node!=nullptr)  //Check if the right node is not null
    {

      //we will start searching in the left nodes of the to_be_deleted->Right_Node
      // To find the smallest node in this subtree to replace the to_be_deleted node

      auto it=to_be_deleted->Right_Node;  //Starting point for searching for the smallest element in this subtree
      while(it->Left_Node!=nullptr)
      {
        it=it->Left_Node;   //Iterate to the next left node
      }

      //The it we got is the smallest node in this subtree.
      //Next, replace the spot we are deleting by this node "it"

      if(it!=to_be_deleted->Right_Node)
      {

        if(it->Right_Node!=nullptr)
        {
          //we need to connect the right node of the "it" spot with the parent of "it"
          it->Parent_Node->Left_Node=it->Right_Node;
          //Connect the "it"'s rights nodes parent with "it"'s parent
          it->Right_Node->Parent_Node=it->Parent_Node;

        }
        else
        {
          it->Parent_Node->Left_Node=nullptr;
        }



        //move the pointers of to_be_deleted to "it".
        it->Left_Node=to_be_deleted->Left_Node;
        it->Right_Node=to_be_deleted->Right_Node;
        it->Parent_Node=to_be_deleted->Parent_Node;

        //Make sure the parent of to_be_deleted points to "it"
        if(to_be_deleted->Parent_Node!=nullptr)
        {
          //check which side of the parent node to_be_deleted is
          if(to_be_deleted->Parent_Node->Right_Node==to_be_deleted)
          {
            it->Parent_Node->Right_Node=it;
          }
          else
          {
            it->Parent_Node->Left_Node=it;
          }
        }
        else
        {
          //This is when we are deleting the root node
          this->Root_Node=it;
        }


        //Before we fully delete, we need to make sure that the left and right nodes of to_be_deleted actually point
        // to it
        if(to_be_deleted->Left_Node!=nullptr)
        {
          to_be_deleted->Left_Node->Parent_Node=it;
        }
        if(to_be_deleted->Right_Node!=nullptr)
        {
          to_be_deleted->Right_Node->Parent_Node=it;
        }

        //Next, disconnect the points on to_be_deleted and delete it
        to_be_deleted->Right_Node=nullptr;
        to_be_deleted->Left_Node=nullptr;
        to_be_deleted->Parent_Node=nullptr;
        delete to_be_deleted;
      }
      else
      {


        //This is the situation when it did not even move, so it is still to_be_deleted->Right_Node
        it->Parent_Node=to_be_deleted->Parent_Node;
        it->Left_Node=to_be_deleted->Left_Node;   //the left node of to_be_deleted->Right_Node=nullptr

        //Make sure the left node of to_be_deleted actually points to it NOw
        if(it->Left_Node!=nullptr)
        {
          it->Left_Node->Parent_Node=it;
        }

        //Connect the parents right/left node to "it"
        if(it->Parent_Node!=nullptr)
        {
          if(it->Parent_Node->Right_Node==to_be_deleted)
          {
            it->Parent_Node->Right_Node=it;
          }
          else
          {
            it->Parent_Node->Left_Node=it;
          }
        }
        else
        { //We are deleting the root node, so hence make sure root connects to "it"
          this->Root_Node=it;
        }



        to_be_deleted->Right_Node=nullptr;
        to_be_deleted->Left_Node=nullptr;
        to_be_deleted->Parent_Node=nullptr;
        delete to_be_deleted;

      }

    }
    else if(to_be_deleted->Left_Node!=nullptr)
    {

      //In this situation, we will look at the left node of to_be_deleted and search for the largest node
      // in this subtree
      auto it=to_be_deleted->Left_Node;
      while(it->Right_Node!=nullptr)
      {
        it=it->Right_Node;        //Iterate to the next right node.
      }

      //Now that we have the biggest node in this subtree, we can replace the
      // to_be_deleted node with the it node and make sure we connect the correct pointers

      if(it!=to_be_deleted->Left_Node)
      {
        //if the left node of it is not nullptr, we need to make sure to connect it with "it"'s parent
        if(it->Left_Node!=nullptr)
        {
          it->Left_Node->Parent_Node=it->Parent_Node;
          it->Parent_Node->Right_Node=it->Left_Node;
        }
        else
        {
          it->Parent_Node->Right_Node=nullptr;
        }

        //Next, we need to transfer the to_be_deleted pointers to "it"
        // Since "it" is going to replace it.
        it->Left_Node=to_be_deleted->Left_Node;
        it->Right_Node=to_be_deleted->Right_Node;
        it->Parent_Node=to_be_deleted->Parent_Node;

        //Next, we need to make sure the parent points to the new "it"
        if(to_be_deleted->Parent_Node!=nullptr)
        {
          if(to_be_deleted->Parent_Node->Right_Node==to_be_deleted)
          {
            it->Parent_Node->Right_Node=it;
          }
          else
          {
            it->Parent_Node->Left_Node=it;
          }
        }
        else
        {
          //this is the situation when we are deleting the root node
          this->Root_Node=it;
        }

        //Before we fully delete, we need to make sure that the left and right nodes of to_be_deleted actually point
        // to "it"
        if(to_be_deleted->Left_Node!=nullptr)
        {
          to_be_deleted->Left_Node->Parent_Node=it;
        }
        if(to_be_deleted->Right_Node!=nullptr)
        {
          to_be_deleted->Right_Node->Parent_Node=it;
        }

        //Next, disconnect to_be_deleted from the tree and delete it
        to_be_deleted->Right_Node=nullptr;
        to_be_deleted->Left_Node=nullptr;
        to_be_deleted->Parent_Node=nullptr;
        delete to_be_deleted;
      }
      else
      {

        //this is the situation when we it did not even move away from to_be_deleted->Left_Node
        it->Parent_Node=to_be_deleted->Parent_Node;
        it->Right_Node=to_be_deleted->Right_Node;   //the right node of to_be_deleted->Left_Node=nullptr

        if(it->Right_Node!=nullptr)
        {
          it->Right_Node->Parent_Node=it;
        }

        //Connect the parents right/left node to "it"
        if(it->Parent_Node!=nullptr)
        {
          if(it->Parent_Node->Right_Node==to_be_deleted)
          {
            it->Parent_Node->Right_Node=it;
          }
          else
          {
            it->Parent_Node->Left_Node=it;
          }
        }
        else
        {
          this->Root_Node=it;
        }


        to_be_deleted->Right_Node=nullptr;
        to_be_deleted->Left_Node=nullptr;
        to_be_deleted->Parent_Node=nullptr;
        delete to_be_deleted;


      }
    }
    else
    {
      //this is the situation we are deleting a node with no left or right nodes
      //this is special since we can just delete it out right,
      //unless it is the root node, which then requires us to make sure the root node becomes null.

      if(to_be_deleted->Parent_Node!=nullptr)
      {
        //make sure the parent node does not point to to_be_deleted anymore
        if(to_be_deleted->Parent_Node->Right_Node==to_be_deleted)
        {
          //disconnect it from the tree
          to_be_deleted->Parent_Node->Right_Node=nullptr;
          delete to_be_deleted;
        }
        else
        {
          to_be_deleted->Parent_Node->Left_Node=nullptr;
          delete to_be_deleted;
        }
      }
      else
      {
        //this is the situation we are deleting the root node and its the last node
        this->Root_Node=nullptr;
        delete to_be_deleted;
      }
    }
  }

  //Lastly, return which side of the root was this element deleted from?
  return side;
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
    else if(node->pivot == pivot && node->data.find(element)!=node->data.end())
    {
      return node;
    }
    else
    {
      std::cout << "No such node/elmemnt exists"<< std::endl;
      return nullptr;
    }
}

//-------------------------------------------------------
//Overloaded search only for the node with certain pivot
template<class T,class S>
BST_Node<T,S>* BST<T,S>::Search(BST_Node<T,S>* &node, S pivot)
{

  if(node->pivot>pivot && node->Left_Node != nullptr)
  {

    return Search(node->Left_Node, pivot);
  }
  else if(node->pivot < pivot && node->Right_Node != nullptr)
  {

    return Search(node->Right_Node,pivot);
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
bool BST<T,S>::Is_Empty()
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
Side_of_Tree BST<T,S>::Search_Compare_Point(BST_Node<T,S>* &node,S pivot)
{
  if(node->pivot> pivot)          //If the element is less then the data of node, then search left of the node for a spot
  {
    if(node->Left_Node==nullptr)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->pivot=pivot;
      node_p->Parent_Node=node;                                //Input the data for new node
      node->Left_Node=node_p;
      return LEFT_T;
    }
    else
    {
      Search_Compare_Point(node->Left_Node,pivot);
      return LEFT_T;
    }

  }
  else if(node->pivot<pivot)      //If the element is greater then the data of node, then search right of the node for a spot
  {
    if(node->Right_Node==nullptr)
    {
      BST_Node<T,S>* node_p= new BST_Node<T,S>;          //Make new node pointer
      node_p->pivot=pivot;
      node_p->Parent_Node=node;
      node->Right_Node=node_p;
      return RIGHT_T;
    }
    else
    {
      Search_Compare_Point(node->Right_Node,pivot);
      return RIGHT_T;
    }

  }
  else                                                   //If the pivot is the same then do nothing
  {
    return CENTER_T;
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
std::vector<BST_Node<T,S>*> BST<T,S>::Node_list(BST_Node<T,S>* &node)
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
  Delete(pivot,element);
}

//---------------------------------------------------
//Overloaded Balanced Delete for deleting entire nodes
template<class T,class S>
void BST<T,S>::Balanced_Delete(S pivot)
{
  Side_of_Tree side=Delete(pivot);
   if(this->Root_Node!=nullptr)
   {
     if(side==RIGHT_T && this->Root_Node->Left_Node!=nullptr)
     {
       //We need to be more careful when searching in the neighborhood of the root node
       BST_Node<T,S>* Old_root=this->Root_Node;
       BST_Node<T,S>* New_root=this->Root_Node->Left_Node;
       //This is to make sure we don't lose our nodes in this process

       //Set the Left node of the old root as the Right node of the new Root
       Old_root->Left_Node=New_root->Right_Node;
       if(Old_root->Left_Node!=nullptr)
       {
         Old_root->Left_Node->Parent_Node=Old_root;
       }

       //Set the Old roots parent as the new root
       Old_root->Parent_Node=New_root;

       //Set the New root's right node as the old root
       New_root->Right_Node=Old_root;

       //Now set the New_root's parent as null and set the root node as the new root
       New_root->Parent_Node=nullptr;
       this->Root_Node=New_root;
     }
     else if(side==LEFT_T && this->Root_Node->Right_Node!=nullptr)
     {
       BST_Node<T,S>* Old_root=this->Root_Node;
       BST_Node<T,S>* New_root=this->Root_Node->Right_Node;
       //This is to make sure we dont't lose our nodes in this process

       //Set the Right node of the old root as the Left node of the new Root
       Old_root->Right_Node=New_root->Left_Node;
       if(Old_root->Right_Node!=nullptr)
       {
         Old_root->Right_Node->Parent_Node=Old_root;
       }

       //Set the Old roots parent as the new root
       Old_root->Parent_Node=New_root;

       //Set the New root's right node as the old root
       New_root->Left_Node=Old_root;

       //Now set the New_root's parent as null and set the root node as the new root
       New_root->Parent_Node=nullptr;
       this->Root_Node=New_root;
     }
     //Otherwise we don't need to use the chain trick since it is balanced.
   }
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

//-----------------------------------------------
//Balanced Insert Function for inserting just nodes
template<class T,class S>
void BST<T,S>::Balanced_Insert(S pivot)
{
  Side_of_Tree side=Insert(pivot);
  //First, lets check if we have a non-empty tree
  if(this->Root_Node!=nullptr)
  {
    if(side==LEFT_T)
    {
      //This means it is safe to search left of the root node,
      // as we inserted something on the left.
      BST_Node<T,S>* Old_root=this->Root_Node;
      BST_Node<T,S>* New_root=this->Root_Node->Left_Node;
      //This is to make sure we don't lose our nodes in this process

      //Set the Left node of the old root as the Right node of the new Root
      Old_root->Left_Node=New_root->Right_Node;
      if(Old_root->Left_Node!=nullptr)
      {
        Old_root->Left_Node->Parent_Node=Old_root;
      }

      //Set the Old roots parent as the new root
      Old_root->Parent_Node=New_root;

      //Set the New root's right node as the old root
      New_root->Right_Node=Old_root;

      //Now set the New_root's parent as null and set the root node as the new root
      New_root->Parent_Node=nullptr;
      this->Root_Node=New_root;
    }
    else if(side==RIGHT_T)
    {
      //this means it is safe to search right of the root node
      BST_Node<T,S>* Old_root=this->Root_Node;
      BST_Node<T,S>* New_root=this->Root_Node->Right_Node;
      //This is to make sure we dont't lose our nodes in this process

      //Set the Right node of the old root as the Left node of the new Root
      Old_root->Right_Node=New_root->Left_Node;
      if(Old_root->Right_Node!=nullptr)
      {
        Old_root->Right_Node->Parent_Node=Old_root;
      }

      //Set the Old roots parent as the new root
      Old_root->Parent_Node=New_root;

      //Set the New root's right node as the old root
      New_root->Left_Node=Old_root;

      //Now set the New_root's parent as null and set the root node as the new root
      New_root->Parent_Node=nullptr;
      this->Root_Node=New_root;
    }
    //otherwise don't do anything since it is already balanced.
  }
}

//----------------------------------------------
//Find the depth of the subtree starting at the node.
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



//------------------------------------------
//Iterator functions









//-------------------------------------------
//End of BST functions

//-------------------------------------------
//BSTIterator functions

//--------------------------------------------------
//Constructor
template<class T,class S>
BSTIterator<T,S>::BSTIterator(BST_Node<T,S>* p)
{
  //First, we need to create the initial stack, starting at the node we inputed.
  BST_Node<T,S>* nodes=p;

  //Traverse the left  subtree, and only put the elements in the left nodes in to the stack
  while(nodes!=nullptr)
  {
    this->stack.push(nodes);
    nodes=nodes->Left_Node;
  }

  //Lets set the cur node as the top of the stack and pop it off of the stack as well
  if(this->stack.empty()==false)
  {
    //Take the top of the stack and desinate it as the current node
    this->cur_node=this->stack.top();
    //Pop off the top of the stack, which corresponds to the current node
    this->stack.pop();

  }
  else
  {
    cur_node=nullptr;
  }
}
//---------------------------------------------------

//---------------------------------------------------
//preiterate operator++
template<class T,class S>
BSTIterator<T,S>& BSTIterator<T,S>::operator++()
{
  //BSTIterator(cur_node->Right_Node);
  if(cur_node!=nullptr)
  {
    if(cur_node->Right_Node!=nullptr)
    {
      BST_Node<T,S>* nodes=cur_node->Right_Node;
      while(nodes!=nullptr)
      {
        this->stack.push(nodes);
        nodes=nodes->Left_Node;
      }
    }
  }


  if(this->stack.empty()==false)
  {
    this->cur_node=this->stack.top();
    this->stack.pop();
  }
  else
  {
    this->cur_node=nullptr;
  }


  return *this;
}

//------------------------------------------------

//------------------------------------------------
//equality relation
template<class T,class S>
bool BSTIterator<T,S>::operator==(const BSTIterator<T,S>& other)const
{
  return this->cur_node==other.cur_node;
}

//------------------------------------------------
//not equal relation
template<class T,class S>
bool BSTIterator<T,S>::operator!=(const BSTIterator<T,S>& other)const
{
  return !(*this==other);
}

//-----------------------------------------------
//Dereference operator
template<class T,class S>
BST_Node<T,S>& BSTIterator<T,S>::operator*()const
{
  return *(this->cur_node);
}

//----------------------------------------------
// arrow operator
template<class T,class S>
BST_Node<T,S>* BSTIterator<T,S>::operator->()const
{

  return &(operator*());
}


//----------------------------------------------
//End of BSTIterator functions


#endif
