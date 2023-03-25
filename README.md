With the Guardians of the Galaxy making Knowhere their base of operations, that sector of space has
become rather popular. This popularity brings with it extra traffic and is putting a strain on the intergalactic
docking station. Ships are now required to pay for time at the docking station. Those ships that stay longer than
their time allotment will receive an automated ticket. You have been hired to write a program that will help
generate tickets for parking violations at Knowhere.
Functionality: This program will utilize a linked list as a queue. The ships will dock at the station if there is an
open dock; if not the ships will form a queue. Before docking, the ship will pay for time at the docking station.
When the ship undocks, the time will be checked to see if the ship stayed longer than the time purchased. If so, a
ticket will be generated. When a ship undocks, if there are ships in the queue, the first ship in the queue will dock
at the docking station.

Pseudocode: Your pseudocode should describe the following items
• Main.cpp
o List functions you plan to create
▪ Determine the parameters
▪ Determine the return type
▪ Detail the step-by-step logic that the function will perform
o Detail the step-by-step logic of the main function
• Overloaded += operator from linked list class
• Overloaded -- operator from linked list class
• Overloaded << operator from ticket class
• Calculate fine function from ticket class
Classes: The members and functions to be included in each class are listed below. Other functions may be added
to the class. Please remember that class functions should be generic enough to be used in any situation.
Functions that solve a specific problem for this project should be defined in main rather than the class.
• Linked List
o Head (Ship pointer)
o Default constructor
o Overloaded constructor – pass in node which becomes new head
o Overloaded += operator
▪ Adds node to end of list
o Overloaded -- operator
▪ Prefix notation
▪ Remove node from beginning of list

• Ship
o Name (string)
o Ship ID (string)
o Credit (in minutes) (integer)
o Ship pointer (to point to next ship in the queue)
o Default constructor
o Overloaded constructor
o Copy constructor
• Dock
o Hour In (integer)
o Minutes In (integer)
o Ship pointer (to point to docked ship)
o Default constructor
o Overloaded constructor
o Copy constructor
• Ticket
o Ship Info (Node pointer)
o Dock Info (Dock pointer)

o Hour Out (integer)
o Minutes Out (integer)
o Default constructor
o Overloaded constructor
o Copy constructor
o Overloaded << operator
▪ Display contents of the ticket object
o Calculate Fine
▪ Determine the fine assessed
o Make this class friends with the Dock and Ship classes

Details:
• This project will utilize multiple classes (see above).
• Each class must have a header file and a source file.
• There are 10 docks.
o The docks will be held in an array
• All input and output is file based
o The input file is a log of ships entering and exiting Knowhere
o Link the ship to the first open dock in the array
o If no open dock exists, put the ship in the queue
• The time listed in the file for a ship entrance is the initial time the ship arrived
o The entrance time does not reflect the time the ship docked
o If a ship is removed from the queue and docks, the start time for the meter will be 15 minutes
after the previous ship left the dock
o Example: a ship leaves the dock at 10:03, the ship from the queue will dock at 10:18
• When a ship leaves the dock, check to see if a ticket is generated.
o You must calculate how many minutes the ship was docked
o Compare that to the credits paid for
o If the ship was docked more minutes than credits, a ticket is generated for the excess time
o When a ticket is generated, you must calculate the fine. The fine is 200 units per extra minute for
the first hour and 500 per extra minute thereafter.
▪ Example: A ship left 75 minutes late. The fine would be 200 * 60 + 500 * 15 = 19500
credits

o If a ship has remaining credits when leaving the dock, those credits are lost
• You may assume that all ship actions occur within a 24 hour time span beginning at midnight and ending
at 11:59 PM
• All time will be given in military time
o Hours 0 -11 are AM
o Hours 12-23 are PM
• No input validation is required. You may assume that all input is valid.
Input: All input will come from a file named Knowhere.dat. The file will contain multiple lines of information
to describe what is happening at Knowhere. Each line will be one of the formats as described below. There will
be spaces between each item on the line. You may assume that the entries in the file are in chronological order.

There will be a newline character after each line except for the last line in the file which may or may not have a
newline character.
• Ship entering Knowhere
enter <time in> <ship name> <ship ID> <paid time>
Example
enter 14:15 Milano GG-08-2014 20
• Ship leaving Knowhere
exit <ship ID> <time out>
Example
exit GG-08-2014 14:30
Output: All output will be written to a file named Tickets.txt. This file will contain all of the tickets
generated by ships that stayed at the docking station longer than the amount of time paid. The ticket should be
of the following format:
Ship ID: <Ship ID>
Name: <Ship Name>
Time In: <Hour In>:<Minutes In>
Time Out: <Hour Out>:<Minutes Out>
Credited Minutes: <Credit>
Extra Minutes: <Minutes Over>
Fine: <fine> units
<blank line>
