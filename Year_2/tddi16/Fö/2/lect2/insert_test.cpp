#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>

using namespace std;

// Kompilera och kör med -O2

template <class Container>
void measure(int label, ofstream &out) {
	const int TIMES = 10000;

	vector<Container> data(TIMES, Container());

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++) {
		for (int j = 0; j < label; j++)
			data[i].insert(data[i].begin(), 1);
	}
	auto end = chrono::high_resolution_clock::now();

	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << endl;
}

int main() {
	ofstream a{"vector_insert.txt"};
	ofstream b{"list_insert.txt"};

	for (int i = 0; i <= 1000; i += 10) {
		cout << i << endl;
		measure<vector<int>>(i, a);
		measure<list<int>>(i, b);
	}

	return 0;
}
