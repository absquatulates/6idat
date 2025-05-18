#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>

using namespace std;

// Kompilera och kör med -O2

template <class Container>
void measure(int label, ofstream &out) {
	const int TIMES = 100000;

	Container c(label, 1);

	int sum = 0;
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++) {
		for (auto &&x : c) {
			sum += x;
		}
	}
	auto end = chrono::high_resolution_clock::now();

	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << "\t" << sum << endl;
}

int main() {
	ofstream a{"vector_iter.txt"};
	ofstream b{"list_iter.txt"};

	for (int i = 0; i <= 2000; i += 10) {
		cout << i << endl;
		measure<vector<int>>(i, a);
		measure<list<int>>(i, b);
	}

	return 0;
}
