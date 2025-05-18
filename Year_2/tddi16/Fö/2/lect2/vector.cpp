void append(T x) {
	if (count >= capacity)
		grow();

	data[count] = x;
	count++;
}
// end APPEND

void insert(int pos, T x) {
	if (count >= capacity)
		grow();

	for (int i = count - 1; i >= pos; i--)
		data[i + 1] = data[i];

	data[pos] = x;
	count++;
}
// end INSERT

void grow() {
	int new_capacity = 2 * capacity;
	T *new_data = new T[new_capacity];

	for (int i = 0; i < capacity; i++)
		new_data[i] = data[i];

	data = new_data;
	capacity = new_capacity;
}
// end GROW
