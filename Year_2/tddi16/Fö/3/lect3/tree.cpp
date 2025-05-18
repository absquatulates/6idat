class Node {
public:
	Node(int v, Node *l, Node *r) :
		v{v}, l{l}, r{r} {}

	int v;
	Node *l;
	Node *r;
};
// end NODE

Node *find(Node *root, int value) {
	if (!root)
		return nullptr;

	if (value < root->v) {
		return find(root->l, value);
	} else if (value > root->v) {
		return find(root->r, value);
	} else { // value == root->v
		return root;
	}
}
// end FIND
