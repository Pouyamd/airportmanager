#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "manager.h"
#include <iostream>



//this class shows details about every passenger that had been in the airport
class Passenger :public Manager
{
public:
    Passenger(){};
    Passenger(string, string ,string );
    passenger(string);
    bool add_passenger();//books a new passenger in the db without main class help
    bool remove_passenger(string);
    bool remove_manager(string);



protected:
    //passenger details
    string full_name;
    string nationality;
    string passenger_id;
    string gender;




};
#endif
