#include <iostream>
#include "Employee.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"
/////////////////////////////////
using namespace std;

int main()
{

     string name,pass;
     string enter;
     int option;
     int  inner_option;
     Manager manager;

     cout << "Hello AND Welcome" << endl;
     cout << "Please log in to continue" << endl;
     cout << "Please Enter Name :";cin >> name;
     cout << "Please Enter password :";cin >> pass;

     if(manager.log_in(name , pass))//checks if the pass and name are alright
     {
         system("cls");//to clear the screen after a cout statement
         cout << "Welcome..." << endl;
         while(true)//after confirmation
         {
             cout << "\nchoose of the following options :" << endl;
             cout << endl;
             cout << "1.Employee panel" << endl;
             cout << "2.Passengers panel" << endl;
             cout << "3.Flights panel" << endl;
             cout << "4.Tickets list" << endl;
             cout << "5.exit" << endl;
             cin >> option;

////////////////////////////////////////////////////////////////////////
//next panel
             if(option == 1)//enters the employees class
             {
                    while(true)
                    {

                             system("cls");
                             cout << "1.show Employees info" << endl;
                             cout << "2.Add a new Employee" << endl;
                             cout << "3.remove an Employee" << endl;
                             cout << "4.back" << endl;
                             cin >>  inner_option;

                             if( inner_option == 1)
                             {
                                 manager.show_data("Employees");//goes through database
                                 cout << "\n\nEnter sth to go to main menu" << endl;
                                 cin >> enter;
                                 system("cls");

                             }
                             else if( inner_option == 2)
                             {
                                 string name,job;

                                 cout << "Please Enter Employee's name : ";cin >> name;
                                 cout << "Please Enter Employee's job :";cin >> job;

                                 Employee em(name , job);//books a new employee in db
                                 if(em.add_emplpoyee())
                                 {
                                    cout << "Employee successfully added" << endl;
                                    cout << "Please Enter sth to continue..." << endl;
                                    cin >> enter;
                                    system("cls");
                                 }
                                 else
                                 {
                                    cout << "::Unable to add Employee , sth went wrong\n" << endl;
                                    cout << "Please Enter sth to continue..." << endl;
                                    cin >> enter;
                                    system("cls");

                                 }


                             }
                             else if( inner_option == 3)
                             {
                                 string name,job,id;

                                 cout << "Employees' starting ID : 400674100 \n\n" << endl;
                                 cout << "Please Enter Employee's name : ";cin >> name;
                                 cout << "Please Enter Employee's job :";cin >> job;
                                 cout << "Please Enter Employee's id :";cin >> id;
                                 Employee em(name , job);//removes an employee
                                 if(em.remove_employee(id))//gets an id num to delete employee
                                 {
                                    cout << "Employee successfully removed" << endl;
                                    cout << "Enter sth to continue..." << endl;
                                    cin >> enter;
                                    system("cls");
                                 }

                                 else
                                 {
                                    cout << "::Unable to remove Employee , sth goes wrong" << endl;
                                    cout << "Enter sth to continue..." << endl;
                                    cin >> enter;
                                    system("cls");

                                 }


                             }
                             else if(inner_option == 4)//exits from current panel
                             {
                                 system("cls");
                                 break;
                            }

                    }

             }
/////////////////////////////////////////////////////////////////////////
             else if(option == 2)//passenger class
             {
                   while(true)
                   {

                             system("cls");
                             cout << "1.show Passengers info" << endl;
                             cout << "2.Add a new Passenger" << endl;
                             cout << "3.remove a Passenger" << endl;
                             cout << "4.back" << endl;
                             cin >>  inner_option;


                             if( inner_option == 1)
                                {

                                    manager.show_data("PASSENGERS");//reveals all the infos about passengers in db
                                    cout << "\n\nEnter sth to go to main menu" << endl;
                                    cin >> enter;
                                    system("cls");


                                }
                             else if( inner_option == 2)//adds a new passenger in db
                                {
                                    string full_name , nationality , gender;

                                    cout << "Full Name : ";cin >> full_name;
                                    cout << "Nationality :";cin >> nationality;
                                    cout << "Gender : ";cin >>gender;

                                    Passenger passenger(full_name , nationality , gender);//constructor func
                                    if(passenger.add_passenger())
                                    {
                                        cout << "Passenger successfully added" << endl;
                                        cout << "Please Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");
                                    }
                                    else
                                    {
                                        cout << "::Unable to add Passenger , sth went wrong\n" << endl;
                                        cout << "Please Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");
                                    }
                                }
                             else if ( inner_option == 3)
                                {
                                    string full_name , nationality , gender , id;

                                    cout << "Passengers' starting ID : 110600 \n\n" << endl;
                                    cout << "Full Name : ";cin >> full_name;
                                    cout << "Nationality :";cin >> nationality;
                                    cout << "Gender : ";cin >>gender;
                                    cout << "ID :";cin >> id;

                                    Passenger passenger(full_name , nationality , gender);//constructor
                                    if(passenger.remove_passenger(id))
                                    {
                                        cout << "Passenger successfully removed" << endl;
                                        cout << "Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");


                                    }

                                    else
                                    {
                                        cout << "::Unable to remove Passenger , sth goes wrong\n"<< endl;
                                        cout << "Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");


                                    }

                                }
                            else if( inner_option == 4)
                            {
                                system("cls");
                                break;

                            }
                   }

          }
