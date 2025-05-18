int fibonacci(int x) {
	int result = x;
	if (x > 1)
		result = fibonacci(x - 1) + fibonacci(x - 2);

	return result;
}
// end OLD

unordered_map<int, int> table;
int fibonacci(int x) {
	auto i = table.find(x);
	if (i != table.end())
		return i->second;

	int result = x;
	if (x > 1)
		result = fibonacci(x - 1) + fibonacci(x - 2);

	table[x] = result; // Kom ihåg!
	return result;
}
// end NEW
