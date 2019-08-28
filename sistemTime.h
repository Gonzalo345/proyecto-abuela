/*
 * sistemTime.h
 *
 *  Created on: Aug 27, 2019
 *      Author: gonzalo
 */

#ifndef SISTEMTIME_H_
#define SISTEMTIME_H_

#include <time.h>
#include <chrono>

class timeControl{
	private:
		unsigned int speed;
		unsigned int timeDelta;
		unsigned int offset;
		unsigned int currentSec;

	public:
		timeControl();
		//~timeControl();
		unsigned int hour();
		unsigned int min();
		unsigned int currentMin();
		unsigned int systemTime(unsigned int,unsigned int,unsigned int);
		void speedFactor(unsigned int);
};


timeControl::timeControl(){
	speed = 1;							// Speed factor 1 to 200
	timeDelta = 0;
	offset = 0;
	timeDelta = timeControl::systemTime( speed , timeDelta, offset );
}

unsigned int timeControl::currentMin(){
	unsigned int timeMin;
	timeMin = timeControl::systemTime( speed , timeDelta, offset )/60;
	return (timeMin);
}

unsigned int timeControl::hour(){
	unsigned int currentHour;
	currentHour = timeControl::systemTime( speed , timeDelta, offset )/3600;
	return (currentHour);
}

unsigned int timeControl::min(){
	unsigned int auxHora, auxMin, currentMin;
	currentMin = timeControl::systemTime( speed , timeDelta, offset )/60;
	auxHora = currentMin / 60;
	auxMin = currentMin - (auxHora * 60);
	return (auxMin);
}

/*
 SystemTime(Speed , TimeDelta, Offset)  Take the system SystemTime
	Speed: speed factor entered by the user
	TimeDelta: From this moment the time begins to be multiplied by the multiplication factor.
	Offset: The difference between the real time and the time displayed on the screen
*/

unsigned int timeControl::systemTime( unsigned int mult, unsigned int TimeDelta, unsigned int Offset){

	unsigned int Delta, TimeSystem, TimeNuevo;
	time_t now;
	struct tm *loc_time; 								// Converting current time to local time
	now = time ( NULL ); 								// Getting current time of system
	loc_time = localtime ( &now );

	TimeSystem = loc_time->tm_hour * 3600 + loc_time->tm_min*60 + loc_time->tm_sec; 	// SystemTime
	Delta = ( TimeSystem - TimeDelta );
	if ( Delta < 1){ Delta = 1;	}
	TimeNuevo = TimeSystem + Offset + ( Delta  * ( mult - 1 ));
	return(TimeNuevo);
}

void timeControl::speedFactor(unsigned int extSpeed){

	currentSec = timeControl::systemTime( speed , timeDelta, offset );	// I save the fictitious time "shown on the screen"
	timeDelta = timeControl::systemTime( 1 , 0, 0 ); 					// I save the system time "the real time"
	offset = currentSec - timeDelta;									// Offset = "shown on the screen" - "the real time"
	speed = extSpeed;

}

#endif /* SISTEMTIME_H_ */

