/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Christian Szablewski-Paz
 * Date        : October 2nd, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor Code.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
	vector<vector<int>> ways;
	if (num_stairs <= 0) {
	   ways.push_back(vector<int>());
	}
	else {
		for(int i = 1; i < 4; i++) {
			if(num_stairs >= i) {
				vector<vector<int>> result = get_ways(num_stairs - i);
				for(size_t j = 0; j < result.size(); j++){
					result.at(j).push_back(i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
	for(size_t i = 0; i < ways.size(); i++){
		if(ways.size() > 9){
			cout << setw(2);
		}
		cout << (i + 1) << ". " << "[";
		for (int j = ways.at(i).size() - 1; j >= 0; j--){
			if(j != 0) {
				cout << ways.at(i).at(j) << ", ";
			}
			else {
				cout << ways.at(i).at(j);
			}
		}
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	if (argc !=2) {
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	istringstream iss(argv[1]);
	int num;
	if (!(iss >> num) || num < 0) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	iss.clear();
	if (get_ways(num).size() == 1) {
		cout << "1 way to climb 1 stair." << endl;
	}
	else {
		cout << get_ways(num).size() << " ways to climb " << num << " stairs." << endl;
	}
	display_ways(get_ways(num));
	return 0;
}
