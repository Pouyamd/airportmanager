#include "Flight.h"

/////////////////////////////////////////////////////////////
Flight::Flight(string flight_date, string flight_time , string flight_origin , string flight_destination )
{
    this->flight_date = flight_date;//gets the data from constructor as a pointer because of sqlite3 issues to run
    this->flight_time = flight_time;
    this->flight_origin = flight_origin;
    this->flight_destination = flight_destination;
}

////////////////////////////////////////////////////////////////////////////////
bool Flight::add_flight()
{
    sqlite3 *db;
        Manager manager;//works with constructor in manager

        int controller = 0;
        controller = sqlite3_open("AirportManager.db" , &db);//opens sqlite3
        if(controller)
        {
            cout << "Unable to open database" << endl;

            return false;
        }
        else
        {
            string sql_command = "CREATE TABLE IF NOT EXISTS FLIGHTS ("//table for flight board in sqlite3
            "FLIGHTNUMBER   INT,"
            "DATE   TEXT,"
            "TIME   TEXT,"
            "ORIGIN   TEXT,"
            "DESTINATION   TEXT);";

            char* ErrorMassage;
            controller = sqlite3_exec(db , sql_command.c_str() ,  NULL, 0 , &ErrorMassage);//error handler

            if(controller != SQLITE_OK)//handles if cannot book the data
            {
                 cout << "Unable to create data :" << ErrorMassage << endl;

                 sqlite3_free(ErrorMassage);
                 return false;
            }



            int id_number = manager.get_ID_number(db,controller , "FLIGHTS" , "FLIGHTNUMBER") + 1;//1010;//creats an id for every flight in db this is needed to delete flight infos later
            flight_number = std::to_string(id_number);
            string mydata[] ={"'" + flight_number + "'",
                            "'" + flight_date + "'",
                            "'" + flight_time + "'",
                            "'" + flight_origin + "'",
                            "'" + flight_destination + "'"};


            sql_command = "INSERT INTO FLIGHTS (FLIGHTNUMBER , DATE , TIME , ORIGIN , DESTINATION) VALUES ("+mydata[0]+","+mydata[1]+","+mydata[2]+","+mydata[3]+","+mydata[4]+");";//inserts a new flight info in db




            controller = sqlite3_exec(db , sql_command.c_str() ,  NULL, 0 , &ErrorMassage);//error handler

            if(controller != SQLITE_OK)
            {
                 cout << "Unable to insert data into dataBase :" << ErrorMassage<< endl;
                 sqlite3_free(ErrorMassage);
                 return false;
            }

            cout << "Flight Number :" << flight_number << endl;

            sqlite3_close(db);
            return true;
        }
}

//////////////////////////////////////////////////////////////////////////////
bool Flight::remove_flight(string flight_number)//gets the previous id that booked in db and deletes the row
{
    sqlite3 *db;
    Manager manager;
    bool info_is_right = false;

    int controller = 0;
    controller = sqlite3_open("AirportManager.db" , &db);//opens db
    if(controller)
    {
        cout << "Unable to open database " << endl;
        return false;
    }
    else
    {

        string sql_command = "SELECT FLIGHTNUMBER FROM FLIGHTS";//order to delete row
        char* ErrorMassage;
        vector<string> container;
        controller = sqlite3_exec(db , sql_command.c_str() , manager.get_callback_data , &container , &ErrorMassage);

        if(controller != SQLITE_OK)//error handler
        {
            cout << "Unable to Select FLIGHTNUMBER : " << ErrorMassage << endl;
            sqlite3_free(ErrorMassage);
            return false;
        }

        for(unsigned int i = 0;i < container.size();i++)//looks through col to delete that row with id
        {
            if(container[i] == flight_number)
                info_is_right = true;
        }

        if(!info_is_right)
        {
            cout << "The information is not right" << endl;
            return false;
        }

        sql_command = "DELETE FROM FLIGHTS WHERE FLIGHTNUMBER = "+flight_number;

        controller = sqlite3_exec(db , sql_command.c_str() , NULL , 0 , &ErrorMassage);//error handler
        if(controller != SQLITE_OK)
        {
            cout << "Unable to Delete data : " << ErrorMassage << endl;
            return false;
        }

        sqlite3_close(db);//closes db

    }

   return true;
}
