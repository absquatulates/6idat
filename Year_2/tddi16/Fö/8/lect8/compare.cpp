#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

void compare_a(vector<string> a, vector<string> b) {
	for (auto &&x : a) {
		if (find(b.begin(), b.end(), x) == b.end()) {
			cout << "-> " << x << endl;
		}
	}

	for (auto &&x : b) {
		if (find(a.begin(), a.end(), x) == a.end()) {
			cout << "<- " << x << endl;
		}
	}
}

void compare_b(vector<string> a, vector<string> b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	size_t aPos = 0;
	size_t bPos = 0;
	while (aPos < a.size() && bPos < b.size()) {
		const string &aElem = a[aPos];
		const string &bElem = b[bPos];

		if (aElem < bElem) {
			cout << "-> " << aElem << endl;
			aPos++;
		} else if (aElem > bElem) {
			cout << "<- " << bElem << endl;
			bPos++;
		} else {
			aPos++;
			bPos++;
		}
	}

	for (; aPos < a.size(); aPos++)
		cout << "-> " << a[aPos] << endl;

	for (; bPos < b.size(); bPos++)
		cout << "<- " << b[bPos] << endl;
}

void test(vector<string> a, vector<string> b) {
	ofstream to("compare.txt");
	const size_t step = 10;

	vector<string> newA;
	for (size_t i = 0; i < a.size(); i += step) {
		cerr << i << " of " << a.size() << "..." << endl;

		while (newA.size() < i)
			newA.push_back(a[newA.size()]);

		auto time_a = chrono::high_resolution_clock::now();
		for (int i = 0; i < 10; i++)
			compare_a(newA, newA);
		auto time_b = chrono::high_resolution_clock::now();
		for (int i = 0; i < 10; i++)
			compare_b(newA, newA);
		auto time_c = chrono::high_resolution_clock::now();

		to << i << "\t" << chrono::duration_cast<chrono::milliseconds>(time_b - time_a).count()
		   << "\t" << chrono::duration_cast<chrono::milliseconds>(time_c - time_b).count() << endl;
	}
}

vector<string> read() {
	string s;
	vector<string> r;
	while (cin >> s && s != "#")
		r.push_back(s);
	return r;
}

int main(int argc, const char *argv[]) {
	if (argc != 2) {
		cerr << "Need either 'a', 'b' or 't' as a parameter!" << endl;
		return 1;
	}

	string arg{argv[1]};
	void (*fn)(vector<string>, vector<string>);
	if (arg == "a") {
		fn = &compare_a;
	} else if (arg == "b") {
		fn = &compare_b;
	} else if (arg == "t") {
		fn = &test;
	} else {
		cerr << "Enter 'a' or 'b'!" << endl;
		return 1;
	}

	vector<string> a = read();
	vector<string> b = read();
	(*fn)(a, b);

	return 0;
}
