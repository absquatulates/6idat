// begin NO_AMORTIZED:
void f(vector<int> &data) {
	int sum = 0;
	for (int i = 1; i < data.size(); i *= 2) {
		sum += data[i];
	}
	data.push_back(sum);
}
// end NO_AMORTIZED

void f(vector<int> &data) {
	int sum = 0;
	for (int i = data.size() - 1; i > 0; i--) {
		sum += data[i];
		data.push_back(sum);
	}
}
// end AMORTIZED
