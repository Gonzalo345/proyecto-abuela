//============================================================================
// Name        : Program.c
// Author      : Jorge Gonzalo Cordo Yarvi
// Version     : 2.0
// Description : Create an agenda for my grandmother
// Compiler    : Eclipse IDE
//============================================================================

#include <sys/select.h>  							// To compile in Linux
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>

using namespace std;

#define EndKey          0
#define MaxTask         40

struct Str_Task {
	unsigned On: 1;
	unsigned Done: 1;
	unsigned Text1: 1;
	unsigned Text2: 1;
	unsigned Text3: 1;
	int StartHour, StartMin, Start;
	int EndHour, EndMin, End;
	char  Text4[40];
	char  Text5[40];
};

void 		TaskInit( Str_Task [], int );									// Initialization of tasks
void 		Agenda( Str_Task [], int );										// Agenda Loop
void 		TaskStatus( Str_Task [], unsigned int );						// Status of tasks
void 		Delay( void );													// 3-second delay
int 		kbhit( void );													// Controls if a key was pressed
int 		SystemTime( int, int, int );									// I take the system SystemTime
int 		HMS_Seg( int, int, int );										// Converts hours, minutes and seconds into a single integer.


int main ()
{
	const int arraySize = MaxTask; 											// size of array Str_Task
	int length;
	unsigned int i, Hour, Min, CurrentSec, Day_User, CurrentMin;
	char Option = 7;
	char TextTask[40];
	unsigned int Speed = 1;													// Speed factor 1 to 200
	unsigned int TimeDelta = 0;
	unsigned int Offset = 0;
	unsigned int NumTask = 9; 												// Number of tasks

	Str_Task Task[MaxTask];


	TaskInit( Task, arraySize );											// Initialization of tasks
	TimeDelta = SystemTime( Speed , TimeDelta, Offset ); 					// I save the SystemTime time in seconds
	cout << " ************************************************** " << endl;
	cout << "           AGENDA FOR MY GRANDMOTHER" 				   << endl;
	cout << " ************************************************** " << endl;

	for(i=0; i < MaxTask; i++) {											// Printing of scheduled tasks
		if ( Task[i].On == 1 ){
			cout << "Task :" << i << " "<< Task[i].Text4 << " Start " << Task[i].StartHour
				 << ":" << Task[i].StartMin << " End " << Task[i].EndHour << ":"
				 << Task[i].EndMin << endl;
		}
	}
	CurrentSec = SystemTime( Speed , TimeDelta, Offset );
	CurrentMin = CurrentSec / 60;
	Hour = CurrentMin / 60;						 							// Displaying time in standard format
	Min = CurrentMin - ( Hour * 60);
	cout << "Actual Time: " << Hour << ":" << Min << endl << endl;
 	cout << "To see the task of the moment press    1" << endl;
	cout << "To input an hour press                 2" << endl;
	cout << "To see the the actual Time             3" << endl;
	cout << "To see the status of the task          4" << endl;
	cout << "To input a speed factor press          5" << endl;
	cout << "To see the menu press                  6" << endl;
	cout << "To add a new task press                7" << endl;
	cout << "To finish press                        8" << endl << endl;

	while ( Option !=  '8' ){

		while (!kbhit()) { 													// While no key is pressed
			CurrentSec = SystemTime( Speed , TimeDelta, Offset ); 			// Take the current time
			CurrentMin = CurrentSec / 60;
			Agenda( Task,   CurrentMin );  									// Controls the automatic execution of tasks
		}
		cin >> Option;

		switch (Option) {
			/* Task of the moment */
			case '1':
				
				CurrentSec = SystemTime( Speed , TimeDelta, Offset ); 		// Take the current time
				CurrentMin = CurrentSec / 60; 
				Hour = CurrentMin / 60;
				Min = CurrentMin - ( Hour * 60 );
				cout << "\nActual Time: " << Hour << ":" << Min << endl;
				TaskStatus( Task, CurrentMin );
				cout <<"To see the menu press 6:" << endl;
				break;

			/* Enter an hour, to show which task would be running */
			case '2':
				
				cout << "Enter the hour first, then the minutes" << endl;
				cout << "Hours  : ";
				cin >> Hour;
				cout << "Minutes: ";
				cin >> Min;
				Day_User = HMS_Seg( Hour , Min, 0 ) / 60;
				TaskStatus( Task, Day_User );
				cout << "To see the menu press 6:" << endl;
				break;

			/* Displaying the current time in standard format */
			case '3':
				
				CurrentSec = SystemTime( Speed , TimeDelta, Offset );
				CurrentMin = CurrentSec / 60;
				Hour = CurrentMin / 60;
				Min = CurrentMin - ( Hour * 60 );
				cout << "Actual Time: " << Hour << ":" << Min << endl;
				cout << "To see the menu press 6:" << endl;
				break;

			/* Show the status of tasks */
			case '4':

				for( i=0; i < MaxTask; i++ ) {
					if ( Task[i].On == 1 ){
						if ( Task[i].Done == 1 ){
							cout << "Task " << i << ": " << Task[i].Text4 << "Start " << Task[i].StartHour << ":" << Task[i].StartMin << " End " << Task[i].EndHour << ":" << Task[i].EndMin << "Status done!" << endl;
						}
						else{
							cout << "Task " << i << ":" << Task[i].Text4 <<" Start " << Task[i].StartHour << ":" << Task[i].StartMin << " End " << Task[i].EndHour << ":" << Task[i].EndMin << " Status undone!" << endl;
						}
					}
				}
				Delay();
				cout << "To see the menu press 6:" << endl;
				break;

			/* Increase the speed factor */
			case '5':

				CurrentSec = SystemTime( Speed , TimeDelta, Offset );
				Hour = CurrentSec / 3600;
				Min = (CurrentSec - ( Hour * 3600)) / 60;
				cout << "Actual Time: " << Hour << ":" << Min << endl;
				CurrentSec = SystemTime( Speed , TimeDelta, Offset );			// I save the fictitious time "shown on the screen"
				TimeDelta = SystemTime( 1 , 0, 0 ); 							// I save the system time "the real time"
				Offset = CurrentSec - TimeDelta;								// Offset = "shown on the screen" - "the real time"
				cout << "Enter the speed factor ( 1 to 200 ) :" << endl;
				cin >> Speed;
				cout << "Speed :" << Speed << endl;
				if ( Speed < 1 ){
					Speed = 1;
				}
				if ( Speed > 200 ){
					Speed = 200;
				}
				cout << "To see the menu press 6:" << endl;
				break;

			/* Show the menu */
			case '6':

			 	cout << "To see the task of the moment press    1" << endl;
				cout << "To input an hour press                 2" << endl;
				cout << "To see the the actual Time             3" << endl;
				cout << "To see the status of the task          4" << endl;
				cout << "To input a speed factor press          5" << endl;
				cout << "To see the menu press                  6" << endl;
				cout << "To add a new task press                7" << endl;
				cout << "To finish press                        8" << endl;
				break;

				/* New task */
			case '7':
				
				cout << "To create a new task " << endl << "Enter the task text : ";
				std::cin.ignore();
				std::cin.getline ( TextTask , 40 );   							// I read the whole line of text 
				cout << "What is the start time of the task?" << endl << "Hours : ";
				cin >> Task[NumTask].StartHour;				
				cout << "Minutes: ";
				cin >> Task[NumTask].StartMin;
				cout << "What is the end time of the task?" << endl << "Hours : ";
				cin >> Task[NumTask].EndHour;
				cout << "Minutes: ";
				cin >> Task[NumTask].EndMin;
				length = strlen( TextTask );									// I complete the string with spaces to match the lengths
				for( i = 0; i < 25; i++){
					if ( length < 25 ) {
						TextTask[ i + length ]= ' ';
					}
				}
				TextTask[25]='\0';
				strcpy( Task[NumTask].Text4, TextTask);
				strcpy( Task[NumTask].Text5, "Have you done it?" );
				cout << "The new task has been created" << endl;
				cout << "Task :" << NumTask << " "<< Task[NumTask].Text4 << " Start " << Task[NumTask].StartHour
					 << ":" << Task[NumTask].StartMin << " End " << Task[NumTask].EndHour << ":" << Task[NumTask].EndMin << endl;
				Task[NumTask].Start = HMS_Seg(Task[NumTask].StartHour, Task[NumTask].StartMin, 0)/60;
				Task[NumTask].End = HMS_Seg(Task[NumTask].EndHour, Task[NumTask].EndMin, 0)/60;
				Task[NumTask].On = 1;
				NumTask++;
				cout << "To see the menu press 6:" << endl;
				break;

			/* Default */
			default :

				cout << "Entry was not recognized enter again\n" << endl;
				break;
		}

	}
    	cout << "Press enter to continue ..." << endl;
	while ( !kbhit() );

	return 0;
}

