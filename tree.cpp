/////////////////////////////////////////
///////   Marc Week sample C++  code ////
///////                              ////
///////                              ////
/////////////////////////////////////////

/* 

This program manages"simulates" messages from a varitey of different type of communication channels. Phone, email and facebook

It contains a class of persons contact ifnro which is conatined in array, mssages are contained in an AVL tree in. 
all structures are managed with a class that contained two AVLs and a contact list.
operator overloading was used in all classes to make the implientaion eaiser

This section is the implimetation of the tree AVL structure types


*/



#include "message.h"



using namespace std;

//constructor for the messages
message::message(): name(NULL), address(NULL), text(NULL){}


//messenger constructor with arguments 
message::message(char * newname, char * newaddress, char * newtext)
{
   if (newname)
   {
     name = new char[strlen(newname)+1];
     strcpy(name, newname);
   }
   if (newaddress)
   {
     address = new char[strlen(newaddress)+1];
     strcpy(address, newaddress);
   }
   if (newtext)
   {
     text = new char[strlen(newtext)+1];
     strcpy(text, newtext);
   }
}

//messanger copy constructor
message::message(message * newmessage)
{
  if (newmessage->name)
   {
     name = new char[strlen(newmessage->name)+1];
     strcpy(name, newmessage->name);
   }
   if (newmessage->address)
   {
     address = new char[strlen(newmessage->address)+1];
     strcpy(address, newmessage->address);
   }
   if (newmessage->text)
   {
     text = new char[strlen(newmessage->text)+1];
     strcpy(text, newmessage->text);
   }
}

//deconstructor
message::~message()
{
 if (name) delete [] name;
 if (address) delete [] address;
 if (text) delete [] text;
}


//boolean equals operator internal
message & message::operator=(message newmessage)
{
  if (this == &newmessage) return *this;
  if (name) delete[] name;
  if (newmessage.name)
   {
     name = new char[strlen(newmessage.name)+1];
     strcpy(name, newmessage.name);
   }
  if (address) delete [] address;
   if (newmessage.address)
   {
     address = new char[strlen(newmessage.address)+1];
     strcpy(address, newmessage.address);
   }
  if (text) delete []text;
   if (newmessage.text)
   {
     text = new char[strlen(newmessage.text)+1];
     strcpy(text, newmessage.text);
   }
}



//booloean equals freind function
bool message::operator == (const message & m) 
{
   if (!strcmp(name, m.name) && !strcmp(address, m.address) && !strcmp(text, m.text)) return true;
   else return false;
}
bool operator == (const message & m, const message & n) 
{
   if (!strcmp(n.name, m.name) && !strcmp(n.address, m.address) && !strcmp(n.text, m.text)) return true;
   else return false;
}


//operator overloaded output function
ostream& operator << (ostream& out, const message & m)
{
  cout << "Name: ";
  cout.width(15);
  cout << left<< m.name; 
  cout << "Address: ";
  cout.width(20);
  cout <<left  << m.address;
  cout << "Message: ";
  cout.width(20);
  cout << left << m.text;
  cout << endl;
}


//tree node default constructor
node::node() : message(), left(NULL), right(NULL) {}

//message constructor with message argument
node::node(message * newmessage) : message(newmessage), left(NULL), right(NULL){}

//message copy constructor
node::node(node * newnode): message(newnode->name, newnode->address, newnode->text), left(NULL), right(NULL)
{
}

//message lessthan operator function
bool message::operator < (const message & m)
{
  if (strcmp(name, m.name) < 0) return true;//just checks name
  return false;
}


//node deconstructor
node::~node()
{
  right = left = NULL;
}


//traverses to the left node pointer
node *& node::goleft()
{
  return left;
}

//traverses to the right node pointer
node *& node::goright()
{

  return right;
}

//sets the left node pointer
void node::setleft(node * newleft)
{

   left = newleft;

}

//set the right node pointer
void node::setright(node * newright)
{
   right = newright;
}




//tree default constructor
tree::tree(): root(NULL) {}


//tree copy constructor
tree::tree(const tree * newtree)
{
  copytree(root, newtree->root);
}


