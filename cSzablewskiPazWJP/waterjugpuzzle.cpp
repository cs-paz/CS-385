/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Christian Szablewski-Paz & Sydney Cardy
 * Date        : October 17th, 2020
 * Description : Solves the iconic water jug puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	string directions;
	State *parent;

	State(int _a, int _b, int _c, string _directions) :
			a { _a }, b { _b }, c { _c }, directions { _directions }, parent {
					nullptr } {
	}

	void remove() {
		if (this->parent != nullptr) {
			this->parent->remove();
			this->parent = nullptr;
		}
		delete this;
	}

	//deep clone to get around memory leaks
	State* deep_clone() {
		State *copy = new State(this->a, this->b, this->c, this->directions);
		if (this->parent != nullptr) {
			copy->parent = this->parent->deep_clone();
		}
		return copy;
	}
	// String representation of state in tuple form.
	string to_string() {

		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

void waterjug(int aCapacity, int bCapacity, int cCapacity, int aGoal, int bGoal,
		int cGoal) {

	int aCurr = 0;
	int bCurr = 0;
	int cCurr = cCapacity;
	const int length = aCapacity + 1;
	State ***matrix = new State**[length];
	for (int i = 0; i < length; i++) {
		matrix[i] = new State*[bCapacity + 1];
		fill(matrix[i], matrix[i] + bCapacity + 1, nullptr);
	}
	vector<State*> states;
	State *initialState = new State(aCurr, bCurr, cCurr, "Initial state. ");
	states.push_back(initialState);
	stack<State*> endStates;

	//Is the problem solved
	while (!states.empty()) {
		State *current = states.at(0);
		states.erase(states.begin());

		//a = 0, b = 0, c = 8

		if (current->a == aGoal && current->b == bGoal && current->c == cGoal) {
			endStates.push(current);
			while (current->parent != nullptr) {
				current = current->parent;
				endStates.push(current);
			}
			while (!endStates.empty()) {
				State *finalState = endStates.top();
				endStates.pop();
				cout << finalState->directions << finalState->to_string()
						<< endl;
				delete finalState;
			}
			for (int i = 0; i < length; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;
			states.clear();
			return;
		}

		if (matrix[current->a][current->b] == nullptr) {
			matrix[current->a][current->b] = current;

			ostringstream oss;
			int setA;
			int setB;
			int setC;
			//Pour from C to A
			if (current->c != 0 && current->a != aCapacity) {
				if (aCapacity >= (current->a + current->c)) {
					setA = current->a + current->c;
					setC = 0;
					setB = current->b;
				} else {
					setC = current->c - (aCapacity - current->a);
					setA = aCapacity;
					setB = current->b;
				}
				int difference = current->c - setC;
				if (difference != 1) {
					oss << "Pour " << difference << " gallons"
							<< " from C to A. ";
				} else {
					oss << "Pour " << difference << " gallon"
							<< " from C to A. ";
				}
				State *pushToQueue = new State(setA, setB, setC, oss.str());
				pushToQueue->parent = current->deep_clone();
				states.push_back(pushToQueue);
				oss.str("");
				oss.clear();
			}

			//Pour from B to A
			if (current->b != 0 && current->a != aCapacity) {
				if (aCapacity >= (current->a + current->b)) {
					setA = current->a + current->b;
					setB = 0;
					setC = current->c;
				} else {
					setB = current->b - (aCapacity - current->a);
					setA = aCapacity;
					setC = current->c;
				}
				int difference = current->b - setB;
				if (difference != 1) {
					oss << "Pour " << difference << " gallons"
							<< " from B to A. ";
				} else {
					oss << "Pour " << difference << " gallon"
							<< " from B to A. ";
				}
				State *pushToQueue = new State(setA, setB, setC, oss.str());
				pushToQueue->parent = current->deep_clone();
				states.push_back(pushToQueue);
				oss.str("");
				oss.clear();
			}

			//(0, 0, 8)
			//Pour from C to B
			if (current->c != 0 && current->b != bCapacity) {
				if (bCapacity >= (current->b + current->c)) {
					setB = current->b + current->c;
					setC = 0;
					setA = current->a;
				} else {
					setC = current->c - (bCapacity - current->b);
					setB = bCapacity;
					setA = current->a;
				}
				int difference = current->c - setC;
				if (difference != 1) {
					oss << "Pour " << difference << " gallons"
							<< " from C to B. ";
				} else {
					oss << "Pour " << difference << " gallon"
							<< " from C to B. ";
				}
				State *pushToQueue = new State(setA, setB, setC, oss.str());
				pushToQueue->parent = current->deep_clone();
				states.push_back(pushToQueue);
				oss.str("");
				oss.clear();
			}

			//Pour from A to B
			if (current->a != 0 && current->b != bCapacity) {
				if (bCapacity >= (current->b + current->a)) {
					setB = current->b + current->a;
					setA = 0;
					setC = current->c;
				} else {
					setA = current->a - (bCapacity - current->b);
					setB = bCapacity;
					setC = current->c;
				}
				int difference = current->a - setA;
				if (difference != 1) {
					oss << "Pour " << difference << " gallons"
							<< " from A to B. ";
				} else {
					oss << "Pour " << difference << " gallon"
							<< " from A to B. ";
				}
				State *pushToQueue = new State(setA, setB, setC, oss.str());
				pushToQueue->parent = current->deep_clone();
				states.push_back(pushToQueue);
				oss.str("");
				oss.clear();
			}

			//Pour from B to C
			if (current->b != 0 && current->c != cCapacity) {
				if (cCapacity >= (current->b + current->c)) {
					setC = current->b + current->c;
					setB = 0;
					setA = current->a;
				} else {
					setB = current->b - (cCapacity - current->c);
					setC = cCapacity;
					setA = current->a;
				}
				int difference = current->b - setB;
				if (difference != 1) {
					oss << "Pour " << difference << " gallons"
							<< " from B to C. ";
				} else {
					oss << "Pour " << difference << " gallon"
							<< " from B to C. ";
				}
				State *pushToQueue = new State(setA, setB, setC, oss.str());
				pushToQueue->parent = current->deep_clone();
				states.push_back(pushToQueue);
				oss.str("");
				oss.clear();
			}

			//Pour from A to C
			if (current->a != 0 && current->c != cCapacity) {
				if (cCapacity >= (current->a + current->c)) {
					setC = current->a + current->c;
					setA = 0;
					setB = current->b;
				} else {
					setA = current->a - (cCapacity - current->c);
					setC = cCapacity;
					setB = current->b;
				}
				int difference = current->a - setA;
				if (difference != 1) {
					oss << "Pour " << difference << " gallons"
							<< " from A to C. ";
				} else {
					oss << "Pour " << difference << " gallon"
							<< " from A to C. ";
				}
				State *pushToQueue = new State(setA, setB, setC, oss.str());
				pushToQueue->parent = current->deep_clone();
				states.push_back(pushToQueue);
				oss.str("");
				oss.clear();
			}
		} //force close if loop goes over 20

	}
	cout << "No solution.";
	return;
}

int main(int argc, char *argv[]) {
	if (argc != 7) {
		cerr
				<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
				<< endl;
		return 1;
	}

	istringstream iss;
	int x;
	int capacities[4] = { };
	int goals[4] = { };
	string tempNames[] = { "", "A", "B", "C" };
	for (int i = 1; i < argc; i++) {
		iss.str(argv[i]);
		if ((!(iss >> x) || x < 0)) {
			if (i < 4) {
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "
						<< tempNames[i] << "." << endl;
				return 1;
			} else {
				cerr << "Error: Invalid goal '" << argv[i] << "' for jug "
						<< tempNames[i - 3] << "." << endl;
				return 1;
			}
		}
		if (i == 3 && x <= 0) {
			cerr << "Error: Invalid capacity '" << x << "' for jug C." << endl;
			return 1;
		}
		iss.clear();
		if (i < 4) {
			capacities[i] = x;
		} else {
			goals[i - 3] = x;
		}
	}
	for (int i = 1; i < 4; i++) {
		if (capacities[i] < goals[i]) {
			cerr << "Error: Goal cannot exceed capacity of jug " << tempNames[i]
					<< "." << endl;
			return 1;
		}
		iss.clear();
	}
	if (goals[1] + goals[2] + goals[3] != capacities[3]) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return 1;
	}

	waterjug(capacities[1], capacities[2], capacities[3], goals[1], goals[2],
			goals[3]);

	return 0;
}