/* Detect if a key was pressed. To compile in Linux is required*/
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

/* Controls if a key was pressed */
void TaskStatus( struct Str_Task  Task[], unsigned int CurrentTime ){

	int i, Act;
	char text;
	
	Act = 0;
	for( i = 0; i < MaxTask; i++ ) {
		if (CurrentTime >= Task[i].Start && CurrentTime <= Task[i].End  && Act == 0){
			Delay();
			cout << "Task " << i << ":" << Task[i].Text4 << endl;  				//I look if any task is running.
			if (Task[i].Done){
				Delay();
				cout << "Relax, you have already done it!" << endl;
			}
			else{
				Delay();
				cout << "Status Undone!," << Task[i].Text5 << endl << "Y/N : ";
				cin >> text;
				if ( text == 'y' || text == 'Y'){
					Task[i].Done = 0x01;
					Delay();
					cout << "New status done!" << endl;
				}
				if ( text == 'n' || text == 'N'){
					Task[i].Done = 0x00;
					Delay();
					cout << "Status undone!" << endl;
				}
			}
			Act = 1; 															// Loop execution flag
		}
	}
	if ( Act == 0 ){
		Delay();
		cout << "There are no tasks at that time!:" << endl;
	}
	Delay();
}

/*
 SystemTime(Speed , TimeDelta, Offset)  Take the system SystemTime
	Speed: speed factor entered by the user
	TimeDelta: From this moment the time begins to be multiplied by the multiplication factor.
	Offset: The difference between the real time and the time displayed on the screen
*/

