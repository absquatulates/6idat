void elemAt(int i) {
	Node *at = begin;
	for (int x = 0; x < i; x++)
		at = at->next;
	return at;
}
// end AT

void append(T x) {
	Node *n = new Node();
	n->value = x;
	n->next = null;

	if (end) {
		end->next = n;
		end = n;
	} else {
		begin = end = n;
	}
}
// end APPEND

void insert(Node *i, T x) {
	Node *n = new Node();
	n->value = x;
	n->next = i->next;

	i->next = n;

	// div. specialfall
}
// end INSERT
