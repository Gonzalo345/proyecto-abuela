//============================================================================
// Name        : Program.c
// Author      : Gonzalo, Yarvi
// Version     : 2.0
// Created on  : August 20, 2019
// Description : Create an agenda for my grandmother
// Compiler    : Eclipse IDE
//============================================================================

#include <sys/select.h>  							// To compile in Linux
#include <iostream>
#include "data.h"
#include "sistemTime.h"

using namespace std;

void Delay( long int secs );								// 3-second delay
void createNewTask(data &);
void taskInit(data &);
int kbhit( void );								// Controls if a key was pressed
unsigned int stringtoInt(string, unsigned int &, unsigned int &, bool &);
int stringtoInt(string );



int main (int argc, char** argv)
{
	timeControl Time;
	data Task;
	string strOption;
	int option = 0;
	unsigned int Hour, Min;
	unsigned int Speed;

	taskInit(Task);						// Initialization of tasks

	cout << "****************************************************" << endl;
	cout << "           AGENDA FOR MY GRANDMOTHER				 " << endl;
	cout << "****************************************************" << endl;
	cout << "Actual Time: " << Time.hour() << ":" << Time.min() << endl << endl;
 	cout << "To see the task of the moment press    			1" << endl;
	cout << "To input an hour press                 			2" << endl;
	cout << "To see the the actual Time             			3" << endl;
	cout << "To see the status of the task          			4" << endl;
	cout << "To input a speed factor press          			5" << endl;
	cout << "To see the menu press                  			6" << endl;
	cout << "To add a new task press                			7" << endl;
	cout << "To finish press                        			8" << endl << endl;
	while (option !=  8){

		while (!kbhit()) { 													// While no key is pressed
																			// Take the current time
			Task.actualTask(Time.currentMin());  							// Controls the automatic execution of tasks
			Delay( 1 );
		}
		cin >> strOption;
		option = stringtoInt(strOption);
		switch (option) {
			case 1: // Task of the moment
				cout << "\nActual Time: " << Time.hour() << ":" << Time.min() << endl;
				Task.taskStatus(Time.currentMin());
				cout << "To see the menu press 6:" << endl;
				break;

			case 2:	// Enter an hour, to show which task would be running
				cout << "Enter the hour first, then the minutes" << endl;
				cout << "Hours  : ";
				cin >> Hour;
				cout << "Minutes: ";
				cin >> Min;
				Task.taskStatus(Hour * 60 + Min);
				cout << "To see the menu press 6:" << endl;
				break;

			case 3:	// Displaying the current time in standard format
				cout << "Actual Time: " << Time.hour() << ":" << Time.min() << endl;
				cout << "To see the menu press 6:" << endl;
				break;

			case 4:	// Show the status of tasks
				Task.showTasks();
				Delay(3);
				cout << "To see the menu press 6:" << endl;
				break;

			case 5: // Increase the speed factor
				cout << "Actual Time: " << Time.hour() << ":" << Time.min() << endl;
				cout << "Enter the speed factor ( 1 to 200 ) :" << endl;
				cin >> Speed;
				if ( Speed < 1   ){ Speed = 1;}
				if ( Speed > 200 ){	Speed = 200;}
				cout << "Speed :" << Speed << endl;
				Time.speedFactor(Speed);
				cout << "To see the menu press 6:" << endl;
				break;

			case 6:	// Show the menu
			 	cout << "To see the task of the moment press    1" << endl;
				cout << "To input an hour press                 2" << endl;
				cout << "To see the the actual Time             3" << endl;
				cout << "To see the status of the task          4" << endl;
				cout << "To input a speed factor press          5" << endl;
				cout << "To see the menu press                  6" << endl;
				cout << "To add a new task press                7" << endl;
				cout << "To finish press                        8" << endl;
				break;

			case 7:	// New task
				createNewTask(Task);
				cout << "To see the menu press 6:" << endl;
				break;

			case 8: // Exit
				cout << "Closing program" << endl;
				break;

			default:
				cout << "Entry was not recognized enter again\n" << endl;
				break;
		}

	}
	Task.delet(Task);
	//delete Task;
    cout << "Press enter to continue ..." << endl;
    cin >> strOption;
	return 0;
}

