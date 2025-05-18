#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

void insert(vector<int> &t, int value) {
	t.push_back(value);
}

void insert(set<int> &t, int value) {
	t.insert(value);
}

void insert(unordered_set<int> &t, int value) {
	t.insert(value);
}

bool find(const vector<int> &t, int value) {
	return std::find(t.begin(), t.end(), value) != t.end();
}

bool find(const set<int> &t, int value) {
	return t.find(value) != t.end();
}

bool find(const unordered_set<int> &t, int value) {
	return t.find(value) != t.end();
}

template <class Container>
void measure(int label, ofstream &out) {
	const int TIMES = 100000;

	Container c;
	for (int i = 0; i < label; i++)
		insert(c, i);

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++) {
		int to_find = label - 1 - (i % label);
		if (!find(c, to_find))
			break;
	}
	auto end = chrono::high_resolution_clock::now();

	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << endl;
}

int main() {
	ofstream a{"vector_find.txt"};
	ofstream b{"set_find.txt"};
	ofstream c{"uset_find.txt"};

	for (int i = 10; i <= 1000; i += 10) {
		cout << i << endl;
		measure<vector<int>>(i, a);
		measure<set<int>>(i, b);
		measure<unordered_set<int>>(i, c);
	}

	return 0;
}
