#ifndef MANAGER_H
#define MANAGER_H





#include <stdio.h>
#include "sqlite3.h"
#include <iostream>
#include <vector>
/////////////////////////////////////////////////////////////
using namespace std;

class Manager//works with db and conforming the admin
{
public:
    int get_ID_number(sqlite3* ,int, string , string);//looks for id num in db

    bool is_already(sqlite3* ,int  , string, string , string);//looks if there is such info in db

    void show_data(string);//prints the data in db with a specific id


    bool log_in(string , string );//admin confirmation

/////////////////////////////////////////////////////////////////////////////////

static int get_callback_data(void *p, int size, char **column_text, char **column_name)//looks through a col and row for the given string list
{
    if (size == 0) return -1;
    vector<string> &container = *static_cast<vector<string>*>(p);//type

    if (!column_text[0]) container.push_back("NULL");//puts null in empty db row
    else container.push_back(column_text[0]);//bppks the given data in row
    return 0;

}
///////////////////////////////////////////////////////////////////////////////////////////
static int get_callback_data_multiple(void *p, int size, char **column_text, char **column_name)
{
    if (size == 0) return -1;
    vector<string> &container1 = *static_cast<vector<string>*>(p);


//books null in all col and rows in db
    if (!column_text[0]) container1.push_back("NULL");
    else container1.push_back(column_text[0]);

    if (!column_text[1]) container1.push_back("NULL");
    else container1.push_back(column_text[1]);

    if (!column_text[2]) container1.push_back("NULL");
    else container1.push_back(column_text[2]);

    if (!column_text[3]) container1.push_back("NULL");
    else container1.push_back(column_text[3]);


    return 0;

}




static int read_callback_data(void *p, int size, char **column_text, char **column_name)//couts  data from db
{

      for( int i = 0; i<size; i++)
      {
         cout << column_name[i] << " = " << (column_text[i] ? column_text[i] : "NULL") << endl;
      }
      cout << "\n\n" << endl;
   return 0;
}

};

#endif // MANAGER_H


