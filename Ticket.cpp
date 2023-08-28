

#include "Ticket.h"


bool Ticket::get_passenger_info(string passenger_id)//works with get_id in manager class
{
    sqlite3* db;
    Manager manager;

    int controller = sqlite3_open("AirportManager.db", &db);//opens sqlite3
    if(controller)
    {
        cout << "Unable to open DataBase" << endl;
    }
    else
    {
        if(!manager.is_already(db , controller , passenger_id , "PASSENGERS" , "ID"))//already data error
        {
            cout << "NO Passenger whit this ID found" << endl;
            return false;
        }

        string sql_command = "SELECT NAME,NATIONALITY,GENDER FROM PASSENGERS where ID = "+passenger_id;//creats a id num for every ticket booked in db later we need this to delete ticket

        vector<string> container;

        char* ErroMassage;
        controller = sqlite3_exec(db , sql_command.c_str() , get_callback_data_multiple , &container , &ErroMassage);//error handler
        if(controller != SQLITE_OK)
        {
            cout << "Unable to Read Data : " << ErroMassage << endl;
            sqlite3_free(ErroMassage);
            return false;
        }



        this->passenger_id = passenger_id;
        this->full_name = container[0];
        this->nationality = container[1];
        this->gender = container[2];//books ticket details in table in db



        return true;

/////////////////////////////////////////////////////////////////////////////
    }
    return false;
}

bool Ticket::get_flight_info(string flight_number)//needs data from flight class infos
{
    sqlite3* db;
    Manager manager;


    int controller = sqlite3_open("AirportManager.db", &db);//opens sqlite3
    if(controller)
    {
        cout << "Unable to open DataBase" << endl;
    }
    else
    {

        if(!manager.is_already(db , controller , flight_number , "FLIGHTS" , "FLIGHTNUMBER"))//already data error
        {
            cout << "NO Flight whit this ID found" << endl;
            return false;
        }

        string sql_command = "SELECT DATE , TIME , ORIGIN , DESTINATION FROM FLIGHTS where FLIGHTNUMBER = "+flight_number;//puts the data in different parts of table

        vector<string> container;

        char* ErroMassage;
        controller = sqlite3_exec(db , sql_command.c_str() , get_callback_data_multiple , &container , &ErroMassage);//error handler
        if(controller != SQLITE_OK)
        {
            cout << "Unable to Read Data : " << ErroMassage << endl;
            sqlite3_free(ErroMassage);
            return false;
        }

        this->flight_number = flight_number;
        this->flight_date = container[0];
        this->flight_time = container[1];
        this->flight_origin = container[2];
        this->flight_destination = container[3];
        return true;
    }///////handles empty col
   return false;
}

bool Ticket::add_ticket()
{
    sqlite3* db;
    Manager manager;

    int controller = sqlite3_open("AirportManager.db" , &db);
    if(controller)
    {
        cout << "Unable to open DataBase" << endl;
        return false;
    }
    else
    {
        if(manager.is_already(db , controller , passenger_id , "TICKETS" , "PASSENGERID"))//already data error
        {
            cout << "This  Ticket has already been taken " << endl;
            return false;
        }
//db codes
        string sql_command = "CREATE TABLE IF NOT EXISTS TICKETS("
        "PASSENGERID   TEXT,"
        "FULLNAME    TEXT,"
        "NATIONALITY  TEXT,"
        "GENDER       TEXT,"
        "FLIGHTNUMBER  TEXT,"
        "FLIGHTDATE     TEXT,"
        "FLIGHTTIME     TEXT,"
        "FLIGHTORIGIN    TEXT,"
        "FLITGHTDESTINATION   TEXT);";


        char* ErrorMassage;
        controller = sqlite3_exec(db , sql_command.c_str() , NULL , 0 , &ErrorMassage);//handles error
        if(controller != SQLITE_OK)
        {
            cout << "Unable to Create table :" << ErrorMassage;
            sqlite3_free(ErrorMassage);
            return false;
        }



        string mydata[] ={"'"+passenger_id+"'",
                          "'"+full_name+"'",
                          "'"+nationality+"'",
                          "'"+gender+"'",
                          "'"+flight_number+"'",
                          "'"+flight_date+"'",
                          "'"+flight_time+"'",
                          "'"+flight_origin+"'",
                          "'"+flight_destination+"'"};
//////////////////////inserts data in sqlite3
        sql_command = "INSERT INTO TICKETS(PASSENGERID , FULLNAME , NATIONALITY , GENDER , FLIGHTNUMBER , FLIGHTDATE , FLIGHTTIME , FLIGHTORIGIN , FLITGHTDESTINATION)"\
        "VALUES ("+mydata[0]+","+mydata[1]+","+mydata[2]+","+mydata[3]+","+mydata[4]+","+mydata[5]+","+mydata[6]+","+mydata[7]+","+mydata[8]+");";

        controller = sqlite3_exec(db , sql_command.c_str() , NULL , 0 , &ErrorMassage);

        if(controller != SQLITE_OK)
        {
            cout << "Unable to insert data :" << ErrorMassage;
            sqlite3_free(ErrorMassage);
            return false;
        }
       return true;

    }
    return false;
}

