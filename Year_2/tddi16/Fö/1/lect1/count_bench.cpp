#include <chrono>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include "count.h"

// Global variabel för att undvika för mycket kompilatoroptimeringar.
volatile int dont_optimize_too_much;

template <class Fn>
double measure_one(Fn fn, int max_value, int elements) {
	vector<int> data;
	std::random_device dev;
	std::uniform_int_distribution<int> dist(0, max_value - 1);
	for (int i = 0; i < elements; i++)
		data.push_back(dist(dev));

	auto begin = std::chrono::high_resolution_clock::now();
	std::vector<int> result = fn(data, max_value);
	auto end = std::chrono::high_resolution_clock::now();

	// Undvik att kompilatorn optimerar för mycket...
	dont_optimize_too_much = std::accumulate(result.begin(), result.end(), 0);

	return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0;
}

int main(int argc, const char *argv[]) {
	if (argc < 2) {
		std::cout << "No parameter!" << std::endl;
		return 1;
	}

	std::ofstream out(argv[1]);

	int max = 10000;
	for (int i = 0; i <= max; i += 100) {
		int value = std::max(1, i);

		out << value << "\t"

			<< measure_one(solution_a, value, value) << "\t"
			<< measure_one(solution_a, max, value) << "\t"
			<< measure_one(solution_a, value, max) << "\t"

			<< measure_one(solution_b, value, value) << "\t"
			<< measure_one(solution_b, max, value) << "\t"
			<< measure_one(solution_b, value, max) << "\n";

		if ((i % 1000) == 0)
			std::cout << i << " of " << max << std::endl;
	}
}
