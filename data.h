//============================================================================
// Name        : Task.cpp
// Author      : Gonzalo
// Version     : 3.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include <string.h>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;



class data{
	private:
		struct strTask{
			unsigned done: 1;
			unsigned flag1: 1;
			unsigned flag2: 1;
			unsigned flag3: 1;
			int startHour, startMin;
			int endHour, endMin;
			int start;
			int end;
			string textTask;
			string question;
		};
		struct cmp{
		    bool operator()(const strTask &x, const strTask &y) const {
		        return x.start < y.start;
		    }
		};
		vector <strTask> task {};
		int hmsSeg( int, int );		// Converts hours, minutes and seconds into a single integer.
	public:
		//data();
		~data();
		void showTasks();
		void actualTask(int);
		void taskStatus(int);
		void addNode( int, int, string, string);
		void addNode( int, int, int, int, string, string);
};

data::~data(){
	task.clear();
}
/*
data::data(){
	task.start = Start;
	task.end = End;
	task.textTask = TextTask;
	task.question = Question;
	task.done = 0;
	task.startHour = 0;
	task.startMin = 0;
	task.endHour = 0;
	task.endMin = 0;
}*/

void data::addNode( int start, int end, string text1, string text2){

	strTask new_task;
	new_task.start = start;
	new_task.end = end;
	new_task.startHour = start / 60;
	new_task.startMin =  start - ((start / 60) * 60);
	new_task.endHour = end / 60;
	new_task.endMin = end - ((end / 60) * 60);
	new_task.done = 0;
	new_task.flag1 = 0;
	new_task.flag2 = 0;
	new_task.flag3 = 0;
	new_task.textTask = text1;
	new_task.question = text2;
	task.push_back(new_task);
	sort(task.begin(), task.end(), cmp());
	//cout << "The node was correctly added to the battery" << endl;
}

void data::addNode( int horaStart, int minStar, int horaEnd, int minEnd, string text1, string text2){

	strTask new_task;
	new_task.start = horaStart * 60 + minStar;
	new_task.end = horaEnd * 60 + minEnd;
	new_task.startHour = horaStart;
	new_task.startMin =  minStar;
	new_task.endHour = horaEnd;
	new_task.endMin = minEnd;
	new_task.done = 0;
	new_task.flag1 = 0;
	new_task.flag2 = 0;
	new_task.flag3 = 0;
	new_task.textTask = text1;
	new_task.question = text2;
	task.push_back(new_task);
	sort(task.begin(), task.end(), cmp());
	cout << "The node was correctly added to the battery" << endl;

}

void data::showTasks(){
	unsigned int i = 0;
	for(i = 0; i < task.size(); i++){
		if ( task[i].done == 1 ){
			cout << "Task [" << i << "]: " << left << setw(30) << setfill(' ') << task[i].textTask;
			cout << "Start " << right << setw(2) << setfill(' ') << task[i].startHour << ":" << left << setw(2) << setfill('0') << task[i].startMin;
			cout << "  End " << right << setw(2) << setfill(' ') << task[i].endHour   << ":" << left << setw(2) << setfill('0') << task[i].endMin;
			cout << " Status done!" << endl;
		}
		else{
			cout << "Task [" << i << "]: "  << left << setw(30) << setfill(' ') << task[i].textTask;
			cout << "Start " << right << setw(2) << setfill(' ') << task[i].startHour << ":" << left << setw(2) << setfill('0') << task[i].startMin;
			cout << "  End " << right << setw(2) << setfill(' ') << task[i].endHour   << ":" << left << setw(2) << setfill('0') << task[i].endMin;
			cout << " Status undone!" << endl;
		}
	}
}


/*
int main() {
	data a;

	a.addNode(1014, 1136,"dormir", "chau");
	a.addNode(514, 636,"comer", "chau");
	a.addNode(414, 536,"desayunar", "chau");
	a.addNode(914, 1036,"cenar", "chau");

	a.mostrar();
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

*/
// Control of execution of tasks
void data::actualTask( int extTime ){

	int extHour, extMin;
	unsigned int i;
	extHour = extTime / 60;
	extMin = extTime - ((extTime / 60) * 60);
	for(i = 0; i < task.size(); i++){
		if ( extTime >= task[i].start && extTime < task[i].end - 10 && task[i].flag1 == 0){ 	// Task starting?
			task[i].flag1 = 1;  										// I show the message once
			cout << "\nActual Time: "<< extHour << ":" << extMin << endl;
			cout <<"Task: " << task[i].textTask << " is starting !" << endl;
			cout << "Start time " << task[i].startHour << ":" << task[i].startMin << " ------> End time "<< task[i].endHour << ":" << task[i].endMin << endl;
		}
		// Ten minutes left to finish the task?
		if ( extTime >= ( task[i].end - 10 ) && extTime < task[i].end && task[i].flag2 == 0){
			if ( task[i].done == 0 ){
				task[i].flag2 = 1;     									// I show the message once
				cout << "\nActual Time: " << extHour << ":" << extMin << endl;
				cout << "In 10 minutes the task : " << task[i].textTask <<" will be finished" << endl;
			}
		}
		// Activity ending?
		if ( extTime >= task[i].end && extTime < task[i].end + 4 && task[i].flag3 == 0 ){
			task[i].flag3 = 1;   										// I show the message once
			cout << "\nActual Time: " << extHour << ":" << extMin << endl;
			cout <<"The task: "<< task[i].textTask <<" is finished! " << "End time :" << task[i].endHour << ":" << task[i].endMin << endl;
		}
	}

}


void data::taskStatus( int extTime ){

	int Act;
	unsigned int i;
	string text;
	Act = 0;
	for(i = 0; i < task.size(); i++){
		if (extTime >= task[i].start && extTime <= task[i].end  && Act == 0){
			cout << "Task : " << task[i].textTask << endl;  				//I look if any task is running.
			if (task[i].done){
				//Delay(3);
				cout << "Relax, you have already done it!" << endl;
			}
			else{
				//Delay(3);
				cout << "Status Undone!," << task[i].question << endl << "Y/N : ";
				cin >> text;
				if ( text == "y" || text == "Y"){
					task[i].done = 1;
					//Delay(3);
					cout << "New status done!" << endl;
				}
				if ( text == "n" || text == "N"){
					task[i].done = 0;
					//Delay(3);
					cout << "Status undone!" << endl;
				}
			}
			Act = 1; 															// Loop execution flag
		}
	}
	//Delay(3);

}

#endif /* DATA_H_ */

