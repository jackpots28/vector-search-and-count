
#include "stdafx.h"
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

const size_t testSize = 20'500'000;

template <class T>
class countSrch {
public:

	countSrch() {
		tmpVec.resize(testSize);
		for (auto& d : tmpVec) {
			d = (rand() % 1000000);
		}
	}

	void setSrch(double tmpSrch) {
		srch = tmpSrch;
	}
	
	void prntVec() {
		for (int j = 0; j < tmpVec.size(); j++) {
			cout << tmpVec.at(j) << " ";
		}
		cout << endl;
	}

	void sortTmpVec() {
		const auto start = high_resolution_clock::now();
		sort(par_unseq, tmpVec.begin(), tmpVec.end());
		const auto end = high_resolution_clock::now();

		printf("Duration: %fms\n", duration_cast<duration<double, milli>>(end - start).count());
	}

	void sortTmpVecWOpar() {
		const auto start = high_resolution_clock::now();
		sort(tmpVec.begin(), tmpVec.end());
		const auto end = high_resolution_clock::now();

		printf("Duration with out parallelism: %fms\n", duration_cast<duration<double, milli>>(end - start).count());
	}

	int vecSrch() {
		pos = distance(tmpVec.begin(), find(par_unseq, tmpVec.begin(), tmpVec.end(), srch));
		if (pos >= tmpVec.size()) {
			return -1;
		}
		else
			return pos;
	}

	int countOcc() {
		counter = count(par_unseq, tmpVec.begin(), tmpVec.end(), srch);
		return counter;
		/*
		bool flag = true;
		tmpPos = pos;
		counter = 0;
		it = tmpVec.begin() + pos;
		tmpIt = it;
		while (flag) {
			if (tmpVec.at(pos) == srch && tmpVec.at(pos) < tmpVec.size() + 1) {
				counter++;
				pos++;
				//tmpPos++;
				it++;
			}
			else
				flag = false;
		}
		return counter;
		*/
	}


private:
	ptrdiff_t tmpPos;
	ptrdiff_t pos;

	vector<int>::iterator it;
	vector<int>::iterator tmpIt;

	vector<T>tmpVec;

	T srch;
	int counter;
};


int main() {
	//srand(time(NULL));

	double srchVal = 0;
	double result = 0;
	int count = 0;

	countSrch<double> obj;
	countSrch<double> obj2;
	
	// obj.prntVec();
	
	cout << "Enter a value to search: ";
	cin >> srchVal;
	

	cout << endl;
	obj.setSrch(srchVal);
	result = obj.vecSrch();
	count = obj.countOcc();
	if (result == -1) {
		cout << "Value not found." << endl;
	}
	else {
		cout << "First occurence of value: " << srchVal << " found at index: " << result << endl;
		cout << "value was found: " << count << " time(s)." << endl << endl;
	}

	obj.sortTmpVec();
	obj2.sortTmpVecWOpar();

    return 0;
}