int SystemTime( int mult, int TimeDelta, int Offset){

	unsigned int Delta, TimeSystem, TimeNuevo;
	time_t now;
	struct tm *loc_time;      													// Converting current time to local time
	now = time ( NULL );    		    										// Getting current time of system
	loc_time = localtime ( &now );

	TimeSystem = HMS_Seg( loc_time->tm_hour, loc_time->tm_min, loc_time->tm_sec ); 	// SystemTime
	Delta = ( TimeSystem - TimeDelta );
	if ( Delta < 1){
		Delta = 1;
	}
	TimeNuevo = TimeSystem + Offset + ( Delta  * ( mult - 1 ));
	return(TimeNuevo);
}

/* Convert hours, minutes and seconds into a single number */
int HMS_Seg( int Hour, int Min, int Sec ){

	int CurrentTime;
	CurrentTime = Hour * 3600 + Min * 60 + Sec;
	return ( CurrentTime );
}

/* Three-Second Delay */
void Delay( void ){

	time_t seconds, aux;
	seconds = time( NULL );
	aux = time( NULL );
	while( seconds <= aux + 3 )
		seconds = time( NULL );
}

/* Control of execution of tasks */
void Agenda( struct Str_Task  Task[], int SecondsDay ){

	int i, Hour, Min;
	Hour = SecondsDay / 60;
	Min = SecondsDay - ( Hour * 60);
	for( i = 0; i < MaxTask; i++ ) {
		/* Task starting? */
		if ( SecondsDay >= Task[i].Start && SecondsDay < Task[i].End - 10 && Task[i].Text1 == 0){
			Task[i].Text1 = 1;  										// I show the message once
			cout << "\nActual Time: "<< Hour << ":" << Min << endl;
			cout <<"Task: "<< i << " is starting !: " << Task[i].Text4 << endl << "Start time " << Task[i].StartHour << ":" << Task[i].StartMin << " ------> End time "<< Task[i].EndHour << ":" << Task[i].EndMin << endl;
		}
		/* Ten minutes left to finish the task? */
		if ( SecondsDay >= ( Task[i].End -10 ) && SecondsDay < Task[i].End && Task[i].Text2 == 0){
			if ( Task[i].Done == 0 ){
				Task[i].Text2 = 1;     									// I show the message once
				cout << "\nActual Time: " << Hour << ":" << Min << endl;
				cout <<"In 10 minutes the task :" << i << " " << Task[i].Text4 <<" will be finished" << endl;
			}
		}
		/* Activity ending? */
		if ( SecondsDay >= Task[i].End && SecondsDay < Task[i].End + 4 && Task[i].Text3 == 0 ){
			Task[i].Text3 = 1;   										// I show the message once
			cout << "\nActual Time: " << Hour << ":" << Min << endl;
			cout <<"The task: "<< i <<" is finished " << Task[i].Text4 << "End time :" << Task[i].EndHour << ":" << Task[i].EndMin << endl;
		}
	}
}

