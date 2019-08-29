//============================================================================
// Name        : Task.cpp
// Author      : Gonzalo, Yarvi
// Version     : 3.0
// Created on  : August 27, 2019
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;



class timeControl{
	private:
		unsigned int speed;
		unsigned int offset;
		unsigned int currentSec;
		time_point<system_clock> startDelta,end;

	public:
		timeControl();
		//~timeControl();
		unsigned int hour();
		unsigned int min();
		unsigned int currentMin();
		unsigned int systemTime(unsigned int, unsigned int);
		void speedFactor(unsigned int);
};

timeControl::timeControl(){

	startDelta = system_clock::now();
	speed = 1;							// Speed factor 1 to 200
	offset = 0;
	currentSec = 0;
}

unsigned int timeControl::currentMin(){
	unsigned int timeMin;
	timeMin = timeControl::systemTime( speed , offset )/60;
	return (timeMin);
}

unsigned int timeControl::hour(){
	unsigned int currentHour;
	currentHour = timeControl::systemTime( speed , offset )/3600;
	return (currentHour);
}

unsigned int timeControl::min(){
	unsigned int auxHora, auxMin, currentMin;
	currentMin = timeControl::systemTime( speed , offset )/60;
	auxHora = currentMin / 60;
	auxMin = currentMin - (auxHora * 60);
	return (auxMin);
}

// SystemTime(Speed , TimeDelta, Offset)  Take the system SystemTime
//	Speed: speed factor entered by the user
//	TimeDelta: From this moment the time begins to be multiplied by the multiplication factor.
//	Offset: The difference between the real time and the time displayed on the screen

unsigned int timeControl::systemTime( unsigned int mult, unsigned int Offset){

	unsigned int Delta, TimeSystem, TimeNuevo;
	time_t now;
	struct tm *loc_time; 								// Converting current time to local time
	now = time ( NULL ); 								// Getting current time of system
	loc_time = localtime ( &now );

	end = system_clock::now();
	TimeSystem = loc_time->tm_hour* 3600 + loc_time->tm_min*60 + loc_time->tm_sec; 	// SystemTime

	duration<double> elapsed_seconds = end - startDelta;
	Delta = (unsigned int)elapsed_seconds.count();
	TimeNuevo = TimeSystem + Offset + ( Delta  * ( mult - 1 ));

	return(TimeNuevo);
}

void timeControl::speedFactor(unsigned int extSpeed){

	unsigned int timeDelta;
	currentSec = timeControl::systemTime( speed , offset );	// I save the fictitious time "shown on the screen"
	timeDelta = systemTime( 1 ,0 ); 					// I save the system time "the real time"
	startDelta = system_clock::now();
	duration<double> elapsed_seconds = end - startDelta;
	//Necesito calcular el valor de los segundos del sistema
	offset = currentSec - timeDelta;							// Offset = "shown on the screen" - "the real time"
	speed = extSpeed;

}