////////////////////////////////////////////////////////////////////////////////
//flight class
        else if(option == 3)
          {
               while(true)
               {

                             system("cls");
                             cout << "1.show Flights info" << endl;
                             cout << "2.Add a new Flight" << endl;
                             cout << "3.cancel a Flight" << endl;
                             cout << "4.back" << endl;
                             cin >>  inner_option;

                             if( inner_option == 1)
                             {
                                    manager.show_data("Flights");
                                    cout << "\n\nEnter sth to go to main menu" << endl;
                                    cin >> enter;
                                    system("cls");

                             }
                             else if( inner_option == 2 )
                             {
                                 string date , time ,origin , destination;

                                    cout << "Date : ";cin >> date;
                                    cout << "Time :";cin >> time;
                                    cout << "Origin :";cin >> origin;
                                    cout << "Destination : ";cin >>destination;

                                    Flight flight(date, time , origin , destination);//constructor
                                    if(flight.add_flight())
                                    {
                                        cout << "Flight successfully added" << endl;
                                        cout << "Please Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");

                                    }
                                    else
                                    {
                                        cout << "::Unable to add Flight , sth goes wrong\n" << endl;
                                        cin >> enter;
                                        system("cls");

                                    }
                             }
                             else if( inner_option == 3)//cancels a flight
                             {
                                 string flight_number;
                                 Flight flight;
                                 cout << "Flights' starting FlightNumber : 1010 \n\n" << endl;

                                 cout << "Please Enter Flight number : ";cin >> flight_number;
                                 if(flight.remove_flight(flight_number))//gets a flight num to delete the whole data about it
                                 {
                                     cout << "flight successfully cancelled" << endl;
                                     cout << "Please Enter sth to continue..." << endl;
                                     cin >> enter;
                                     system("cls");
                                 }

                                 else//shows error if there is not such a num
                                 {
                                     cout << "::Unable to cancel flight , sth goes wrong\n" << endl;
                                     cout << "\n\nEnter sth to continue" << endl;
                                     cin >> enter;
                                     system("cls");

                                 }

                             }
                             else if( inner_option == 4)//exits from flight panel
                             {
                                 system("cls");
                                 break;
                             }
                  }

          }
          ///////////////////////////////////////////ticket class
          else if(option == 4)
          {
                 while(true)
                 {

                                 system("cls");
                                 cout << "1.show TICKETS list" << endl;
                                 cout << "2.Add a new TICKET" << endl;
                                 cout << "3.cancel a TICKET" << endl;
                                 cout << "4.back" << endl;
                                 cin >>  inner_option;

                                 if( inner_option == 1)
                                 {
                                        manager.show_data("TICKETS");//shows the col that named TICKETS in db
                                        cout << "\n\nEnter sth to go to main menu" << endl;
                                        cin >> enter;
                                        system("cls");
                                 }
                                 else if(inner_option == 2)//gets the needed data to book a new ticket
                                 {
                                        string passenger_id , flight_number;
                                        Ticket tk;
                                        tk.availabe_flights();
                                        cout << "\n\nPlease Enter Flight number : ";cin >> flight_number;

                                        cout << "Passengers' starting ID : 110600 \n\n" << endl;
                                        cout << "\n\nPlease Enter Passenger Id : ";cin >> passenger_id;

                                        if(tk.get_flight_info(flight_number))//if there is a flight num continues
                                        {
                                            if(tk.get_passenger_info(passenger_id))//books the infos about the ticket in db
                                            {
                                               if(tk.add_ticket())
                                               {
                                                   cout << "Ticket successfully added" << endl;
                                               }

                                            }
                                        }
                                        cout << "please Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");



                                 }
                             else if(inner_option == 3)//removes a certain ticket
                             {
                                        string passenger_id , flight_number;
                                        Ticket tk;

                                        cout << "Please Enter Flight number : ";cin >> flight_number;
                                        cout << "Please Enter Passenger Id : ";cin >> passenger_id;

                                        if(tk.remove_ticket(passenger_id , flight_number))//looks through db for this info
                                        {
                                            cout << "Ticket successfully cancelled " << endl;
                                            cout << "Please Enter sth to continue..." << endl;
                                            cin >> enter;
                                            system("cls");
                                        }
                                        else
                                        {
                                        cout << "Please Enter sth to continue..." << endl;
                                        cin >> enter;
                                        system("cls");
                                        }

                             }
                            else if(inner_option == 4)//exits from this panel
                            {
                                system("cls");
                                break;
                            }
                  }
          }
////////////////////////////////////////////////
          else if(option == 5)//goes out from program
          {
              cout << "GoodBye " << endl;
              break;
          }
          else
            system("cls");
        }

    }
    else//wrong admin infos
    {
        cout << "Unable to log in , WRONG INFO " << endl;
    }





}
