#include "count.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <cstring>

template <class Fn>
void measure(Fn fn, int elements, int max_value) {
	vector<int> data;
	std::random_device dev;
	std::uniform_int_distribution<int> dist(0, max_value - 1);
	for (int i = 0; i < elements; i++)
		data.push_back(dist(dev));

	std::cout << "Antal element : " << elements << std::endl;
	std::cout << "Maximalt värde: " << max_value << std::endl;

	auto begin = std::chrono::high_resolution_clock::now();
	std::vector<int> result = fn(data, max_value);
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Tid: "
			  << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0
			  << " ms" << std::endl;

	for (int i = 0; i < std::min(max_value, 10); i++) {
		std::cout << std::setw(2) << i << ": " << std::setw(4) << result[i] << std::endl;
	}

	std::cout << "Summa: " << std::accumulate(result.begin(), result.end(), 0) << std::endl;
}

int main(int argc, const char **argv) {
	if (argc < 4) {
		std::cout << "Usage: [a/b] [elements] [max_value]" << std::endl;
		return 1;
	}

	int elements = std::stoi(argv[2]);
	int max_value = std::stoi(argv[3]);

	if (strcmp(argv[1], "a") == 0) {
		measure(solution_a, elements, max_value);
	} else if (strcmp(argv[1], "b") == 0) {
		measure(solution_b, elements, max_value);
	} else {
		std::cout << "Specify either a or b\n";
		return 1;
	}

	return 0;
}
