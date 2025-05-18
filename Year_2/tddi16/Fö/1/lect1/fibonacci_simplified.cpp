int fib1(int n) {
	if (n == 1 || n == 2) {
		return 1;
	} else {
		return fib1(n - 1)
			+ fib1(n - 1);
	}
}
// end FIB1
