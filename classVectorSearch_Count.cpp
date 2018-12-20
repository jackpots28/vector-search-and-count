
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

/***********************/
/****** class def ******/
/***********************/

template <class T>
class countSrch {
public:
	countSrch(T val) {
		for (T i = val; i <= 1000; i++) {
			tmpVec.push_back(rand() % 100 + 1);
		}
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
		sort(tmpVec.begin(), tmpVec.end());
	}

	int vecSrch() {
		pos = distance(tmpVec.begin(), find(tmpVec.begin(), tmpVec.end(), srch));
		if (pos >= tmpVec.size()) {
			return -1;
		}
		else
			return pos;
	}

	int countOcc() {
		counter = count(tmpVec.begin(), tmpVec.end(), srch);
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

	/* test methods for checking certain values */
	/*
	void getVecSize() {
		cout << "tmpVec size: " << tmpVec.size() << endl << endl;
	}

	void getIt() {
		cout << "tmpIt: " << *tmpIt << endl;
		cout << "it: " << *it << endl << endl;
	}
	void getPos() {
		cout << "tmpPos: " << tmpPos << endl;
		cout << "pos: " << pos << endl;
	}
	*/

private:
	ptrdiff_t tmpPos;
	ptrdiff_t pos;

	vector<int>::iterator it;
	vector<int>::iterator tmpIt;

	vector<T>tmpVec;

	T srch;
	int counter;
};




/********************/
/****** main() ******/
/********************/

int main() {
	srand(time(NULL));

	int srchVal = 0;
	int result = 0;
	int count = 0;

	int startInt = 0;
	char startChar = 'a';

	countSrch<int> obj(startInt);

	//obj.sortTmpVec();
	obj.prntVec();
	
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
	

	/*
	cout << endl << endl;
	obj.getVecSize();
	obj.getIt();
	obj.getPos();
	cout << endl;
	*/

    return 0;
}

