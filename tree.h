/////////////////////////////////////////
///////   Marc Week sample C++  code ////
///////                              ////
///////                              ////
/////////////////////////////////////////

/* 

This program manages"simulates" messages from a varitey of different type of communication channels. Phone, email and facebook

It contains a class of persons contact ifnro which is conatined in array, messages are contained in an AVL tree in. 
all structures are managed with a class that contained two AVLs and a contact list.
operator overloading was used in all classes to make the implientaion eaiser

This is the tree set of classes it conatins messages and nodes that make up the AVL balanced tree


*/


using namespace std;



//This class manages messages
class message
{
  public:
    message();
    message(char * newname, char * newaddress, char * text);//message constructor with arguments
    message(message * newmail);//copy constructor
    ~message();
   
    message& operator= (message newmessage);//deep copies a messade to another
    bool operator== (const message & m);//tells if the messages the same
    friend bool operator== (const message & m, const message & n);//friend operatior overloader function for testing if the message is the same
    friend ostream& operator<< (ostream&, const message &);//outputs the message
    bool operator < (const message & m);//tells if the messages is less than the previus. note USE "ELSE" for => 
  protected:
    
    char * name;//name of the sender
    char * address;//address of the sender
    char * text;//text of message
    
};


//this is  the tree node for the messages it is inherited from the message class
class node : public message
{
  public:
   node();
   node(message * newmessage);//constructor for the node with messae argument
   node(node * newnode);//copy constutor
   ~node();
   node *& goleft();//returns the left pointer
   node *& goright();//returns the right pointer
   int returnhight();//retuens the the overall hight of a patyiclar node in the tree
   void setleft(node * newleft);//sets the left pointer to a node
   void setright(node * newright);//sets the right pointer to a node
   void sethight(int newhight);
  protected:
    node * left;
    node * right; 
};



//this a basic binary search tree which sets as a foundation for the AVL tree BST
class tree
{
  public:
    tree();
    tree(const tree * newtree);//copy constructor
    ~tree();
    tree & operator= (const tree & newtree);//copys  the entire tree
  protected:
    int addmessage(node * root, message * newmessage);//ads a message to the tree
    int displayall(node * root) const;//displays the entire tree in alphabetic order based on name
    int copytree(node *& copied, node * source);//copies of the tree
    void removeall(node *& root);// removes all the nodes
    node * root;  
};

//this a a AVL tree thats inhericted from the tree class it self balanced based on height of each node
class BST : public tree
{
   public:
     BST();
     
     BST& operator= (const tree &);//operatorfunction to copy the tree
     BST& operator+= (message & newmessage);//adds a new node to the tree
     friend ostream& operator<<(ostream& out, const BST & t);//outputs the entire tree
     int displayall()const;//displays the entire tree
   protected:
     int balancefactor(node * root);//checks to see if the nodes is balaned > 0  is left heavy whilee < 0 us  right heavy
     int rotateleft(node *& root);// single left roatation of the 3 a node that needs balanced
     int rotateright(node *& root); //single riht rotaion of a node thae needs balancing
     int doubleright(node *& root);//Double rotaion of a node tha needs balancing to the right
     int doubleleft(node *& root);//double rotaion to the left
     int height(node * root);//gets the overall height of the hode
     int addmessage(node *&root,  message * newmessage);//adds a node and self balanced on the return from recursive call.
     
};
