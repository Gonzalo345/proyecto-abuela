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
#include <iomanip>
#include <time.h>
#include <iostream>
#include "include.h"

using namespace std;

#define EndKey          0
#define MaxTask         40


int main (int argc, char** argv)
{
	int Hour, Min, CurrentSec, Day_User, CurrentMin;
	char Option = 7;

	int Speed = 1;							// Speed factor 1 to 200
	int TimeDelta = 0;
	int Offset = 0;
	Str_Task *Task = NULL; 					// New node
	TaskInit( Task );						// Initialization of tasks

	TimeDelta = SystemTime( Speed , TimeDelta, Offset ); 					// I save the SystemTime time in seconds

	cout << " ************************************************** " << endl;
	cout << "           AGENDA FOR MY GRANDMOTHER				 " << endl;
	cout << " ************************************************** " << endl;

	showTask(Task);
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
			Delay( 1 );
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
				cout << "To see the menu press 6:" << endl;
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

				showTask(Task);
				Delay(3);
				cout << "To see the menu press 6:" << endl;
				break;

			/* Increase the speed factor */
			case '5':

				CurrentSec = SystemTime( Speed , TimeDelta, Offset );
				Hour = CurrentSec / 3600;
				Min = (CurrentSec - ( Hour * 3600)) / 60;
				cout << "Actual Time: " << Hour << ":" << Min << endl;
				CurrentSec = SystemTime( Speed , TimeDelta, Offset );		// I save the fictitious time "shown on the screen"
				TimeDelta = SystemTime( 1 , 0, 0 ); 				// I save the system time "the real time"
				Offset = CurrentSec - TimeDelta;				// Offset = "shown on the screen" - "the real time"
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

				CreateNewTask(Task);
				cout << "To see the menu press 6:" << endl;
				break;

			/* Exit */
			case '8':

				cout << "Closing program" << endl;
				break;

			/* Default */
			default :

				cout << "Entry was not recognized enter again\n" << endl;
				break;
		}

	}
	while (Task != NULL){
		eliminarLista(Task);
	}
    cout << "Press enter to continue ..." << endl;
	while ( !kbhit() );

	return 0;
}
void eliminarLista(Str_Task *&Task){
	Str_Task *aux = Task;
	Task = aux->Next;
	delete aux;
}

