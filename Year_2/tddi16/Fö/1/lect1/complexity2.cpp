int c(int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += b(i);
	return sum;
}
