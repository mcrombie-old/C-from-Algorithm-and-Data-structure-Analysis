// Problem Generator for SGDE Session 3
// Problem chosen: Knapsack Problem
​
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;
​
​
int main(){
	int N, lastWt, lastV, wt,v, capacity;
	int sumWeight = 0;

	cout << "What is N?\n";		//Asks for N cases
	cin >> N;
​
	srand(time(NULL));		//Randomises based on time seed
	multimap<int, int> listOfPoints;	//maps val to weight
​
	for(int i = 0; i < N; i++){
		wt = rand() % 20 + 1;	//Weight ranges from 1 to 21 kg
		v = rand() % 20 + 1;	//Value ranges from $1 to $11
		lastV = v;		//Stores previous values
		lastWt = wt;

		while(listOfPoints.find(v)-> second == wt && lastV != v && lastV != wt){	//randomise
			wt = rand()%20 + 1;
			v = rand()%20 + 1;
			lastV = v;
			lastWt = wt;
		}
		sumWeight += wt;
		//Finalised values, add data point.
		listOfPoints.insert(pair<int,int>(wt, v));
	}

	//prints out all key-value pairs
	/*
	for(map<int, int >::const_iterator it = listOfPoints.begin();
    		it != listOfPoints.end(); ++it){
    		cout << it->first << " " << it->second << "\n";
	}*/


	//Calculates capacity randomly
	capacity = sumWeight/4*3 + rand()%20 - 10;
	//cout << "Capacity is: " << capacity << endl;
​
​
	//Writes values to file
	ofstream outputFile;
	outputFile.open("testcases.txt");
	outputFile << capacity << "\n" << N << "\n";
	for(map<int, int >::const_iterator it = listOfPoints.begin();
    		it != listOfPoints.end(); ++it){
    		outputFile << it->first << " " << it->second << "\n";
	}
	outputFile.close();
}
