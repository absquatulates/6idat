#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

// Increase a digit.
int increaseDigit(int num) {
	return (num + 1) % 10;
}

// Decrease a digit (note: modulo in C++ behaves strange with negative numbers, so we add 9 instead
// of subtracting 1, which is equivalent)
int decreaseDigit(int num) {
	return (num + 9) % 10;
}

int intPow(int exp) {
	return static_cast<int>(pow(10, exp));
}

// Increase digit with index 'i'.
int increaseDigit(int num, int i) {
	int below = num % intPow(i);
	int above = num / intPow(i + 1);
	int mid = (num % intPow(i + 1)) / intPow(i);

	return above*intPow(i+1) + increaseDigit(mid)*intPow(i) + below;
}

// Decrease digit with index 'i'.
int decreaseDigit(int num, int i) {
	int below = num % intPow(i);
	int above = num / intPow(i + 1);
	int mid = (num % intPow(i + 1)) / intPow(i);

	return above*intPow(i+1) + decreaseDigit(mid)*intPow(i) + below;
}

// Increase the two least significant digits.
int increaseLow(int num) {
	num = increaseDigit(num, 0);
	num = increaseDigit(num, 1);
	return num;
}

// Increase the two middle digit.
int increaseMid(int num) {
	num = increaseDigit(num, 2);
	num = increaseDigit(num, 3);
	return num;
}

// Increase the two most significant digits.
int increaseHigh(int num) {
	num = increaseDigit(num, 4);
	num = increaseDigit(num, 5);
	return num;
}

// Decrease the lower two digits.
int decreaseLow(int num) {
	num = decreaseDigit(num, 1);
	num = decreaseDigit(num, 2);
	return num;
}

// Decrease the lower two digits.
int decreaseHigh(int num) {
	num = decreaseDigit(num, 3);
	num = decreaseDigit(num, 4);
	return num;
}

vector<int> bfs(int from, int to) {
	vector<function<int(int)>> options{increaseHigh, increaseMid, increaseLow, decreaseHigh, decreaseLow};

	// Remember where we came from!
	vector<int> prev(1000000, -1);

	queue<int> q;
	q.push(from);

	// Mark the starting node so we can recognize it later.
	prev[from] = from;

	while (!q.empty()) {
		int now = q.front(); q.pop();
		if (now == to)
			break;

		for (auto &&f : options) {
			int next = f(now);
			if (prev[next] < 0) {
				// Mark where we came from, bonus mark it as visited!
				prev[next] = now;
				q.push(next);
			}
		}
	}

	// Did we find any path?
	if (prev[to] < 0)
		return vector<int>();

	// Find the path by looking at the 'prev' array.
	vector<int> result;
	for (int at = to; prev[at] != at; at = prev[at]) {
		result.push_back(at);
	}
	result.push_back(from);

	reverse(result.begin(), result.end());

	return result;
}

int main(int argc, const char **argv) {
	int from = 0;
	int to = 568919;

	if (argc == 3) {
		from = stoi(argv[1]);
		to = stoi(argv[2]);
	}

	vector<int> r = bfs(from, to);

	if (r.empty()) {
		cout << "No solution!" << endl;
	} else {
		cout << (r.size() - 1) << " presses:\n";

		cout << setfill('0') << setw(6) << r[0];
		for (size_t i = 1; i < r.size(); i++)
			cout << " -> " << setfill('0') << setw(6) << r[i];
	}

	return 0;
}
