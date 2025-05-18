/////////////////////////////////////////////////////////////
/**
 * remove() tar bort elementet x ur trädet t, om x finns.
 *
 * Comparable och Node_Pointer är formella typer som får specificeras på
 * något sätt (template-parameter, typedef eller ersättning med konkret typ).
 */
    if (t == nullptr) {
        throw AVL_Tree_error("WILLIAM");
    }

    if (x < t->element) {
        remove(x, t->left);

//////////////////////////////////////////////////
        if (Node::node_height(t->left) - Node::node_height(t->right) == 2)
            if (x < t->left->element)
                Node::single_rotate_with_left_child(t);
            else
                Node::double_rotate_with_left_child(t);
        else
            Node::calculate_height(t);
/////////////////////////////////////////////////////

    } else if (t->element < x) {
        remove(x, t->right);

//////////////////////////////////////////////////////////////
        if (Node::node_height(t->right) - Node::node_height(t->left) == 2)
            if (t->right->element < x)
                Node::single_rotate_with_right_child(t);
            else
                Node::double_rotate_with_right_child(t);
        else
            Node::calculate_height(t);
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
/////////////////////////////////////////////////////////////




















    tree.insert(1);
    tree.insert(9);
    tree.insert(1);
    tree.insert(4);
    tree.insert(1);
    tree.insert(11);
    tree.insert(1);
    tree.insert(2);
    tree.insert(1);
    tree.insert(6);
    tree.insert(1);
    tree.insert(10);
    tree.insert(1);
    tree.insert(12);
    tree.insert(1);
    tree.insert(1);
    tree.insert(1);
    tree.insert(3);
    tree.insert(1);
    tree.insert(5);
    tree.insert(1);
    tree.insert(7);
    tree.insert(1);
    tree.insert(13);
    tree.insert(1);
    tree.insert(8);