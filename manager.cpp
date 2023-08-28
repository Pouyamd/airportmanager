#include "manager.h"

int Manager::get_ID_number(sqlite3* database,int controller , string table_name , string column)
{
        vector<string> container;//given id to book through db

        string sql_command = "SELECT "+column+" FROM "+table_name;//looks through the given col and table


        char* ErrorMassage;//error handler in db
        controller = sqlite3_exec(database , sql_command.c_str() ,get_callback_data, &container,&ErrorMassage);

        string id_number_str = container[container.size() - 1];
        int id_number = stoi(id_number_str);


        return id_number;
}

bool Manager::is_already(sqlite3* database,int controller , string data , string table_name , string column_name)//shows the row that data is already exists there
{

            string sql_command = "SELECT "+column_name+" FROM "+table_name;

            vector<string> container;

            char* ErrorMassage;
            controller = sqlite3_exec(database , sql_command.c_str() , get_callback_data ,&container,&ErrorMassage);//error handler

            for(int i = 0;i < container.size();i++)
            {
                if(container[i] == data)
                    return true;
            }

            return false;
}

void Manager::show_data(string table_name)//prints data with given table
{
    sqlite3* db;
    int controller = sqlite3_open("AirportManager.db" , &db);//db name
    if(controller)
    {
        printf("Unable to open DataBase");
    }
    else
    {
        string sql_command = "SELECT * FROM "+table_name;//selects the table
        char* ErrorMassage;

        controller = sqlite3_exec(db, sql_command.c_str() , read_callback_data , 0 , &ErrorMassage );//error handler
        if(controller != SQLITE_OK)
        {
            cout << "Unable to show data : " << ErrorMassage;
            sqlite3_free(ErrorMassage);
        }
    }
}

bool Manager::log_in(string name , string pass)//admin login check
{
        sqlite3 *db;

        //Error handling
        int controller = sqlite3_open("AirportAdmin.db" , &db);

        if(controller)
        {
            cout << "Unable to open database " << endl;
            return false;
        }
        else
        {
            string sql = "SELECT NAME FROM AIRPORT";
            char* ErrorMassage;


            //READING DATA FROM NAME
            vector<string> name_container;

            controller = sqlite3_exec(db , sql.c_str(),get_callback_data, &name_container ,&ErrorMassage);

            if(controller != SQLITE_OK)
            {
                cout << "Unable to Read name from Airport : " << ErrorMassage;
                sqlite3_free(ErrorMassage);
                return false;
            }



            //READING DATA FROM MANAGEROASS
            sql = "SELECT ADMINPASS FROM AIRPORT";
            vector<string> pass_container;

            controller = sqlite3_exec(db , sql.c_str(),get_callback_data, &pass_container ,&ErrorMassage);


            sqlite3_close(db);

            if(name_container[0] == name && pass_container[0] == pass)
            {
                return true;
            }

            return false;
        }

}



