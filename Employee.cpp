#include "Employee.h"
//class for employees infos and changing them

Employee::Employee(string employee_name, string employee_job)
{
//goes through sqlite3 as a pointer for avoiding errors
	this->employee_name = employee_name ;
	this->employee_job = employee_job ;

}


bool Employee::add_emplpoyee()//adds employee in db
{
        sqlite3 *db;



        int controller = sqlite3_open("AirportManager.db" , &db);//opens db
        if(controller)
        {
            cout << "Unable to open database" << endl;//error handler

            return false;
        }
        ///////////////sqlite3 codes
        else
        {
            string sql_command = "CREATE TABLE IF NOT EXISTS EMPLOYEES("
            "ID   INT,"
            "NAME   TEXT,"
            "JOB  TEXT);";//table for employees

            char* ErrorMassage;
            controller = sqlite3_exec(db , sql_command.c_str() ,  NULL, 0 , &ErrorMassage);//error handler

            if(controller != SQLITE_OK)
            {
                 cout << "Unable to create data :" << ErrorMassage << endl;

                 sqlite3_free(ErrorMassage);
                 return false;
            }


            if(is_already(db ,controller , employee_name , "EMPLOYEES" , "NAME"))//if there is such an employee to book shows error
            {
                cout << "There is already an Employee with the same name!" << endl;

                return false;
            }



            int id_number = get_ID_number(db,controller , "EMPLOYEES" , "ID") + 1;//400674100;//creats id num for every employee this is needed later for deleting employee

            employee_id = to_string(id_number);

            string mydata[] ={"'" + employee_id + "'",
                            "'" + employee_name + "'",
                            "'" + employee_job + "'"};


            sql_command = "INSERT INTO EMPLOYEES (ID , NAME , JOB) VALUES ("+mydata[0]+","+mydata[1]+","+mydata[2]+");";//books a new employee in db




            controller = sqlite3_exec(db , sql_command.c_str() ,  NULL, 0 , &ErrorMassage);//error handler

            if(controller != SQLITE_OK)//error in sqlite3 handler
            {
                 cout << "Unable to insert data : " << ErrorMassage << endl;
                 sqlite3_free(ErrorMassage);
                 return false;
            }

            cout << "Employee ID :" << employee_id << endl;

            sqlite3_close(db);
            return true;
        }
        return false;



}

bool Employee::remove_employee(string employee_id)
{
    sqlite3 *db;
    Manager manager;
    bool info_is_right = false;

    int controller = 0;
    controller = sqlite3_open("AirportManager.db" , &db);//opens sqlite3
    if(controller)
    {
        cout << "Unable to open database " << endl;
        return false;
    }
    else
    {
        if(!manager.is_already(db , controller , employee_name , "EMPLOYEES" , "NAME"))//if there is already a employee with this name
        {
            cout << "There is no Employee called "<< employee_name <<" in DataBase";
            return false;
        }

        string sql_command = "SELECT ID FROM EMPLOYEES";
        char* ErrorMassage;
        vector<string> container;
        controller = sqlite3_exec(db , sql_command.c_str() , manager.get_callback_data , &container , &ErrorMassage);//gets id to delete employee from db

        if(controller != SQLITE_OK)
        {
            cout << "Unable to Select ID : "<< ErrorMassage << endl;
            sqlite3_free(ErrorMassage);
            return false;
        }

        for(int i = 0;i < container.size();i++)//looks through col for id
        {
            if(container[i] == employee_id)
                info_is_right = true;
        }

        if(!info_is_right)
        {
            cout <<"The information is not right" << endl;
            return false;
        }

        sql_command = "DELETE FROM EMPLOYEES WHERE ID = "+employee_id;//removes employee

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


