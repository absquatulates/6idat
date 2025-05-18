#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <random>
#include <numeric>

using namespace std;

void insert(vector<int> &into, int val) {
	into.push_back(val);
}

void insert(priority_queue<int> &into, int val) {
	into.push(val);
}

void insert(set<int> &into, int val) {
	into.insert(val);
}

template <class Container>
void measure_insert(int label, ofstream &out, const vector<int> &data) {
	const int TIMES = 1000;

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++) {
		Container c;

		for (size_t i = 0; i < data.size(); i++)
			insert(c, i);
	}
	auto end = chrono::high_resolution_clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << endl;
}

template <class Container>
void measure_bulk_insert(int label, ofstream &out, const vector<int> &data) {
	const int TIMES = 1000;

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++) {
		Container c(data.begin(), data.end());
	}
	auto end = chrono::high_resolution_clock::now();
	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << endl;
}

void remove_max(vector<int> &from) {
	from.erase(max_element(from.begin(), from.end()));
}

void remove_max(priority_queue<int> &from) {
	from.pop();
}

void remove_max(set<int> &from) {
	from.erase(prev(from.end()));
}

template <class Container>
void measure_remove(int label, ofstream &out, const vector<int> &data) {
	const int TIMES = 1000;

	Container c[TIMES];
	for (int i = 0; i < TIMES; i++)
		c[i] = Container(data.begin(), data.end());

	auto begin = chrono::high_resolution_clock::now();

	for (int i = 0; i < TIMES; i++) {
		while (!c[i].empty())
			remove_max(c[i]);
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
	cout << "Insert" << endl;
	{
		ofstream a{"vector_insert.txt"};
		ofstream b{"pq_insert.txt"};
		ofstream c{"set_insert.txt"};

		for (int i = 100; i <= 5000; i += 100) {
			cout << i << endl;
			vector<int> d{data(i)};

			measure_insert<vector<int>>(i, a, d);
			measure_insert<priority_queue<int>>(i, b, d);
			measure_insert<set<int>>(i, c, d);
		}
	}

	cout << "Bulk insert" << endl;
	{
		ofstream a{"vector_bulk_insert.txt"};
		ofstream b{"pq_bulk_insert.txt"};
		ofstream c{"set_bulk_insert.txt"};

		for (int i = 100; i <= 5000; i += 100) {
			cout << i << endl;
			vector<int> d{data(i)};

			measure_bulk_insert<vector<int>>(i, a, d);
			measure_bulk_insert<priority_queue<int>>(i, b, d);
			measure_bulk_insert<set<int>>(i, c, d);
		}
	}

	cout << "Remove max" << endl;
	{
		ofstream a{"vector_remove_max.txt"};
		ofstream b{"pq_remove_max.txt"};
		ofstream c{"set_remove_max.txt"};

		for (int i = 100; i <= 5000; i += 100) {
			cout << i << endl;
			vector<int> d{data(i)};

			if (i < 1000)
				measure_remove<vector<int>>(i, a, d);
			measure_remove<priority_queue<int>>(i, b, d);
			measure_remove<set<int>>(i, c, d);
		}
	}

	return 0;
}
