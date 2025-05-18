struct data {
	int a;
	int b;
};

size_t hash(const data &v) {
	size_t result = v.a;
	result ^= v.b << 16;
	return result;
}
// end MEMBERS

size_t hash(const std::string &v) {
	size_t result = 5381;
	for (char c : v) {
		// result = result * 33 + c;
		result = ((result << 5) + result) + c;
	}
	return result;
}
// end STR