/* initialization of the tasks */
void TaskInit( struct Str_Task  Task[], int sizeOfArray ){

	int i;

	for( i = 0; i < sizeOfArray; i++ ) {
		Task[i].On = 0;
		Task[i].Done = 0;
		Task[i].Text1 = 0;
		Task[i].Text2 = 0;
		Task[i].Text3 = 0;
		Task[i].StartHour = 0;
		Task[i].StartMin = 0;
		Task[i].EndHour = 0;
		Task[i].EndMin = 0;
	}
	Task[0].StartHour = 0;
	Task[0].StartMin = 0;
	Task[0].EndHour = 7;
	Task[0].EndMin = 0;
	Task[0].On = 1;
	strcpy( Task[0].Text4, "Sleep                    " );
	strcpy( Task[0].Text5, "You should be sleeping   " );

	Task[1].StartHour = 7;
	Task[1].StartMin = 12;
	Task[1].EndHour = 7;
	Task[1].EndMin = 23;
	Task[1].On = 1;
	strcpy( Task[1].Text4, "Take the morning pills   " );
	strcpy( Task[1].Text5, "Did you take the pills?  " );

	Task[2].StartHour = 7;
	Task[2].StartMin = 31;
	Task[2].EndHour = 8;
	Task[2].EndMin = 0;
	Task[2].On = 1; 
	strcpy( Task[2].Text4, "Have breakfast           " );
	strcpy( Task[2].Text5, "Did you have breakfast?  " );

	Task[3].StartHour = 11;
	Task[3].StartMin = 30;
	Task[3].EndHour = 12;
	Task[3].EndMin = 00;
	Task[3].On = 1;
	strcpy( Task[3].Text4, "Cook                     " );
	strcpy( Task[3].Text5, "Did you cook?            " );

	Task[4].StartHour = 12;
	Task[4].StartMin = 01;
	Task[4].EndHour = 12;
	Task[4].EndMin = 45;
	Task[4].On = 1;
	strcpy( Task[4].Text4, "Lunch time               " );
	strcpy( Task[4].Text5, "Did you have lunch?      " );

	Task[5].StartHour = 14;
	Task[5].StartMin = 45;
	Task[5].EndHour = 15;
	Task[5].EndMin = 45;
	Task[5].On = 1;
	strcpy( Task[5].Text4, "Take a nap               " );
	strcpy( Task[5].Text5, "Did you take a nap?      " );

	Task[6].StartHour = 17;
	Task[6].StartMin = 0;
	Task[6].EndHour = 18;
	Task[6].EndMin = 0;
	Task[6].On = 1;
	strcpy( Task[6].Text4, "Go to the supermarket    " );
	strcpy( Task[6].Text5, "Did you do the shopping? " );

	Task[7].StartHour = 19;
	Task[7].StartMin = 01;
	Task[7].EndHour = 20;
	Task[7].EndMin = 00;
	Task[7].On = 1;
	strcpy( Task[7].Text4, "Take the night pills     " );
	strcpy( Task[7].Text5, "Did you take the pills?  " );

	Task[8].StartHour = 20;
	Task[8].StartMin = 01;
	Task[8].EndHour = 21;
	Task[8].EndMin = 45;
	Task[8].On = 1;
	strcpy( Task[8].Text4, "Have dinner              " );
	strcpy( Task[8].Text5, "Did you have dinner?     " );

	for( i = 0; i < sizeOfArray; i++ ) {
		Task[i].Start = HMS_Seg(Task[i].StartHour, Task[i].StartMin, 0)/60;
		Task[i].End = HMS_Seg(Task[i].EndHour, Task[i].EndMin, 0)/60;		// I turn hours and minutes into a single number.
	}
}