void addStack(Str_Task *&Task, int Start, int End, char Text4[], char Text5[]){
	Str_Task *new_task = new  Str_Task();
	new_task->Start = Start;
	new_task->End = End;
	new_task->StartHour = Start/60;
	new_task->StartMin = Start-((Start/60)*60);
	new_task->EndHour = End/60;
	new_task->EndMin = End-((End/60)*60);
	new_task->On = 1;
	new_task->Done = 0;
	new_task->Text1 = 0;
	new_task->Text2 = 0;
	new_task->Text3 = 0;
	strcpy( new_task->Text4, (char *)Text4);
	strcpy( new_task->Text5, (char *)Text5);
	new_task->Next = Task;
	Task = new_task;
	//cout << "The node was correctly added to the battery" << endl;
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
void TaskStatus( struct Str_Task  *&Task, int CurrentTime ){

	int i, Act;
	char text;
	Str_Task *actual = new Str_Task();
	actual = Task;
	Act = 0;
	i = 0;
	while (actual != NULL){
		if (CurrentTime >= actual->Start && CurrentTime <= actual->End  && Act == 0){
			Delay(3);
			cout << "Task " << i++ << ":" << actual->Text4 << endl;  				//I look if any task is running.
			if (actual->Done){
				Delay(3);
				cout << "Relax, you have already done it!" << endl;
			}
			else{
				Delay(3);
				cout << "Status Undone!," << actual->Text5 << endl << "Y/N : ";
				cin >> text;
				if ( text == 'y' || text == 'Y'){
					actual->Done = 0x01;
					Delay(3);
					cout << "New status done!" << endl;
				}
				if ( text == 'n' || text == 'N'){
					actual->Done = 0x00;
					Delay(3);
					cout << "Status undone!" << endl;
				}
			}
			Act = 1; 															// Loop execution flag
		}
		actual = actual->Next;
	}
	if ( Act == 0 ){
		Delay(3);
		cout << "There are no tasks at that time!:" << endl;
	}
	Delay(3);
	delete actual;
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
	struct tm *loc_time; 								// Converting current time to local time
	now = time ( NULL ); 								// Getting current time of system
	loc_time = localtime ( &now );

	TimeSystem = HMS_Seg( loc_time->tm_hour, loc_time->tm_min, loc_time->tm_sec ); 	// SystemTime
	Delta = ( TimeSystem - TimeDelta );
	if ( Delta < 1){
		Delta = 1;
	}
	TimeNuevo = TimeSystem + Offset + ( Delta  * ( mult - 1 ));
	return(TimeNuevo);
}

/* Control of execution of tasks */
void Agenda( struct Str_Task  *&Task, int SecondsDay ){

	int i = 0, Hour, Min;
	Hour = SecondsDay / 60;
	Min = SecondsDay - ( Hour * 60);
	Str_Task *actual = new Str_Task();
	actual = Task;
	while(actual!=NULL){
		/* Task starting? */
		if ( SecondsDay >= actual->Start && SecondsDay < actual->End - 10 && actual->Text1 == 0){
			actual->Text1 = 1;  										// I show the message once
			cout << "\nActual Time: "<< Hour << ":" << Min << endl;
			cout <<"Task: "<< i++ << " is starting !: " << actual->Text4 << endl << "Start time " << actual->StartHour << ":" << actual->StartMin << " ------> End time "<< actual->EndHour << ":" << actual->EndMin << endl;
		}
		/* Ten minutes left to finish the task? */
		if ( SecondsDay >= ( actual->End -10 ) && SecondsDay < actual->End && actual->Text2 == 0){
			if ( actual->Done == 0 ){
				actual->Text2 = 1;     									// I show the message once
				cout << "\nActual Time: " << Hour << ":" << Min << endl;
				cout <<"In 10 minutes the task :" << i << " " << actual->Text4 <<" will be finished" << endl;
			}
		}
		/* Activity ending? */
		if ( SecondsDay >= actual->End && SecondsDay < actual->End + 4 && actual->Text3 == 0 ){
			actual->Text3 = 1;   										// I show the message once
			cout << "\nActual Time: " << Hour << ":" << Min << endl;
			cout <<"The task: "<< i <<" is finished " << actual->Text4 << "End time :" << actual->EndHour << ":" << actual->EndMin << endl;
		}
		actual = actual->Next;
	}
	delete actual;
}

void CreateNewTask(Str_Task *&Task ){

	char Text4[40], Text5[40];//, Time[5];
	string strTime;
	int i;
	int length;
	int tens, units, hour, minutes;
	int Start, End;

	cout << "Creating a new task " << endl;
	cout << "Enter the task text : ";
	cin.ignore();
	cin.getline ( Text4 , 40 );   		// I read the whole line of text
	length = strlen( Text4 );			// I complete the string with spaces to match the lengths
	for( i = 0; i < 25; i++){
		if ( length < 25 ) {
			Text4[ i + length ]= ' ';
		}
	}
	Text4[25]='\0';
	strcpy( Text5, "Have you done it?" );

	cout << "What is the start time of the task? enter the time as follows 15:45" << endl;
	cout << "Time : ";
	cin >> strTime;

	if (strTime[2] == ':'){ //findChar(':',strTime)){
		tens = (int)strTime[0] - 48;
		units = (int)strTime[1] - 48;
		hour = tens * 10 + units;
		tens = (int)strTime[3] - 48;
		units = (int)strTime[4] - 48;
		minutes = tens * 10 + units;
		Start = HM_Min(hour,minutes);
	}
	else{
		cout << "I didn't find the : in the string" << endl;

	}
	cout << "What is the end time of the task?" << endl;
	cout << "Time : ";
	cin >> strTime;

	if (strTime[2] == ':'){
		tens = (int)strTime[0] - 48;
		units = (int)strTime[1] - 48;
		hour = tens * 10 + units;
		tens = (int)strTime[3] - 48;
		units = (int)strTime[4] - 48;
		minutes = tens * 10 + units;
		End = HM_Min(hour,minutes);
	}
	else{
		cout << "I didn't find the : in the string" << endl;
	}

	addStack( Task, Start, End, Text4, Text5 );
	cout << "The new task has been created" << endl;
	cout << "Task : " << Task->Text4
		 << " Start " << Task->StartHour <<":"<< Task->StartMin
		 << " End " << Task->EndHour << ":" << Task->EndMin << endl;
}

/* initialization of the tasks */
void TaskInit( struct Str_Task  *&Task ){

	int Start = 0;
	int End = 0;
	char Text4[40];
	char Text5[40];

	Start = HM_Min(0, 0);
    End = HM_Min(7, 0);
	strcpy( Text4, "Sleep                    " );
	strcpy( Text5, "You should be sleeping   " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min(7/*hours*/, 12/*min*/);
    End = HM_Min(7, 23);
	strcpy( Text4, "Take the morning pills   " );
	strcpy( Text5, "Did you take the pills?  " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 7, 31);
    End = HM_Min( 8, 0);
	strcpy( Text4, "Have breakfast           " );
	strcpy( Text5, "Did you have breakfast?  " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 11, 30);
    End = HM_Min( 12, 0);
	strcpy( Text4, "Cook                     " );
	strcpy( Text5, "Did you cook?            " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 12, 01);
    End = HM_Min( 12, 45);
	strcpy( Text4, "Lunch time               " );
	strcpy( Text5, "Did you have lunch?      " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 14, 45);
    End = HM_Min( 15, 45);
	strcpy( Text4, "Take a nap               " );
	strcpy( Text5, "Did you take a nap?      " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 17, 0);
    End = HM_Min( 18, 0);
	strcpy( Text4, "Go to the supermarket    " );
	strcpy( Text5, "Did you do the shopping? " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 19, 01);
    End = HM_Min( 20, 0);
	strcpy( Text4, "Take the night pills     " );
	strcpy( Text5, "Did you take the pills?  " );
	addStack( Task, Start, End, Text4, Text5 );

	Start = HM_Min( 20, 01);
    End = HM_Min( 21, 45);
	strcpy( Text4, "Have dinner              " );
	strcpy( Text5, "Did you have dinner?     " );
	addStack( Task, Start, End, Text4, Text5 );

}

