#ifdef _WIN32
#include <Windows.h>
struct Setup {
    Setup() {
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
    }
} setup;
#endif


#include <iostream>
#include "avl_tree.h"

template <typename Comparable>
void testcase1(AVL_Tree<Comparable> &tree)
{
    tree.insert(6);
    tree.insert(4);
    tree.insert(10);
    tree.insert(5);

    std::cout << "Före borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.remove(10);
    std::cout << "Efter borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.clear();
}

template <typename Comparable>
void testcase2(AVL_Tree<Comparable> &tree)
{
    tree.insert(6);
    tree.insert(4);
    tree.insert(10);
    tree.insert(15);

    std::cout << "Före borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.remove(4);
    std::cout << "Efter borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.clear();
}

template <typename Comparable>
void testcase3(AVL_Tree<Comparable> &tree)
{
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

    std::cout << "Före borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.remove(9);
    std::cout << "Efter borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.clear();
}


template <typename Comparable>
void testcase4(AVL_Tree<Comparable> &tree)
{
    //tree.insert(1);
    
    tree.insert(9);
    tree.insert(4);
    tree.insert(11);
    tree.insert(2);
    tree.insert(10);
    tree.insert(6);
    tree.insert(12);
    tree.insert(1);
    tree.insert(13);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(8);
    tree.insert(16);
    tree.insert(17);
    tree.insert(20);
    tree.insert(81);
    tree.insert(67);
    tree.insert(55);
    
    tree.insert(100);
    tree.insert(111);
    tree.insert(188);
    tree.insert(98);
    tree.insert(72);
    tree.insert(1);
    tree.insert(1);
    tree.insert(1);
    tree.insert(1);
    tree.insert(4);
    tree.insert(4444);
    tree.insert(47);
    tree.insert(87);
    tree.insert(177);
    tree.insert(134);
    tree.insert(2090);
    tree.insert(82);
    tree.insert(69);
    tree.insert(52);

    std::cout << "Före borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.remove(9);
    tree.remove(20);
    std::cout << "Efter borttagning: \n" << std::endl;
    tree.print_tree(std::cout);
    std::cout << std::endl;

    tree.clear();
}

int main()
{
    AVL_Tree<int> avl_tree;

    unsigned int choice;

    while (true)
    {
        std::cout << endl;
        cout << "1 - Testfall 1\n";
        cout << "2 - Testfall 2\n";
        cout << "3 - Testfall 3\n";
        cout << "4 - Testfall 4\n";
        cout << "0 - Avsluta.\n" << endl;
        cout << "Val: ";
        cin >> choice;
        cout << endl;

        try {
            switch (choice) {
            case 0:
                cout << "Slut." << endl;
                return 0;
            case 1:
                cout << "Testfall 1" << std::endl;
                testcase1(avl_tree);
                break;
            case 2:
                cout << "Testfall 2" << std::endl;
                testcase2(avl_tree);
                break;
            case 3:
                cout << "Testfall 3" << std::endl;
                testcase3(avl_tree);
                break;
            case 4:
                cout << "Testfall 4" << endl;
                testcase4(avl_tree);
            default:
                cout << "Felaktigt val!" << '\b' << endl;
                break;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;
        } catch (...) {
            cout << "Ett okänt fel har inträffat." << endl;
        }
    }

    return 0;
}