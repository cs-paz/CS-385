/*******************************************************************************
 * Name    : inversioncounter.cpp
 * Author  : Christian Szablewski-Paz & Zac Schuh
 * Version : 1.0
 * Date    : October 28, 2020
 * Description : Counts the number of inversions in a given sequence of ints.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long int count = 0;
	for(int i = 0; i < length; i++){
		for(int j = i + 1; j < length; j++){
			if(array[i] > array[j]){
				count++;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	int *scratch = new int[length];
	long totalInversions = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return totalInversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
   long count = 0L;
   if(low < high){
	   int mid = low + (high - low) / 2;
	   int L = low;
	   int H = mid + 1;
	   count += mergesort(array, scratch, low, mid) + mergesort(array, scratch, mid + 1, high);
	   for(int i = low; i <= high; i++){
		   if(L <= mid && (H > high || array[L] <= array[H])) {
			   scratch[i] = array[L];
			   L++;
		   }
		   else {
			   count += mid - L + 1;
			   scratch[i] = array[H];
			   H++;
		   }
	   }
	   for(int i = low; i <= high; i++) {
		   array[i] = scratch[i];
	   }
   }
   return count;
}

int main(int argc, char *argv[]) {
	// TODO: parse command-line argument
	istringstream iss;
	int value, index = 0;
	vector<int> values;
	string str;
	str.reserve(11);
	char c;
	string isSlow; //string value used for boolean expressions

	if(argc > 2){
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
	if(argc == 2){
		iss.str(argv[1]);
		iss >> isSlow;
		iss.clear();
		if(isSlow != "" && isSlow != "slow"){
			cerr << "Error: Unrecognized option '" << isSlow << "'." << endl;
			return 1;
		}
	}

	cout << "Enter sequence of integers, each followed by a space: " << flush;

	while (true) {
		c = getchar();
		const bool eoln = c == '\r' || c == '\n';
		if (isspace(c) || eoln) {
			if (str.length() > 0) {
				iss.str(str);
				if (iss >> value) {
					values.push_back(value);
				} else {
					cerr << "Error: Non-integer value '" << str
						 << "' received at index " << index << "." << endl;
					return 1;
				}
				iss.clear();
				++index;
			}
			if (eoln) {
				break;
			}
			str.clear();
		} else {
			str += c;
		}
	}
	if(values.size() == 0) {
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	if(isSlow == "slow") {
		cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
	}
	else {
		cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
	}
	return 0;
}
