#include <iostream>

using namespace std;

double probability(int elements, int slots) {
	double result{1.0};
	for (int i{}; i < elements; i++)
		result *= double(slots - i) / double(slots);
	return 1.0 - result;
}

int main() {
	const int slots = 100;

	for (int i{}; i <= slots; i++) {
		cout << i << "\t" << probability(i, slots) << endl;
	}

	return 0;
}
