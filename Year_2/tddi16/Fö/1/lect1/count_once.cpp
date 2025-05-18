#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "count.h"

const int INPUT_COUNT = 100000;
const int MAX_VALUE = 10000;

template <class Fn>
void measure(Fn fn, const char *label) {
	std::vector<int> data;
	std::random_device dev;
	std::uniform_int_distribution<int> dist(0, MAX_VALUE);
	for (int i = 0; i < INPUT_COUNT; i++)
		data.push_back(dist(dev));

	auto begin = std::chrono::high_resolution_clock::now();
	std::vector<int> result = fn(data, MAX_VALUE);
	auto end = std::chrono::high_resolution_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
	std::cout << label << ": " << ms << " ms (";
	for (int i = 0; i < 10; i++)
		std::cout << " " << result[i];
	std::cout << " ...)\n";
}

int main() {
	measure(solution_a, "Solution a");
	measure(solution_b, "Solution b");
	return 0;
}