//tree deconstructor
tree::~tree()
{  
  removeall(root);
}


//reemove all the trees nodes
void tree::removeall(node *& root)
{
  if (!root) return;
  removeall(root->goleft());
  removeall(root->goright());
  delete root;
}

//copys over the tree
int tree::copytree(node *& copied, node * source)
{
  if (!source)
  {
    copied = NULL;
    return 0;
  }
  copied = new node(source);
  copytree(copied->goleft(), source->goleft());
  copytree(copied->goright(), source->goright());
}

//operator to copytree
tree& tree::operator= (const tree & newtree)
{
  if (root) removeall(root);
  copytree(root, newtree.root);
}

//displays the entire tree in name order
int tree::displayall(node * root) const
{
  if (!root) return 0;
  displayall(root->goleft());
  cout  << *root;
  displayall(root->goright());
  return true;
}


//adds a message node in name order
int tree::addmessage(node * root, message * newmessage)
{
  if(!root)
  {
   root = new node(newmessage);
   return 1;
  }
   if (newmessage < root)
     addmessage(root->goleft(), newmessage);
   else addmessage(root->goright(), newmessage);   
}





//default conrtsuctor for the AVL tree
BST::BST(): tree() {}


//adds a message to AVL tree in operator overloaded
BST& BST::operator+=( message & newmessage)
{
  addmessage(root, &newmessage);
}


//return the height of a node in the tree
int BST::height(node * root)
{
 if (!root) return 0;
 int leftheight = height(root->goleft());
 int rightheight = height(root->goright());
 if (leftheight > rightheight) return 1 + leftheight;
 else return 1 + rightheight;
}

//returns the balance factor of the node > 0  left heavy, < 0 is right heavy
int BST::balancefactor(node * root)
{
  if (!root) return 0;
  return height(root->goleft()) - height(root->goleft()); 
}


//rotaes to the leff for right heavy
int BST::rotateleft(node *& root)
{
  if(!root) return 0;
  node * temp1 = root;
  node * temp2 = temp1->goright()->goleft();  
  root = temp1->goright();
  root->goleft()->setright(temp2);
  root->goright()->setleft(NULL);
}


//rotates to the right for left heavy
int BST::rotateright(node *& root)
{
  if(!root) return 0;
  node * temp1 = root;
  node * temp2 = temp1->goleft()->goright();
  root = temp1->goleft();
  root->goright()->setleft(temp2);
  root->goleft()->setright(NULL);
}


//rotates doubly for left heavy and leftnode is right heavy
int BST::doubleright(node *& root)
{
  node * temp = root;
  root = temp->goleft()->goright();
  root->setleft(temp->goright());
  temp->setleft(NULL);
  root->goleft()->setright(NULL);

} 


//roattes to the right heavy and right node is left heavy
int BST::doubleleft(node *& root)
{
  if (!root) return 0;
  node * temp = root;
  root = temp->goright()->goleft();
  root->setright(temp->goleft());
  temp->setright(NULL);
  root->goright()->setleft(NULL);
}


//adds message recursivily and returns and then balances on the way bact to the top root.
int BST::addmessage(node *& root,  message * newmessage)
{  
  if(!root)
  {
   root = new node(newmessage);
   return 1;
  }
   if (*newmessage < root)
      addmessage(root->goleft(), newmessage);
   else addmessage(root->goright(), newmessage);
   
   int balfac = balancefactor(root);
   if (balfac > 1)//if left heavy
   {
    if(balancefactor(root->goleft()) > 0)//if the right root is right heavy
      rotateright(root);
    else                                 //if the right root is left heavy
      doubleright(root);
   }
   if (balfac < -1)
   {
     if (balancefactor(root->goright()) < 0)//if the left root is left heavy
       rotateleft(root);
     else                                  // if the left root is right heavy
       doubleleft(root);
   } 
}

//outputs the entire tree in name order
int BST::displayall()const
{
 return tree::displayall(root);
}


//operator overloaded output
ostream& operator<< (ostream& out, const  BST & t)
{
   if (!t.displayall()) cout << "NONE\n";
}