bool Ticket::remove_ticket(string passenger_id , string flight_number)//ticket info remover
{
    sqlite3* db;
    int controller = sqlite3_open("AirportManager.db" , &db);
    if(controller)
    {
        cout << "Unable to open DataBase" << endl;
    }
    else
    {
        string sql_command = "SELECT PASSENGERID FROM TICKETS";

        vector<string> passenger_id_container;

        char* ErrorMassage;
        controller = sqlite3_exec(db , sql_command.c_str() , get_callback_data , &passenger_id_container, &ErrorMassage);//error handler

        if(controller != SQLITE_OK)
        {
            cout << "Unable to Find Ticket :" << ErrorMassage;
            sqlite3_free(ErrorMassage);
            return false;
        }



        vector<string> flight_number_container;
        sql_command = "SELECT FLIGHTNUMBER FROM TICKETS";
        controller = sqlite3_exec(db , sql_command.c_str() , get_callback_data , &flight_number_container, &ErrorMassage);


        if(controller != SQLITE_OK)
        {
            cout << "Unable to Find Ticket :" << ErrorMassage;
            sqlite3_free(ErrorMassage);
            return false;
        }

        for(unsigned int i=0;i < passenger_id_container.size();i++)//looks through db to delete ticket
        {
            if(passenger_id_container[i] == passenger_id)
                if(flight_number_container[i] == flight_number)
                {
                   sql_command = "DELETE FROM TICKETS WHERE PASSENGERID = "+passenger_id;

                   controller = sqlite3_exec(db , sql_command.c_str() , NULL , 0 , &ErrorMassage);//error hanler
                   if(controller != SQLITE_OK)
                   {
                       cout << "Unable to Delete Ticket : " << ErrorMassage;
                       return false;
                   }
                   return true;
                }

        }

        cout << "No Tickets found" << endl;
        return false;
    }
   return false;
}

void Ticket::availabe_flights()
{
    sqlite3* db;
    int controller = sqlite3_open("AirportManager.db" , &db);

    if(controller)
    {
        cout << "Unable to open dataBase" << endl;
    }
    else
    {
        string sql_command = "SELECT FLIGHTNUMBER FROM FLIGHTS";
        vector<string> container;
        char* ErrorMassage;

        controller = sqlite3_exec(db , sql_command.c_str() , get_callback_data , &container , &ErrorMassage);

        if(controller != SQLITE_OK)
        {
            cout << "Unable to Read Data From FLIGHTNUMBER , FLIGHTS : " << ErrorMassage << endl;
            sqlite3_free(ErrorMassage);

        }
        else
        {

            cout << "Available Flights : " << endl;
            for(unsigned int i = 0;i < container.size();i++)
            {
                cout << "  :::  " << container[i];
            }
            cout << endl;

        }


    }

}


