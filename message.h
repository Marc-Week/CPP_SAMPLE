/////////////////////////////////////////
///////   Marc Week sample C++  code ////
///////                              ////
///////                              ////
/////////////////////////////////////////


/* 

This program manages"simulates" messages from a varitey of different type of communication channels. Phone, email and facebook

It contains a class of persons contact which is conatined in array, mssages are contained in an AVL tree in. 
all structures are managed with a class that contained two AVLs and a contact list.
operator overloading was used in all classes to make the implientaion eaiser

*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include "tree.h"




//this is s class that conatins contact information.
class person
{
  public:
    person();
    person(char * newname,  char * address, char *newprefered);//constrictor with charactor args
    person(person * newperson);//copy construtor
    ~person();
    int display();//out puts the person contact info
    int copyperson(person * newperson);//deep copys in the data members 
    int copyin(char * newname, char * newaderess, char * newprefered);//poulates that data members
    friend bool operator== (person &, char *);//operator overload see if the names are the same, only checks the first 3 charictors so the user can search easier
    int getcontact(char *&, char *&);//cops the contact info to charitors to send messages.
   protected:
    char * name;//name of the person
    char * address;//address or phone number
    char * prefered;//what type of contact the person uses
};



//this contact is a address book for the user it conatins an array of persons
class contactlist
{
   public:
     contactlist();
     contactlist(contactlist*  newlist);//copy constructor
     ~contactlist();
     int addcontact(person * contact); //deep copies to the next open space on the person array
     int readincontacts(char * filename);//reads in all the persons from external file
     int findcontact(char *& name, char *&address);//finds a charactor on the array with the same name and copies the full name and address
     friend ostream& operator<< (ostream&, const contactlist &);//outputs the entire contact list
    private:

   protected:
      person * contacts;//array of persons
      int max; // size of the array, read in from file
      int index;  //next available open spot on the array
};


//This is the overall class that the UI will use to impliment functions
class messagecenter
{ 
    public:
    messagecenter();
    messagecenter(char * conatctsfile, char * messagesfile);//first arg will read in the contacts, second will read in the messages
    int getmessages(char * filename);//gets all the messages
    int sendmessage();//creats a new message and sends it to the outbox tree
    friend ostream& operator<< (ostream&, const messagecenter &);//out puts the contact list, inbox and outbox
    
    private:
    BST inbox;//AVL  of incoming messages ordered by name
    BST outbox;//AVL of outgoing  messages ordered byname
    contactlist friends;//list  of all friends
};
