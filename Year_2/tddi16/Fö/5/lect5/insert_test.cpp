#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

// Kompilera med O2

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
void measure(int label, ofstream &out, const vector<int> &source) {
	const int TIMES = 1000;

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++) {
		Container data;
		for (int i : source) {
			insert(data, i);
		}
	}
	auto end = chrono::high_resolution_clock::now();

	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << endl;
}

vector<int> data(int size) {
	vector<int> data(size, 0);
	iota(data.begin(), data.end(), 0);
	mt19937 random;
	shuffle(data.begin(), data.end(), random);
	return data;
}

int main() {
	ofstream a{"vector_insert.txt"};
	ofstream b{"set_insert.txt"};
	ofstream c{"uset_insert.txt"};

	for (int i = 10; i <= 2000; i += 10) {
		cout << i << endl;
		vector<int> data = ::data(i);
		measure<vector<int>>(i, a, data);
		measure<set<int>>(i, b, data);
		measure<unordered_set<int>>(i, c, data);
	}

	return 0;
}
