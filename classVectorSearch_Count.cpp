
#include "stdafx.h"
#include <thread>
#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

#include <future>
#include <chrono>

using namespace std;

/***********************/
/****** class def ******/
/***********************/

//template <class T>
class countSrch {
public:
	countSrch(int val) {
		for (int i = val; i <= 1000; i++) {
			tmpVec.push_back(rand() % 100 + 1);
		}
	}

	void runMultiThread(int &runResult);
	
	void prntVec() {
		for (int j = 0; j < tmpVec.size(); j++) {
			cout << tmpVec.at(j) << " ";
		}
		cout << endl;
	}

	void sortTmpVec() {
		sort(tmpVec.begin(), tmpVec.end());
	}

	void setSrch(int val) {
		srchVal = val;
	}


	int vecSrch(int &srchResult) {
		pos = distance(tmpVec.begin(), find(tmpVec.begin(), tmpVec.end(), srchVal));
		if (pos >= tmpVec.size()) {
			return srchResult = -1;
		}
		else
			return srchResult = pos;
			
	}

	int countOcc(int &countRef) {
		counter = count(tmpVec.begin(), tmpVec.end(), srchVal);
		return countRef = counter;
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

	vector<int>tmpVec;

	int counter;

	int resultFromClass;
	int srchVal;
};

void countSrch::runMultiThread(int &runResult) {
	thread t1(&countSrch::vecSrch, this, runResult);
	//thread t2(&countSrch::countOcc, this, runCount);
	t1.join();
	//t2.join();
}


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

	countSrch obj(startInt);

	//obj.sortTmpVec();
	obj.prntVec();
	
	cout << "Enter a value to search: ";
	cin >> srchVal;

	cout << endl;

	/*
	obj.vecSrch(srchVal);
	obj.getResult(result);
	count = obj.countOcc(srchVal);
	*/

	obj.setSrch(srchVal);
	obj.runMultiThread(result);

	
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

