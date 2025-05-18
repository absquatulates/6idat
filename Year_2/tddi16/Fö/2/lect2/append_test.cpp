#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>

using namespace std;

void insert(int n) {
	vector<int> x;

	for (int i = 0; i < n; i++)
		x.push_back(i);
}
// end CODE

void insert_list(int n) {
	list<int> x;

	for (int i = 0; i < n; i++)
		x.push_back(i);
}

template <class Fn>
void measure(Fn fn, int label, ofstream &out) {
	const int TIMES = 100000;

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++)
		fn();
	auto end = chrono::high_resolution_clock::now();

	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << endl;
}

int main() {
	ofstream a{"vector_append.txt"};
	ofstream b{"list_append.txt"};

	for (int i = 1; i <= 200; i++) {
		cout << i << endl;
		measure([i](){ insert(i); }, i, a);
		measure([i](){ insert_list(i); }, i, b);
	}

	return 0;
}
