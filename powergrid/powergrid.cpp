/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : Christian Szablewski-Paz
 * Date        : December 18th, 2020
 * Description : Prims Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <bits/stdc++.h>
#include <algorithm>
#include <typeinfo>
#include <cstring>
#include <array>
using namespace std;
//-----------------------------
bool hasLetters(string x) {
	for(size_t i = 0; i < x.size(); i++) {
		if(isalpha(x[i])) {
			return true;
		}
	}
	return false;
}

bool hasNegativeSign(string x) {
	if(x.size() > 0) {
		return x.at(0) == '-';
	}
	return false;
}

bool stringIsUnnaceptable(string x) {
	return hasLetters(x) || hasNegativeSign(x);
}
//--------------------------------
class Street { //class representation of a street
	public:
		Street(int v1, int v2, int w, string n):
			vertex1{v1}, vertex2{v2}, weight{w}, name{n} {} // @suppress("Symbol is not resolved")
		int getVertex1() {
			return vertex1;
		}
		int getVertex2() {
			return vertex2;
		}
		int getWeight() {
			return weight;
		}
		string getName() {
			return name;
		}
	private:
		int vertex1, vertex2, weight;
		string name;
};

class StreetToPrint {
	public:
		StreetToPrint(string n, int w):
			name{n}, weight{w} {} // @suppress("Symbol is not resolved")
			string getName() {
				return name;
			}
			int getWeight() {
				return weight;
			}
	private:
		string name;
		int weight;
};

