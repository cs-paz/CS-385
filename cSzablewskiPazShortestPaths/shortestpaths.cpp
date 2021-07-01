/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Christian Szablewski-Paz Partner Zac Schuh
 * Date        : 12/7/20
 * Description : Using floyd's algorithm, finds the shortest path between all pairs as read in from a given text file.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

string char_to_string(char c){

    string temp(1, c);
    return temp;

}

long int num_digits(long int temp_num){

    string digits = to_string(temp_num);
    return digits.size();

}

vector<vector<char>> pair_comparison(vector<vector<long int>> v1, vector<vector<long int>> v2, vector<char> vX){
	long int minimum;
    vector<vector<char>> v3;
    for(size_t i = 0; i < v2.size(); i++){

            v3.push_back({});
            for(size_t j = 0; j < v2[i].size(); j++){

                v3[i].push_back('-');

            }
    }

    for(size_t i = 0; i < v2.size(); i++){

        for(size_t j = 0; j < v2.size(); j++){

            for(size_t k = 0; k < v2[j].size(); k++){

                if(!(v2[j][i] + v2[i][k] < 0 || v2[j][i] == 999999999999999999 || v2[i][k] == 999999999999999999)){

                    minimum = min(v2[j][i]+v2[i][k], v2[j][k]);
                    v2[j][k] = minimum;

                }
            }
        }
        for(size_t j = 0; j < v2.size(); j++){

            for(size_t k = 0; k < v2[i].size(); k++){

                if(v1[j][k] != v2[j][k]){

                    v3[j][k] = vX[i];

                }
            }
        }
        v1 = v2;
    }
    return v3;

}

string path(long int index1, long int index2, vector<vector<char>> intermediate_vertex, map<char, long int> pairs){

	string path_output = "";

    if(intermediate_vertex[index1][index2] == '-'){

        return path_output;

    }
    if(intermediate_vertex[index1][pairs[intermediate_vertex[index1][index2]]] != '-'){

        path_output += path(index1, pairs[intermediate_vertex[index1][index2]], intermediate_vertex, pairs);

    }

    path_output += " -> " + char_to_string(intermediate_vertex[index1][index2]);

    if(intermediate_vertex[pairs[intermediate_vertex[index1][index2]]][index2] != '-'){

        path_output += path(pairs[intermediate_vertex[index1][index2]],index2, intermediate_vertex, pairs);

    }
    return path_output;
}

vector<vector<long int>> floyds_algorithm(vector<vector<long int>> temp_vec){
	long int minimum;

    for(size_t i = 0; i < temp_vec.size(); i++){

        for(size_t j = 0; j < temp_vec.size(); j++){

            for(size_t k = 0; k < temp_vec[i].size(); k++){

                if(!(temp_vec[j][i] == 999999999999999999 || temp_vec[i][k] == 999999999999999999 || temp_vec[j][i] + temp_vec[i][k] < 0)){
                	minimum = min(temp_vec[j][k], temp_vec[j][i]+temp_vec[i][k]);
                    temp_vec[j][k] = minimum;
                }
            }
        }
    }

    return temp_vec;

}

