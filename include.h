/*Ejercicio 2: Construya una clase Tiempo que contenga los siguientes atributos
enteros: horas, minutos y segundos. Haga que la clase contenga 2 constructores,
el primero debe tener 3 parámetros Tiempo(int,int,int) y el segundo sólo
tendrá un campo que serán los segundos y desensamble el número entero largo
en horas, minutos y segundos.*/

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

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
	Str_Task *Next;
};

void 	TaskInit( Str_Task *& );				// Initialization of tasks
void 	Agenda( Str_Task *&, int );					// Agenda Loop
void 	TaskStatus( Str_Task *&, int );	// Status of tasks
void 	Delay( long int secs );								// 3-second delay
int 	kbhit( void );								// Controls if a key was pressed
int 	SystemTime( int, int, int );				// I take the system SystemTime
int 	HMS_Seg( int, int, int );					// Converts hours, minutes and seconds into a single integer.
int 	HM_Min( int, int );
void 	CreateNewTask(Str_Task *& );
void 	showTask(Str_Task *& );
int 	findChar(char , string myString);

void 	addStack( Str_Task *&, int, int, char *[], char *[]);
void 	eliminarLista(Str_Task *&);

/* Convert hours, minutes and seconds into a single number */
int HMS_Seg( int Hour, int Min, int Sec ){

	int CurrentTime;
	CurrentTime = Hour * 3600 + Min * 60 + Sec;
	return ( CurrentTime );
}

int HM_Min( int Hour, int Min ){

	int CurrentTime;
	CurrentTime = Hour * 60 + Min;
	return ( CurrentTime );
}

/* Three-Second Delay */
void Delay( long int secs ){

	time_t tv_sec;
	tv_sec = ( time_t )secs;
	struct timespec delta = { tv_sec/*secs*/, 0 /*nanosecs*/};
	//struct timespec delta = { 3/*secs*/, 0 /*nanosecs*/};
	while (nanosleep(&delta, &delta));
}

void 	showTask(Str_Task *&Task ){
	Str_Task *actual = new Str_Task();
	actual = Task;
	int i = 0;
	while(actual!=NULL){
		if ( actual->On == 1 ){
			if ( actual->Done == 1 ){
				cout << "Task  " << i++ << ":" << actual->Text4;
				cout << "Start " << setw(2) << setfill(' ') << actual->StartHour << ":"
					             << setw(2) << setfill('0') << actual->StartMin;
				cout << "  End " << setw(2) << setfill(' ') << actual->EndHour   << ":"
						         << setw(2) << setfill('0') << actual->EndMin;
				cout << "Status done!" << endl;
			}
			else{
				cout << "Task  " << i++ << ":" << actual->Text4;
				cout <<" Start " << setw(2) << setfill(' ') << actual->StartHour << ":"
								 << setw(2) << setfill('0') << actual->StartMin;
				cout << "  End " << setw(2) << setfill(' ') << actual->EndHour   << ":"
								 << setw(2) << setfill('0') << actual->EndMin;
				cout << " Status undone!" << endl;
			}
		}
		actual = actual->Next;
	}
	delete actual;
}

int findChar(char c, string str)
{
	std::size_t found = str.find(':');
	 if (found!=std::string::npos){
		 return 1;
	 }
	 return 0;
}


