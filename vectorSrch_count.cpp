

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <random>

using namespace std;

template <class genType>
struct gTypeFunctions {
	static int vecSrch(vector<genType> tmpVec, genType srch) {
		/*
		auto it = find(tmpVec.begin(), tmpVec.end(), srch);
		if (it != tmpVec.end()) {
		return *it;
		}
		else
		return -1;
		*/
		ptrdiff_t pos = distance(tmpVec.begin(), find(tmpVec.begin(), tmpVec.end(), srch));
		if (pos >= tmpVec.size()) {
			return -1;
		}
		else
			return pos;
	}

	static int countOccVec(vector<genType> tmpVec, genType srch, int beginIndex) {
		bool flag = true;
		int counter = 0;

		vector<int>::iterator it = tmpVec.begin() + beginIndex;
		while (flag) {
			if (tmpVec.at(beginIndex) == srch && it != tmpVec.end()) {
				counter++;
				beginIndex++;
				it++;
			}
			else
				flag = false;
		}
		return counter;
	}
};


int main() {
	srand(time(NULL));

	vector<int> mainVec;
	int srchedVal = 0;
	int result = 0;
	int mainCounter = 0;

	for (int i = 0; i <= 10; i++) {
		mainVec.push_back(rand() % 10 + 1);
	}
	sort(mainVec.begin(), mainVec.end());

	cout << "Vector values: " << endl;
	for (int j = 0; j < mainVec.size(); j++) {
		cout << mainVec.at(j) << " ";
	}

	cout << endl;

	cout << "Enter value to search for: ";
	cin >> srchedVal;

	result = gTypeFunctions<int>::vecSrch(mainVec, srchedVal);

	mainCounter = gTypeFunctions<int>::countOccVec(mainVec, srchedVal, result);
	cout << "Index of first occ: " << result << endl;
	cout << "Counter: " << mainCounter << endl;
	/*
	if (result == -1) {
	cout << "Val not found." << endl;
	}
	else
	cout << "First occurence of: " << srchedVal << " in vector, at positions: " << result << endl;
	*/
	return 0;
}
