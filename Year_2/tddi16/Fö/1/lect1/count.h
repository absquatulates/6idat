#include <vector>
#include <algorithm>

using std::vector;

// begin SOLUTION_A:
vector<int> solution_a(
		const vector<int> &input,
		int max_val)
{
	vector<int> result(max_val, 0);
	for (int i = 0; i < max_val; i++) {
		result[i] = std::count(input.begin(), input.end(), i);
	}
	return result;
}
// end SOLUTION_A

// begin SOLUTION_B:
vector<int> solution_b(
		const vector<int> &input,
		int max_val)
{
	vector<int> result(max_val, 0);
	for (int i = 0; i < input.size(); i++) {
		int value = input[i];
		result[value] += 1;
	}
	return result;
}
// end SOLUTION_B