string streetName(vector<Street> x, int weight){
	for(size_t i = 0; i < x.size(); i++){
		if(x.at(i).getWeight() == weight){
			return x.at(i).getName();
		}
	}
	return "";
}
//-----------------------------------
int main(int argc, char * const argv[]) {
	string numVerticesString, vertex1String = "", vertex2String = "",
			weightString = "", name = "";
	int numVertices, vertex1, vertex2, weight;

	vector<Street> streets;

	if(argc != 2) {
	        cerr << "Usage: ./powergrid <input file>" << endl;
	        return 1;
	}

	ifstream file;
	file.open(argv[1]);
	if(file.fail()) {
	    cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
	    return 1;
	}

	file.exceptions(ifstream::badbit);
	long int commas = 0, lineNumber = 0;
	string currentLine;

	getline(file, currentLine);
	stringstream ss;
	ss.str(currentLine);
	lineNumber++;

	if(!(ss >> numVertices) || numVertices < 1 || numVertices > 1000) { //check for valid # of vertices
		cerr << "Error: Invalid number of vertices '"<< currentLine << "' on line 1." << endl;
		return 1;
	}
	else{
		for(size_t i = 0; i < currentLine.size(); i++) {
			numVerticesString += currentLine.substr(i, 1);
		}
	}

	while(getline(file, currentLine)) {
		lineNumber++;
		if(currentLine == "") {
			cerr << "Error: Invalid edge data \"\" on line " << lineNumber << ".";
			return 1;
		}
		for(size_t i = 0; i < currentLine.size(); i++) {
			if(i == 0) { //make sure theres 3 commas which means 4 components
				for(size_t j = 0; j < currentLine.size(); j++) {
					if(currentLine[j] == ',') {
						commas++;
					}
				}
				if(commas != 3) {
					cerr << "Error: Invalid edge data '" << currentLine << "' on line " << lineNumber << ".";
					return 1;
				}
				commas = 0;
			}
			if(currentLine[i] == ',') {
				commas++;
			}
			else if(commas == 0) {
				vertex1String += currentLine.substr(i, 1);
			}
			else if(commas == 1) {
				vertex2String += currentLine.substr(i, 1);
			}
			else if(commas == 2) {
				weightString += currentLine.substr(i, 1);
			}
			else if(commas == 3) {
				name += currentLine.substr(i, 1);
			}

			if(commas == 1) {
				ss.clear();
				ss.str(vertex1String);
				if(!(ss >> vertex1) || vertex1 > numVertices ||
					vertex1 < 1 || stringIsUnnaceptable(vertex1String)) {
					cerr << "Error: Starting vertex '" << vertex1String << "' on line " << lineNumber
						 << " is not among valid values 1-" << numVerticesString << ".";
					return 1;
				}
			}
			if(commas == 2) {
				ss.clear();
				ss.str(vertex2String);
				if(!(ss >> vertex2) || vertex2 > numVertices ||
					vertex2 < 1 || stringIsUnnaceptable(vertex2String)) {
					cerr << "Error: Ending vertex '" << vertex2String << "' on line " << lineNumber
							<< " is not among valid values 1-" << numVerticesString << ".";
					return 1;
				}
			}
			if(commas == 3) {
				ss.clear();
				ss.str(weightString);
				if(!(ss >> weight) || weight < 1
					|| stringIsUnnaceptable(weightString)) {
					cerr << "Error: Invalid edge weight '" << weightString << "' on line " << lineNumber << ".";
					return 1;
				}
			}

		}
		streets.push_back(Street(vertex1, vertex2, weight, name));
		commas = 0;
		vertex1String = "";
		vertex2String = "";
		weightString = "";
		name = "";
	}

	if(lineNumber <= 2) {
		cout << "No solution.";
		return 0;
	}

	//-----------------------------------------------
	vector<vector<int>> town;  //adjacency matrix
	for(int i = 0; i < numVertices; i++) {
		town.push_back(vector<int>());
		for(int j = 0; j < numVertices; j++) {
			town.at(i).push_back(0);
		}
	} //fill town with 0's to begin

	for(size_t i = 0; i < streets.size(); i++) { //build adjacency matrix
		town.at(streets.at(i).getVertex1() - 1).at(streets.at(i).getVertex2() - 1) = streets.at(i).getWeight();
		town.at(streets.at(i).getVertex2() - 1).at(streets.at(i).getVertex1() - 1) = streets.at(i).getWeight();
	}

	/*for(size_t i = 0; i < town.size(); i++) {
		for(size_t j = 0; j < town.at(0).size(); j++) {
			cout << "[" << town.at(i).at(j) << "]";
		}
		cout << endl;
	}*/
	//------------------------------------------------


	vector<int> mst;
	vector<int> min_values;
	vector<bool> rep;
	for(int i = 0; i < numVertices; i++) {
		if(i == 0){
			mst.push_back(-1);  //root
			min_values.push_back(0);
			rep.push_back(false);
		}
		mst.push_back(-1);
		min_values.push_back(0);
		rep.push_back(false);
	}

	long int min = LONG_MAX; //used to see if min doesn't get initialized
	int minIndex;
	for(int i = 0; i < numVertices - 1; i++){
		for (int j = 0; j < numVertices; j++)  {
			if (rep.at(j) == false && min_values.at(j) < min){
				min = min_values.at(j);
				minIndex = j;
			}
		}

		if(min != LONG_MAX){
			rep.at(minIndex) = true;
		}
		else{
			cout << "No Solution.";
			return 0;
		}

		for (int j = 0; j < numVertices; j++)  {
			if(town[minIndex][j] != 0 && rep[j] ==  false && town[minIndex][j] < min_values[j]){
				mst[j] = min;
				min_values[j] = town[min][j];
			}
		}
	}
	int totalLength = 0;
	for(int i = 1; i < numVertices; i++){
		totalLength += town[i][min_values[i]];
	}

	vector<StreetToPrint> sortedStreets;
	ss.clear();
	for (int i = 1; i < numVertices; i++) {  //take streets in with their values
		sortedStreets.push_back(StreetToPrint(streetName(streets, town[i][min_values[i]]), town[i][min_values[i]]));
	}

	for(size_t i = 0; i < sortedStreets.size(); i++){ //sort it alphabetically
		for(size_t j = 1; j < sortedStreets.size() - i; j++){
			if(sortedStreets.at(j - 1).getName().compare(sortedStreets.at(j).getName()) > 0){
				StreetToPrint temp = sortedStreets.at(j - 1);
				sortedStreets.at(j - 1) = sortedStreets.at(j);
				sortedStreets.at(j) = temp;
			}
		}
	}

	cout << "Total wire length (meters): " << totalLength << endl;
	for(size_t i = 0; i < sortedStreets.size(); i++){
		cout << sortedStreets.at(i).getName() << " [" << sortedStreets.at(i).getWeight() << "]" << endl;
	}

}