// Detect if a key was pressed. To compile in Linux is required
int kbhit( void )
{
	struct timeval tv;
	fd_set read_fd;

	tv.tv_sec=0;
	tv.tv_usec=0;
	FD_ZERO( &read_fd );
	FD_SET( 0, &read_fd );

	if( select( 1, &read_fd, NULL, NULL, &tv ) == -1 )
		return 0;

	if( FD_ISSET( 0,&read_fd ))
		return 1;

	return 0;
}


void createNewTask(data &Task){

	string taskTexto;
	string strStarTime, strEndTime;
	unsigned int start, end,horaStart, minStart, horaEnd, minEnd;
	bool ok1, ok2;
	cout << "Creating a new task " << endl;
	cout << "Enter the task text : ";
	cin.ignore();
	getline (cin,taskTexto);		// I read the whole line of text
	cout << "What is the start time of the task? enter the time as follows 15:45" << endl;
	cout << "Time : ";
	cin >> strStarTime;
	cout << "What is the end time of the task?" << endl;
	cout << "Time : ";
	cin >> strEndTime;
	start = stringtoInt(strStarTime, horaStart, minStart, ok1);
	end   = stringtoInt(strEndTime, horaEnd, minEnd, ok2);
	if(ok1 && ok2){
		Task.addNode(start, end, taskTexto, "Have you done it?");
		cout << "The new task has been created" << endl;
		cout << "Task : " << taskTexto << " Start " << horaStart <<":"<< minStart << " End " << horaEnd << ":" << minEnd << endl;
	}
	else{
		cout << "Error!, the new task hasn't been created" << endl;
	}
}


// initialization of the tasks
void taskInit(data &Task){

	Task.addNode( 0, 0,  7, 0,"Sleep",					"You should be sleeping");
	Task.addNode( 7,12,  7,23,"Take the morning pills",	"Did you take the pills?");
	Task.addNode( 7,31,  8, 0,"Have breakfast",			"Did you have breakfast?");
	Task.addNode(11,30, 12, 0,"Cook",					"Did you cook?");
	Task.addNode(12,01, 12,45,"Lunch time",				"Did you have lunch?");
	Task.addNode(14,45, 15,45,"Take a nap",				"Did you take a nap?");
	Task.addNode(17, 0, 18, 0,"Go to the supermarket",	"Did you do the shopping?");
	Task.addNode(19,01, 20, 0,"Take the night pills",	"Did you take the pills?");
	Task.addNode(20,01, 21,45,"Have dinner",			"Did you have dinner?");

}

unsigned int stringtoInt(string str,unsigned int &hora, unsigned int &min, bool &ok){

	char charHora[] = {'0', '0','\0'},charMin[] = {'0', '0','\0'};
	size_t found = str.find(':');
	if (found!=std::string::npos){
		str.copy(charHora,2,0);
		str.copy(charMin,2,3);
		hora = stoi(charHora);
		min = stoi(charMin);
		ok = true;
	if (hora > 24){ hora = 24;}
	if (min  > 60){ min  = 60;}
		return(hora * 60 + min);
	}
	else{
		cout << "Entry was not recognized" <<endl;
		cout << "I didn't find the : in the string" << endl;
		ok = false;
		return 0;
	}
}

int stringtoInt(string option){
	int i;
    try {
        i = stoi(option);	// string -> integer
    }
    catch (...) {
		i = 9;				// error management
    	//cout << "Entry was not recognized enter again\n" << endl;
    }
    return (i);
}



/* Three-Second Delay */
void Delay( long int secs ){

	time_t tv_sec;
	tv_sec = ( time_t )secs;
	struct timespec delta = { tv_sec, 0}; // {seconds, nanoseconds}
	while (nanosleep(&delta, &delta));
}





