#include "Passenger.h"


Passenger::Passenger(string full_name,string nationality,string gender)
{
    //using pointers to avoid errors and getting every passengers details
    this->full_name = full_name;
    this->nationality= nationality;
    this->gender= gender;

};

bool Passenger::add_passenger()//adds a new passenger to db directly
{
     sqlite3 * db;
     Manager manager;

     int controller=sqlite3_open("AirportManager.db", &db);//naming the data base and the refrences

     if(controller)
     {
         cout << "Unable to open dataBase" << endl;
         return false;
     }

      //SQL CODES
      string sql_command = "CREATE TABLE IF NOT EXISTS PASSENGERS("
      "ID INT,"
      "NAME   TEXT,"
      "NATIONALITY  TEXT,"
      "GENDER       TEXT);";


      //error handling
    char *ErrorMassage;

    //executes sql commands
    controller=sqlite3_exec(db ,sql_command.c_str() , NULL , 0 , &ErrorMassage);

    if(controller != SQLITE_OK)
    {
            cout << "Unable to create data :" << ErrorMassage << endl;

            sqlite3_free(ErrorMassage);
            return false;
    }
    else
    {

        if(manager.is_already(db ,controller , full_name , "PASSENGERS" , "NAME"))//shows error and reveals same passenger with that id
            {
                cout << "There is already a Passenger with the same name!" << endl;

                return false;
            }



            int id_number = manager.get_ID_number(db,controller , "PASSENGERS" , "ID") + 1;//110600;//builds a passenger id in db this id is needed for deleting the passenger later

            passenger_id = std::to_string(id_number);//books the id
//db table for passenger
            string mydata[] ={"'" + passenger_id + "'",
                            "'" + full_name + "'",
                            "'" + nationality + "'",
                            "'" + gender + "'"};


            sql_command = "INSERT INTO PASSENGERS (ID , NAME , NATIONALITY ,GENDER ) VALUES ("+mydata[0]+","+mydata[1]+","+mydata[2]+","+mydata[3]+");";//books a new passenger in db table




            controller = sqlite3_exec(db , sql_command.c_str() ,  NULL, 0 , &ErrorMassage);//db code to book

            if(controller != SQLITE_OK)//error handler
            {
                 cout << "Unable to insert data : " << ErrorMassage << endl;
                 sqlite3_free(ErrorMassage);
                 return false;
            }

            cout << "Passenger ID : " << passenger_id << endl;


            sqlite3_close(db);
            return true;
        }
    return false;

}
bool passenger::remove

bool Passenger::remove_passenger(string passenger_id)
{
    sqlite3 *db;
    Manager manager;
    bool info_is_right = false;

    int controller = 0;
    controller = sqlite3_open("AirportManager.db" , &db);//if has a problem with opening db shows error
    if(controller)
    {
        printf("Unable to open database ");
        return false;
    }
    else
    {
        if(!manager.is_already(db , controller , full_name , "PASSENGERS" , "NAME"))//checks passengers existence
        {
            cout << "There is no PASSENGER called "<< full_name <<" in DataBase";
            return false;
        }

        string sql_command = "SELECT ID FROM PASSENGERS";//gets id for deleting passenger in db
        char* ErrorMassage;
        vector<string> container;
        controller = sqlite3_exec(db , sql_command.c_str() , manager.get_callback_data , &container , &ErrorMassage);//id

        if(controller != SQLITE_OK)//error in finding id
        {
            cout << "Unable to Select ID : "  << ErrorMassage << endl;
            sqlite3_free(ErrorMassage);
            return false;
        }

        for(int i = 0;i < container.size();i++)//looks through passengers infos for that id
        {
            if(container[i] == passenger_id)
                info_is_right = true;
        }

        if(!info_is_right)
        {
            printf("The information is not right");
            return false;
        }

        sql_command = "DELETE FROM PASSENGERS WHERE ID = "+passenger_id;
        //deletes the passenger row
        passenger::passenger( passenger_id){

        }


        controller = sqlite3_exec(db , sql_command.c_str() , NULL , 0 , &ErrorMassage);
        if(controller != SQLITE_OK)//error handler
        {
            cout << "Unable to Delete data : " << ErrorMassage << endl;
            return false;
        }

        sqlite3_close(db);

    }

   return true;
}

