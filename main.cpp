//////////////////////////////////////////////////
//////////                               /////////
//////////       MARC WEEK C++ SAMPLE    /////////
//////////                               /////////
//////////                               ///////// 
//////////////////////////////////////////////////

/* 

This program manages"simulates" messages from a varitey of different type of communication channels. Phone, email and facebook

It contains a class of persons contact ifnro which is conatined in array, mssages are contained in an AVL tree in. 
all structures are managed with a class that contained two AVLs and a contact list.
operator overloading was used in all classes to make the implientaion eaiser

this is the main section where the UI is implemeted

*/


#include "message.h"

using namespace std;


//will output all the contacts, inbox and out box then ask the user to send in a messege until they say no.
main()

{
     char again;
     messagecenter mymessages(const_cast<char*>("contacts.txt"), const_cast<char*>("messages.txt")); 
     do
     {
       cout << mymessages;
       mymessages.sendmessage();
       cout << "Send another message?>";
       cin >>again; cin.ignore(100, '\n');
       again = toupper(again);
     }while(again == 'Y');
   return 1;
}
