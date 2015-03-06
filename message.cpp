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

These are the implimentations of the message center classes


*/



#include "message.h"

using namespace std;

//default constructor for the person
person::person() : name(NULL), address(NULL), prefered(NULL)
{}

//constructor or person class with Char argrumenst
person::person(char * newname, char * newaddress, char * newprefered)
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
   if (newprefered)
  {
    prefered = new char[strlen(newprefered)+1];
    strcpy(prefered, newprefered);
  }
 

  
}

//person class copy construtor
person::person(person * newperson)
{
  if (newperson->name)
  {
    name = new char[strlen(newperson->name)+1];
    strcpy(name, newperson->name);
  }
  if (newperson->address)
  {
    address = new char[strlen(newperson->address)+1];
    strcpy(address, newperson->address);
  }
  if (newperson->prefered)
  {
    prefered = new char[strlen(newperson->prefered)+1];
    strcpy(prefered, newperson->prefered);
  }
 
 

}
//deconstructor for person class
person::~person()
{
 if (name) delete [] name;
 if (address) delete [] address;
 if (prefered) delete [] prefered;
}

//outputs the personclass data members
int person::display()
{  
   if (name && address && prefered)
   {
       cout << "Name: ";
       cout.width(15);
       cout << left << name;
       cout << "Prefered address: ";
       cout.width(15);
       cout << left  << prefered;
       cout << "Address: ";
       cout.width(15);
       cout << left << address;

    }
}
//copys over the person to a uninitlzed data memeber
int person::copyperson(person * newperson)
{
  if (newperson)
  {
    if (name) delete[]  name;
    if (newperson->name)
    {
      name = new char[strlen(newperson->name)+1];
      strcpy(name, newperson->name);
    }
    if (newperson->address)
    {
      address = new char[strlen(newperson->address)+1];
      strcpy(address, newperson->address);
    }

    if (prefered) delete[] prefered;
    if (newperson->prefered)
    {
      prefered = new char[strlen(newperson->prefered)+1];
      strcpy(prefered, newperson->prefered);
    }
   }

}
//copies in from charictor arguments
int person::copyin(char * newname, char * newaddress, char * newprefered)
{
    if (name) delete [] name;
    if (newname)
    {
      name = new char[strlen(newname)+1];
      strcpy(name, newname);
    }
    if (address) delete[] address;
    if (newaddress)
    {
      address = new char[strlen(newaddress)+1];
      strcpy(address, newaddress);
    }

    if (prefered) delete prefered;
    if (newprefered)
    {
      prefered = new char[strlen(newprefered)+1];
      strcpy(prefered, newprefered);
    }
   

}


//operator overloaded equalty check based on name.
bool operator== (person & search, char * name)
{
  if(!strncmp(search.name, name, 3)) return true;//NOTE I Limited to 3 charitors so the user could type in a first name or mispell and still get all the data from the contact list
  return false;
}

int person::getcontact(char *& toname, char *& addressee)//gives the name and address to the arguments
{
   strcpy(toname, name);
   strcpy(addressee, address);
}


//default constuctor for the contact list
contactlist::contactlist():  index(0)
{}

//contact list copy constutor
contactlist::contactlist(contactlist * newlist)
{
  if (newlist)
  {
  max = newlist->max;
  index = newlist->index;
  contacts = new person[max];
  for (int i = 0; i < index; ++i)
     contacts[i].copyperson(&newlist->contacts[i]);
  }
}

//deconstructor for contact list
contactlist::~contactlist()
{
  if (contacts) delete [] contacts;
}

//adds a person and set the index to the next open space
int contactlist::addcontact(person * contact)
{
  if (index != max)
  {
     contacts[index].copyperson(contact);
     ++index;
  }
}
//reads in the contacts from a file
int contactlist::readincontacts(char * filename)
{
   ifstream filein; 
   if (!filein) return 0;
   filein.open(filename);
   int rmax = 0;
   int i = 1;
   char name[20]; 
   char address[20];
   char  prefered[20];
   person * temp;
   filein >> rmax ; filein.ignore (100, '\n');//the size of the array is the first line of the file
   max = rmax;

   contacts = new person[max];
   while (!filein.eof() && i < max)
    {
     filein.get(name, 20, ';'); filein.ignore(100, ';');
     filein.get(address, 20, ';'); filein.ignore(100, ';');
     filein.get(prefered, 20, '\n');  filein.ignore(100, '\n');
     temp = new person(name, address, prefered);
     addcontact(temp);
     delete temp;
     ++i;
     }
   filein.close(); 
   return 1;
}

//outputs the entire contact list
ostream& operator<<(ostream& out, const  contactlist & friends)
{
  for (int i = 0; i < friends.index; ++i)
  { 
    friends.contacts[i].display();
    cout <<endl;
  } 
}

//finds a conatct entered in by the uses and copys in the full name and address
int contactlist::findcontact(char *& name, char *& address)
{
  for (int i = 0; i < index; ++i)
  {
    if (contacts[i] == name)
    {  
      contacts[i].getcontact(name, address); 
      return 1;
    }
  }
  return 0;
}

//default consturctor for messagecenter
messagecenter::messagecenter(){}

//constcutor for the messagecnter with the names of  the externeal files 
messagecenter::messagecenter(char * contactsfile, char * messagefile)//"contact.txt", "messages.txt"
{
   friends.readincontacts(contactsfile);
   getmessages(messagefile);

}
//gets the messages from the file and sends them into the BST inbox
int messagecenter::getmessages(char * filename)
{
   ifstream filein; 
   if (!filein) return 0;
   filein.open(filename);;
   char name[20]; 
   char address[20];
   char  text[50];
   message temp;
   filein.get(name, 20, ';') ; filein.ignore (100, ';');
   while (!filein.eof())
    {
     filein.get(address, 20, ';'); filein.ignore(100, ';');
     filein.get(text, 50, '\n');  filein.ignore(100, '\n');
     temp = message(name, address, text);
     inbox += temp;
     filein.get(name, 20, ';'); filein.ignore(100, ';');
     }
   filein.close(); 
   return 1;
}

//operator overloaded output function displays the contacts list, inbox and outbox
ostream& operator<<(ostream& out, const messagecenter & mycenter)
{
   cout << "\nContacts:\n";
   cout <<  mycenter.friends;

  cout << "\nInbox:\n";
  cout << mycenter.inbox;
  cout << "\nOutbox:\n";
  cout <<  mycenter.outbox;
}


//creats a new message and sends it to the outbox
int messagecenter::sendmessage()
{
   char* name = new char [20];
   char* address = new char [20];
   char text[50];
   cout << "\nSelect name from contact list>";
   cin.get(name, 4, '\n'); cin.ignore(100, '\n');
   name[0] = toupper(name[0]);
   if(!friends.findcontact(name, address))//checks the first 3 charictors for a match and then sends in the address
   {
     cout << "Contact not in friends list\nEnter in address";//lets the user type it in if its not there
     cin.get(address, 20, '\n'); cin.ignore(100, '\n');
   }  
   cout << "\nTo: " << name<< '<' << address << ">\n";  
   cout << "\nEnter message>";
   cin.get(text, 50, '\n'); cin.ignore(100, '\n');
   message sent(name, address, text);
   outbox += sent;  
   cout << "\nMessage sent\n";
   delete [] name;  delete[] address;
}

