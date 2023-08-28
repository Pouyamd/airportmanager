#ifndef Airport_Employes_H
#define Airport_Employes_H

#include <iostream>
#include "manager.h"
#include <stdio.h>


using namespace std;


class Employee : public Manager
{
	public:
		Employee(string , string);
        //string get_employee_name(){return employee_name;}
        //string get_employee_job(){return employee_job;}
        //string get_employee_id(){return employee_id;}
		bool add_emplpoyee();
		bool remove_employee(string);



	private:
		string employee_name;
		string employee_id;
		string employee_job;

};

#endif
