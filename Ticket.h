
#ifndef TICKET_H
#define TICKET_H

#include "Passenger.h"
#include "Flight.h"


class Ticket:protected Passenger , protected Flight
{
public:
    Ticket(){};
    //Ticket(string name , string nationality , string gender ,string flight_date, string flight_time , string flight_origin , string flight_destination ):
    //Passenger(name , nationality , gender),Flight(flight_date , flight_time , flight_origin , flight_destination){};

    bool get_flight_info(string);
    bool get_passenger_info(string);
    bool add_ticket();
    bool remove_ticket(string , string);
    void availabe_flights();
};


#endif // TICKET_H

