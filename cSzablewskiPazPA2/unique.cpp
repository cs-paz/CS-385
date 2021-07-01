/*******************************************************************************
 * Name        : unique.cpp
 * Author      : 
 * Date        : 
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      :
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(const auto &e: s){
    	if(!islower(e)) {
    		return false;
    	}
    }
    return true;
}

bool all_unique_letters(const string &s) {
	int storage = 0;
	for(const auto &e: s){
		if(((storage & (1 << e)) >> e) % 2 == 1 ){
			return false;
		}
	    else {
			storage = storage | (1 << e);
		}
	}

	return true;
}

int main(int argc, char * const argv[]) {
    if(argc != 2){
    	cerr << "Usage: " << argv[0] << " <string>" << endl;
    	return 1;
    }
    if(!is_all_lowercase(argv[1])){
    	cerr << "Error: String must contain only lowercase letters." << endl;
    	return 1;
    }
    if(all_unique_letters(argv[1])){
    	cout << "All letters are unique.";
    }
    else {
    	cout << "Duplicate letters found.";
    }


}
