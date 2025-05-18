#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

typedef vector<int>::iterator iter;

ostream &operator <<(ostream &to, const vector<int> &v) {
	to << "[";

	if (v.size() > 0)
		to << v[0];

	for (size_t i = 1; i < v.size(); i++)
		to << ", " << v[i];

	to << "]";
	return to;
}

bool is_sorted(const vector<int> &v) {
	for (size_t i = 1; i < v.size(); i++) {
		if (v[i - 1] > v[i])
			return false;
	}
	return true;
}

void insertion_sort(vector<int> &v) {
	// Dela i två delar: en sorterad och en osorterad.
	for (size_t pos = 1; pos < v.size(); pos++) {
		// Flytta det första osorterade elementet
		// tills det hamnar på rätt plats i den
		// sorterade delen.
		for (size_t i = pos; i > 0; i--) {
			if (v[i - 1] <= v[i])
				break;
			swap(v[i - 1], v[i]);
		}
	}
}
// end INSERTION

void selection_sort(vector<int> &v) {
	if (v.empty()) return;
	// Dela i två delar: en sorterad och en osorterad.
	for (size_t pos = 0; pos < v.size() - 1; pos++) {
		// Hitta det minsta i den osorterade delen...
		size_t min = pos;
		for (size_t i = pos; i < v.size(); i++)
			if (v[min] > v[i])
				min = i;
		// ... och sätt det sist i den sorterade.
		swap(v[min], v[pos]);
	}
}
// end SELECTION

void bubble_sort(vector<int> &v) {
	for (size_t t = 0; t < v.size(); t++) {
		// Iterera genom arrayen och flytta element.
		for (size_t i = 1; i < v.size() - t; i++) {
			if (v[i - 1] > v[i])
				swap(v[i - 1], v[i]);
		}
	}
}
// end BUBBLE

void bst_sort(vector<int> &v) {
	multiset<int> data(v.begin(), v.end());
	size_t pos = 0;
	for (auto &&x : data)
		v[pos++] = x;
}
// end BST

void heap_sort(vector<int> &v) {
	make_heap(v.begin(), v.end());

	for (iter end = v.end(); end != v.begin(); --end)
		pop_heap(v.begin(), end);
}
// end HEAP

// begin DO_MERGE:
vector<int> merge(const vector<int> &a, const vector<int> &b) {
	vector<int> result;
	auto aPos = a.begin(), bPos = b.begin();
	while (aPos != a.end() && bPos != b.end()) {
		if (*aPos < *bPos)
			result.push_back(*(aPos++));
		else
			result.push_back(*(bPos++));
	}

	while (aPos != a.end())
		result.push_back(*(aPos++));
	while (bPos != b.end())
		result.push_back(*(bPos++));

	return result;
}
// end DO_MERGE

vector<int> merge_sort(iter begin, iter end) {
	if (end - begin <= 1)
		return vector<int>(begin, end);

	iter half = begin + (end - begin)/2;
	vector<int> a = merge_sort(begin, half);
	vector<int> b = merge_sort(half, end);

	return merge(a, b);
}
// end MERGE

void do_merge_sort(vector<int> &v) {
	v = merge_sort(v.begin(), v.end());
}

iter partition(iter begin, iter end, iter pivot_pos) {
	if (begin != pivot_pos)
		swap(*begin, *pivot_pos);

	int pivot = *begin;

	// Partition around the pivot element.
	iter left = begin, right = end - 1;
	while (left < right) {
		// Find something to put in the left position.
		while (left < right && *right >= pivot)
			right--;
		if (left < right)
			*(left++) = *right;

		// Find something to put in the right position.
		while (left < right && pivot >= *left)
			left++;
		if (left < right)
			*(right--) = *left;
	}
	// Put the pivot back where it belongs.
	*left = pivot;

	return left;
}
// end PARTITION

void quicksort(iter begin, iter end) {
	if (end - begin <= 1)
		return;
	// Vi väljer alltid sista elementet för
	// enkelhets skull. Det finns bättre alternativ.
	iter pivot = end - 1;
	iter middle = partition(begin, end, pivot);
	// Sortera båda halvorna med quicksort.
	quicksort(begin, middle);
	quicksort(middle + 1, end);
}
// end QUICK

void do_quicksort(vector<int> &v) {
	quicksort(v.begin(), v.end());
}

void std_sort(vector<int> &v) {
	std::sort(v.begin(), v.end());
}

void std_stable_sort(vector<int> &v) {
	std::stable_sort(v.begin(), v.end());
}

template <typename T>
void sort(vector<int> data, T fn) {
	fn(data);
	cout << data << endl;
	if (!is_sorted(data))
		cout << "ERROR! Not sorted!" << endl;
}

template <typename T>
size_t time(vector<int> data, T fn) {
	auto a = chrono::high_resolution_clock::now();
	fn(data);
	auto b = chrono::high_resolution_clock::now();
	if (!is_sorted(data))
		cerr << "ERROR! Not sorted!" << endl;
	return chrono::duration_cast<chrono::milliseconds>(b - a).count();
}

void time_fns(ostream &to, const vector<int> &) {
	to << endl;
}

template <typename First, typename... Rest>
void time_fns(ostream &to, const vector<int> &data, First first, Rest...fn) {
	to << "\t" << time(data, first);
	time_fns(to, data, fn...);
}

template <typename... T>
void time(const string &file, size_t elements, size_t step, T...fn) {
	mt19937 random;
	vector<int> data(elements, 0);
	uniform_int_distribution<int> dist(0, 2000);
	generate(data.begin(), data.end(), [&dist, &random]() { return dist(random); });

	ofstream out(file);
	vector<int> to_sort;
	for (size_t i = 0; i <= data.size(); i += step) {
		cerr << i << " of " << data.size() << "..." << endl;

		while (to_sort.size() < i)
			to_sort.push_back(data[to_sort.size()]);

		out << i;
		time_fns(out, to_sort, fn...);
	}
}

void sanity_check() {
	// Simple test to check that the sorting is correct.
	vector<int> data{5, 1, 8, 7, 2};
	cout << data << endl;

	sort(data, insertion_sort);
	sort(data, selection_sort);
	sort(data, bubble_sort);
	sort(data, bst_sort);
	sort(data, heap_sort);
	sort(data, do_merge_sort);
	sort(data, do_quicksort);
	sort(data, std_sort);
}

int main() {
	sanity_check();

	cerr << "Comparison between all..." << endl;
	time("sort.txt", 20000, 200, bubble_sort, insertion_sort, selection_sort, do_merge_sort, bst_sort, heap_sort, do_quicksort, std_sort);

	cerr << "Comparing the fast ones..." << endl;
	time("sort_fast.txt", 200000, 2000, do_merge_sort, bst_sort, heap_sort, do_quicksort, std_sort, std_stable_sort);

	return 0;
}
