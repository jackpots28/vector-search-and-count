
#include "stdafx.h"
#include <memory>
#include <iostream>
#include <chrono>
#include <ratio>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include <execution>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;
using std::execution::par_unseq;
using namespace std;

const size_t testSize = 3'000'000;

template <class T>
class countSrch {
public:

	countSrch() {
		cout << "Object created." << endl;
		tmpVec.resize(testSize);
		for (auto& d : tmpVec) {
			d = (rand() % 10000);
		}
	}

	~countSrch() {
		cout << "Object destroyed." << endl;
	}

	void setSrch(T tmpSrch) {
		srch = tmpSrch;
	}
	
	void prntVec() {
		for (int j = 0; j < tmpVec.size(); j++) {
			cout << tmpVec.at(j) << " ";
		}
		cout << endl;
	}

	void sortTmpVec() {
		cout << "Sorting vector using parallelism." << endl;
		const auto start = high_resolution_clock::now();
		sort(par_unseq, tmpVec.begin(), tmpVec.end());
		const auto end = high_resolution_clock::now();
		printf("Duration: %fms\n", duration_cast<duration<double, milli>>(end - start).count());
	}

	void sortTmpVecWOpar() {
		cout << "Sorting vector without using parallelism." << endl;
		const auto start = high_resolution_clock::now();
		sort(tmpVec.begin(), tmpVec.end());
		const auto end = high_resolution_clock::now();
		printf("Duration with out parallelism: %fms\n", duration_cast<duration<double, milli>>(end - start).count());

		cout << endl;
	}

	
	void refVecSrchAndCount(T& returnPos, T& counterRef) {
		pos = distance(tmpVec.begin(), find(par_unseq, tmpVec.begin(), tmpVec.end(), srch));
		if (pos >= tmpVec.size()) {
			returnPos -1;
		}
		else
			returnPos = pos;

		counterRef = count(par_unseq, tmpVec.begin(), tmpVec.end(), srch);
	}

private:
	ptrdiff_t tmpPos;
	ptrdiff_t pos;

	vector<T>tmpVec;

	T srch;
};


int main() {
	srand(time(NULL));

	vector<double> testNumbers;
	for (int i = 0; i <= 5; i++) {
		testNumbers.push_back(rand() % 10000);
	}

	double result = 0;
	double counterMain = 0;

	cout << endl;

	unique_ptr<countSrch<double>> obj(new countSrch<double>());
	unique_ptr<countSrch<char>> obj2(new countSrch<char>());
	
	cout << endl;

	for (int j = 0; j < testNumbers.size(); j++) {
		obj->setSrch(testNumbers.at(j));
		obj->refVecSrchAndCount(result, counterMain);
		if (result == -1) {
			cout << "Value not found." << endl;
		}
		else {
			cout << "First occurence of value: " << testNumbers.at(j) << " found at index: " << result << endl;
			cout << "value was found: " << counterMain << " time(s)." << endl << endl;
		}
	}

	obj->sortTmpVec();
	obj2->sortTmpVecWOpar();

    return 0;
}

