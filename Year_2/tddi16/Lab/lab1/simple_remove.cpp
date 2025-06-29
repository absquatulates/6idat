/**
 * remove() tar bort elementet x ur trädet t, om x finns.
 *
 * Comparable och Node_Pointer är formella typer som får specificeras på
 * något sätt (template-parameter, typedef eller ersättning med konkret typ).
 */
void remove(const Comparable &x, Node_Pointer &t) {
    if (t == nullptr) {
        return;  // Här kan ett undantag genereras i stället ...
    }

    if (x < t->element) {
        remove(x, t->left);

//////////////////////////////////////////////////
        if (node_height(t->left) - node_height(t->right) == 2)
            if (x < t->left->element)
                single_rotate_with_left_child(t);
            else
                double_rotate_with_left_child(t);
        else
            calculate_height(t);
/////////////////////////////////////////////////////

    } else if (t->element < x) {
        remove(x, t->right);

//////////////////////////////////////////////////////////////
        if (node_height(t->right) - node_height(t->left) == 2)
            if (t->right->element < x)
                single_rotate_with_right_child(t);
            else
                double_rotate_with_right_child(t);
        else
            calculate_height(t);
///////////////////////////////////////////////////////////

    } else {
        // Sökt värde finns i noden t
        Node_Pointer  tmp;

        if (t->left != nullptr && t->right != nullptr) {
            // Noden har två barn och ersätts med inorder efterföljare
            tmp = find_min(t->right);
            t->element = tmp->element;
            remove(t->element, t->right);
        } else {
            // Noden har inget eller ett barn
            tmp = t;

            if (t->left == nullptr)
                t = t->right;
            else
                t = t->left;

            delete tmp;
        }
    }
}