int main(int argc, char * const argv[]){

    long int line, weight, spaces;
    string currentLine;
    string spacer = "  ";

	if(argc != 2){

	        cerr << "Usage: ./shortestpaths <filename>" << endl;
	        return 1;

	}
	ifstream file;
	file.open(argv[1]);
	if(file.fail()){

	    cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
	    return 1;

	}

	vector<char> letters = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
	    		'P','Q','R','S','T','U','V','W','X','Y','Z'};

	map<string, long int> pairs_s = {{"A",0},{"B",1},{"C",2},{"D",3},{"E",4},{"F",5},{"G",6},{"H",7},{"I",8},
			{"J",9},{"K",10},{"L",11},{"M",12},{"N",13},{"O",14},{"P",15},{"Q",16},{"R",17},{"S",18},{"T",19},
			{"U",20},{"V",21},{"W",22},{"X",23},{"Y",24},{"Z",25}};

    map<char, long int> pairs = {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},{'F',5},{'G',6},{'H',7},{'I',8},
    		{'J',9},{'K',10},{'L',11},{'M',12},{'N',13},{'O',14},{'P',15},{'Q',16},{'R',17},{'S',18},{'T',19},
			{'U',20},{'V',21},{'W',22},{'X',23},{'Y',24},{'Z',25}};

    vector<vector<long int>> inp;

    getline(file, currentLine);

    istringstream iss;
    iss.str(currentLine);
    iss >> line;

    if(line < 1 || line > 26){

        cerr << "Error: Invalid number of vertices '"<< currentLine << "' on line 1." << endl;
        return 1;

    }

    for(long int i = 0; i < line; i++){
        inp.push_back({});
        for(long int j = 0; j < line; j++){

            if(i == j){

                inp[i].push_back(0);

            }
            else{

                inp[i].push_back(999999999999999999);

            }
        }
    }
    long int count = 1;

    string starting_vertex, ending_vertex, edge_weight;

    while(getline(file, currentLine)){
        count++;
        iss.clear();
        spaces = 0;
        starting_vertex = "";
        ending_vertex = "";
        edge_weight = "";
        for(size_t i = 0; i < currentLine.size(); i++){
            if(currentLine[i] == ' '){

                spaces++;

            }
            else if(spaces == 0){

                starting_vertex+=currentLine[i];

            }
            else if(spaces == 1){

                ending_vertex+=currentLine[i];

            }
            else{

                edge_weight+=currentLine[i];

            }
        }
        if(starting_vertex.length() > 1 || (pairs[starting_vertex[0]] == 0 && starting_vertex[0] != 'A') || pairs[starting_vertex[0]] > line - 1){

            cerr << "Error: Starting vertex '" << starting_vertex << "' on line " << count << " is not among valid values " << letters[0] << "-" << letters[line - 1] << "." << endl;
            return 1;

        }
        if(ending_vertex.length() > 1 || (pairs[ending_vertex[0]] == 0 && ending_vertex[0] != 'A') || pairs[ending_vertex[0]] > line - 1){

            cerr << "Error: Ending vertex '" << ending_vertex << "' on line " << count << " is not among valid values " << letters[0] << "-" << letters[line - 1] << "." << endl;
            return 1;

        }
        if(edge_weight == ""){

            cerr << "Error: Invalid edge data '" << currentLine << "' on line " << count << "." << endl;
            return 1;

        }
        iss.str(edge_weight);
        iss >> weight;
        if(weight <= 0){

            cerr << "Error: Invalid edge weight '" << edge_weight << "' " << "on line " << count << "." << endl;
            return 1;

        }
        inp[pairs[currentLine[0]]][pairs[currentLine[2]]] = weight;
        weight = 0;
    }
    long int max_digit = 1;

    for (size_t i = 0; i < inp.size(); i++){

        for(size_t j = 0; j < inp[i].size(); j++){

            if(inp[i][j] != 999999999999999999 && num_digits(inp[i][j]) > max_digit){

                max_digit = num_digits(inp[i][j]);

            }
        }
    }
    cout << "Distance matrix:" << endl;
    cout << spacer;
    for(size_t i = 0; i < inp.size(); i++){
        for(long int j = 0; j < max_digit - 1; j++){
                    cout << " ";
                }
        if(i == inp.size() - 1){

            cout << letters[i];

        }
        else{

            cout << letters[i] << " ";

        }
    }
    cout << endl;
    for(size_t i = 0; i < inp.size(); i++){
        cout << letters[i] << " ";
        for(size_t j = 0; j < inp[i].size(); j++){

            if(inp[i][j] == 999999999999999999 && 1 < max_digit){

                for(long int k = 0; k < max_digit - 1; k++){
                    cout << " ";

                }
            }
            else if(num_digits(inp[i][j]) < max_digit){
                for(long int k = 0; k < max_digit-num_digits(inp[i][j]); k++){
                    cout << " ";
                }
            }
            if(inp[i][j] == 999999999999999999 && j == inp[i].size() - 1){

                cout << "-";

            }
            else if(inp[i][j] == 999999999999999999){

                cout << "-" << " ";

            }
            else if(j == inp[i].size() - 1){

                cout << inp[i][j];

            }
            else{

                cout << inp[i][j] << " ";

            }
        }
        cout << endl;
    }

    vector<vector<long int>> txt = floyds_algorithm(inp);
    max_digit = 1;

    for (size_t i = 0; i < txt.size(); i++){

        for(size_t j = 0; j < txt[i].size(); j++){

            if(txt[i][j] != 999999999999999999 && num_digits(txt[i][j]) > max_digit){

                max_digit = num_digits(txt[i][j]);

            }
        }
    }

    cout << endl << "Path lengths:" << endl;
    cout << spacer;
    for(size_t i = 0; i < inp.size(); i++){
        for(long int j = 0; j < max_digit - 1; j++){
                    cout << " ";
        }
        if(i == inp.size() - 1){

            cout << letters[i];

        }
        else{

            cout << letters[i] << " ";

        }
    }
    cout << endl;

    for(size_t i = 0; i < txt.size(); i++){
        cout << letters[i] << " ";
        for(size_t j = 0; j < txt[i].size(); j++){

            if(txt[i][j] == 999999999999999999 && 1 < max_digit){

                for(long int k = 0; k < max_digit - 1; k++){
                    cout << " ";

                }
            }
            else if(num_digits(txt[i][j]) < max_digit){

                for(long int k = 0; k < max_digit-num_digits(txt[i][j]); k++){
                    cout << " ";

                }
            }
            if(txt[i][j] == 999999999999999999 && j == txt[i].size() - 1){

                cout << "-";

            }
            else if(txt[i][j] == 999999999999999999){

                cout << "-" << " ";

            }
            else if(j == txt[i].size() - 1){

                cout << txt[i][j];

            }
            else{

                cout << txt[i][j] << " ";

            }
        }
        cout << endl;
    }
    vector<vector<char>> intermediate_vertex = pair_comparison(inp, inp, letters);

    cout << endl << "Intermediate vertices:" << endl;

    cout << spacer;
    for(size_t i = 0; i < inp.size(); i++){
        if(i == inp.size() - 1){

            cout << letters[i];

        }
        else{

            cout << letters[i] << " ";

        }
    }
    cout << endl;

    for(size_t i = 0; i < intermediate_vertex.size(); i++){

        cout << letters[i] << " ";

        for(size_t j = 0; j < intermediate_vertex[i].size(); j++){

            if(j == intermediate_vertex[i].size() - 1){

                cout << intermediate_vertex[i][j];

            }
            else{

                cout << intermediate_vertex[i][j] << " ";

            }
        }
        cout << endl;
    }
    cout << endl;
    string temp_path;

    for(size_t i = 0; i < intermediate_vertex.size(); i++){

        for(size_t j = 0; j < intermediate_vertex[i].size(); j++){

            if(txt[i][j] == 999999999999999999){

                cout<< letters[i] << " -> " << letters[j] << ", distance: infinity, path: none" << endl;

            }
            else{

                cout<< letters[i] << " -> " << letters[j] << ", distance: " << txt[i][j] << ", path: " << letters[i];
                temp_path = path(i, j, intermediate_vertex, pairs);
                cout << temp_path;
                if(letters[i] != letters[j]){

                    cout << " -> " << letters[j];

                }
                if(i < intermediate_vertex.size() - 1 || j < intermediate_vertex[i].size() - 1){

                    cout << endl;

                }
            }
        }
    }
}
