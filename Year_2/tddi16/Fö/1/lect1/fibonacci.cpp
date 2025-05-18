#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;

int fib1(int n) {
	if (n == 1 || n == 2) {
		return 1;
	} else {
		return fib1(n - 1)
			+ fib1(n - 2);
	}
}
// end FIB1

int fib2(int n) {
	vector<int> res(n+1, 1);

	for (int i=3; i<=n; i++) {
		res[i] = res[i - 1]
				+ res[i - 2];
	}

	return res[n];
}
// end FIB2

template <class Fn>
void measure(Fn fn, int label, ofstream &out) {
	const int TIMES = 1000000;

	int result = 0;
	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < TIMES; i++)
		result += fn();
	auto end = chrono::high_resolution_clock::now();

	auto ms = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
	out << label << "\t" << ms << "\t" << result << endl;
}

void check(int i, ofstream &a, ofstream &b) {
	measure([i](){ return fib1(i); }, i, a);
	measure([i](){ return fib2(i); }, i, b);
}

int main() {
	ofstream a{"fib1.txt"};
	ofstream b{"fib2.txt"};

	for (int i = 1; i <= 15; i++) {
		cout << i << endl;
		check(i, a, b);
	}

	return 0;
}
