class Node {
public:
	Node(int v, Node *l, Node *r) :
		v{v}, l{l}, r{r} {}

	int v;
	Node *l;
	Node *r;
};
// end NODE

void traverse(Node *n) {
	if (!n)
		return;

	// 1
	traverse(n->l);
	// 2
	traverse(n->r);
	// 3
}
// end TRAVERSE

void traverse(Node *n) {
	if (!n)
		return;

	cout << n->v << endl;
	traverse(n->l);
	traverse(n->r);
}
// end TRAVERSE1

void traverse(Node *n) {
	if (!n)
		return;

	traverse(n->l);
	cout << n->v << endl;
	traverse(n->r);
}
// end TRAVERSE2

void traverse(Node *n) {
	if (!n)
		return;

	traverse(n->l);
	traverse(n->r);
	cout << n->v << endl;
}
// end TRAVERSE3

// begin TRAVERSE_STACK:
void traverse(Node *root) {
	stack<Node *> s;
	s.push(root);
	while (!s.empty()) {
		Node *n = s.top(); s.pop();
		cout << n->v << endl;
		if (n->l) s.push(n->l);
		if (n->r) s.push(n->r);
	}
}
// end TRAVERSE_STACK

// begin TRAVERSE_QUEUE:
void traverse(Node *root) {
	queue<Node *> q;
	q.push(root);
	while (!q.empty()) {
		Node *n = q.front(); q.pop();
		cout << n->v << endl;
		if (n->l) q.push(n->l);
		if (n->r) q.push(n->r);
	}
}
// end TRAVERSE_QUEUE

// begin TRAVERSE_INORDER:
void traverse(Node *root) {
	stack<Node *> s;
	Node *current = root;
	while (current || !s.empty()) {
		while (current) {
			s.push(current);
			current = current->l;
		}
		current = s.top(); s.pop();
		cout << current->v << endl;
		current = current->r;
	}
}
// end TRAVERSE_INORDER
