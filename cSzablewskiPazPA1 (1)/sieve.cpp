/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Christian Szablewski-Paz
 * Date        : September 16th, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
	PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

//displays primes according to margins given in instructions
void PrimesSieve::display_primes() const {
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
        int primesInRow = 0;
        if(primes_per_row >= count_num_primes()){
            for(int i = 2; i <= limit_; i++){
            	if(i == 2){
            		cout << 2;
            	}
            	// " " delimeter function
                if(is_prime_[i] && i != 2){
                	cout << " " << i;
                }
            }
        }
        else{
            for(int i = 2; i <= limit_; i++){
                if(is_prime_[i]){
                    if(primesInRow == 0) {
                        cout << setw(max_prime_width) << i;
                        primesInRow++;
                    }
                    else{
                    cout << setw(max_prime_width + 1) << i;
                    primesInRow++;
                        if(primesInRow == primes_per_row) {
                        	cout << endl;
                        	primesInRow = 0;
                        }
                    }
                }
            }
        }
}

// returns number of primes leading up to limit_
int PrimesSieve::count_num_primes() const {
	int primes = 0;
	for (int i = 2; i <= limit_; i++){
		if (is_prime_[i]){
			primes++;
		}
	}
	return primes;
}

// uses sieve algorithm given to determine the prime numbers
// up to the limit inclusively
void PrimesSieve::sieve() {
	for(int i = 2; i <= limit_; i++){
		is_prime_[i] = true;
	}
	for (int i = 2; i <= sqrt(limit_); i++){
		if(is_prime_[i]){
			for (int j = i*i; j <= limit_; j += i){
				is_prime_[j] = false;
			}
		}
	}

	// find max prime
	// loops backwards in is_prime_ to find first prime number
	int count = limit_;
	while(!is_prime_[count]){
		count--;
	}
	max_prime_ = count;
	num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
	int count = 0;
	while(num != 0){
		num = num /10;
		count++;
	}
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // cout statements for linux command line tests
    PrimesSieve test = PrimesSieve(limit);
    cout << endl;
    cout << "Number of primes found: " << test.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    test.display_primes();

    return 0;
}
