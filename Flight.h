#ifndef FLIGHT_H
#define FLIGHT_H

#include "manager.h"

////////////////////////////////////////////////////////////////////////
//this class shows details about the flightboard
class Flight : public Manager//gets data from db in manager class
{
public:
    Flight(){};
    Flight(string ,string, string , string);
    bool add_flight();
    bool remove_flight(string);

protected:
    string flight_number;
    string flight_date;
    string flight_time;
    string flight_origin;
    string flight_destination;
};



#endif // FLIGHT_H
