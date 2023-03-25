// Oria Patrick Attey - OPA180000
#include "Ticket.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "linkedList.h"
#include <fstream>
#include <sstream>

using  namespace std;

int main()
{
   // Dynamically allocate the docks array and linked list
	Dock* docks = new Dock[10];
	linkedList* queue = new linkedList;

	//opening input and output files
	fstream outfilestream;
	string fname_out = "Tickets.txt";

	//Create and open the output file
	outfilestream.open(fname_out, ios::out);

	fstream infilestream;
	string fname_in = "Knowhere.dat";
	// Open the input file
	infilestream.open(fname_in.c_str(), ios::in);

	string input; // variable to store the input from the file
	int Next_read = 0; // variable, that increment move to the next input in the file
	bool isEnter = true, isStart = true;
	int Dock_Number = 0;
	int Hours_Out = 0, minOut = 0, hour_In = 0, Minutes_In = 0, credits = 0;
	string Ship_ID;
	string Ship_Name;
	string Input_Time;
	int Docks_Total = 10;


   if (infilestream)
   {
      while (!infilestream.eof())
         {
			infilestream >> input; //begin to read inputs from the input file
			switch (Next_read)
			{
			   // the first case emphasize either the first input is Enter or not, " Exit"
				case 0:
				   {
					if (input.compare("enter") == 0)
                  {
                     isEnter = true; //It's true that's means the first input is enter
                  }
					else
					 {
						isEnter = false; // It's false that means the fist input is Exit
					}
					Next_read++; // moving forward to the next reading
					break;
				}
				// This case emphasize whether the next reading is " time in" or " ship ID"
				case 1:
				   {
               // if it's enter, record the time in (hour in and minute in)
					if (isEnter)
                  {
                     stringstream stream(input);             //**************************
                     getline(stream, Input_Time, ':');      //                         *
                     hour_In = stoi(Input_Time);           // Example of time in      *
                     getline(stream, Input_Time, ':');    //    14:15               *
                     Minutes_In = stoi(Input_Time);           //*************************
                  }
               // if exit, record  the Ship ID
					else
                  {
                     Ship_ID = input; //Example of Ship ID " GG-08-2018 "
                  }
					Next_read++;
					break;
				}
				// This case emphasize whether the next reading is " time in" or " ship ID"
				case 2:
				   {
            // if enter, record the Ship name
               if (isEnter)
                  {
                     Ship_Name = input; // Example of ship name " la_Concorde"
                     Next_read++; // moving to the next reading
                  }
            // if exit, record the time out ( hour out and minutes out )
					else
                  {
                     stringstream stream(input);            //**************************
                     getline(stream, Input_Time, ':');     //Example of Time out:     *
                     Hours_Out = stoi(Input_Time);         //   14:30                 *
                     getline(stream, Input_Time, ':');   //                         *
                     minOut = stoi(Input_Time);         //*************************
                     Next_read = 0; // Done reading from the exit part
                  }
					break;
				}
				// let's continue reading for for the " enter" part
				// This case record the next reading which is the ship ID
				case 3:
				   {
                  Ship_ID = input; //Example of ship ID " GG-08-2018"
                  Next_read++; // moving to the next reading
                  break;
               }
				case 4:
				    {
                  credits = stoi(input); //Example of paid Time " 20 "
                  Next_read = 0; // Done reading from the enter part
                  break;
               }
         }

         //This part especially evaluate the inputs recorded from the input file
			if (Next_read == 0)
            {
         // the first situation is where the ship is entering " Knowhere"
				if (isEnter)
				{
					Ship * emptyShip = nullptr;
					Ship* newShip = new Ship(Ship_Name, Ship_ID, emptyShip, credits);
					Dock_Number++;
					if (Dock_Number <= Docks_Total)
					{
						Dock* tempDock = new Dock(hour_In, Minutes_In, false, newShip);
						for (int i = 0; i < Docks_Total; i++) //situation in which we find empty first
						 {                                    // empty dock
							if (docks[i].getIsEmpty())
							 {
								docks[i] = *tempDock;
								tempDock = nullptr;
								delete tempDock;
								break;
							}
						}
					}
					// the second situation will be where the docks are full, and the ship has to go to the queue
					else
					{
						*queue += newShip;
					}

					newShip = nullptr;
					delete newShip;
				}
         // the second scenario is the one in which the ship is leaving " Knowhere "
				else
               {
					for (int i = 0; i < Dock_Number; i++)
					{
						if (docks[i].returnDock(Ship_ID)) //finding the dock in which the ship is docked
						 {
							Dock* tempDock = &docks[i];
							Ship* newShip = tempDock->returnShip();
							Ticket* tickets = new Ticket(newShip, tempDock, Hours_Out, minOut); // Generating ticket
							tickets->calculateFine(); //calculating fine

                  // Whenever there is a fine for ship, print the ticket for that Ship
							if (tickets->getFine() > 0)
                        {
                           if (!isStart)
                           {
                              outfilestream << '\n' << '\n';
                           }
                           outfilestream << *tickets;
                           isStart = false;
                        }

							Ship * Ship_Pointer;
							if (queue->getHead() != NULL) //if we have ships in queue , the first ship will be the one to be docked
                        {
                           Ship_Pointer = queue->getHead();
                           --*(queue); //removing the recently docked ship from the queue
                        }
							else
                        {
                           Ship_Pointer = nullptr;
                        }
							docks[i].updateDock(Ship_Pointer, Hours_Out, minOut);

							Dock_Number--;
							break;
						}
					}
				}
			}
		}
		//close both input and output files
		infilestream.close();
		outfilestream.close();

   }
   else
      cout<<" Input error ! "<< endl;
	return 0;
}
