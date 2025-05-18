T elemAt(int i) {
	return data[i];
}
// end AT

void append(T x) {
	T *new_data = new T[count + 1];
	for (int i = 0; i < count; i++)
		new_data[i] = data[i];

	new_data[count] = x;
	delete []data;
	data = new_data;
	count++;
}
// end APPEND

void insert(int pos, T x) {
	T *new_data = new T[count + 1];
	for (int i = 0; i < pos; i++)
		new_data[i] = data[i];

	new_data[pos] = x;

	for (int i = pos; i < count; i++)
		new_data[i + 1] = data[i];
	delete []data;
	data = new_data; count++;
}
// end INSERT
