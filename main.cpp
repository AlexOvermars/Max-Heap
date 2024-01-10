#include "AVL_Tree.h"
#include <cassert>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>
#include <cstdlib>
using namespace std;

// parent of right node is equal to the removed node


// Test cases for basic structure
std::vector<std::vector<int>> test_cases{
        {1, 2, 3},
        {3, 2, 1},
        {1, 3, 2},
        {3, 1, 2}
};

void test_basic_structure() {

    for (auto test: test_cases) {
        avlTree tree;
        for (int n : test) {
            tree.add(n);
        }

        if (!tree.is_valid_avl(tree)){
            cout << "The Code is Broken";
        }
    }

}


// Complex test cases
std::vector<std::vector<int>> complex_cases{
        {10, 20, 30, 40, 50},
        {10, 20, 30, 50, 40},
        {30, 20, 10, 5, 1},
        {30, 20, 10, 1, 5},
        {5, 4, 6, 3, 7, 2, 8},
        {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30},
        {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33},
        {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36},
        {10, 8, 6, 4, 2, 0, -2, -4, -6, -8},
        {'A', 'B', 'C', 'D', 'E'},
        {1,1,1,1},
};

void test_complex_cases() {

    for (auto test: complex_cases) {
        avlTree tree;
        for (auto n : test) {
            tree.add(n);
        }

        //assert(tree.is_valid_avl(tree));
        if (!tree.is_valid_avl(tree)) {
            cout << "Not Valid Tree";
        }
    }

}


// Stress test insert
void test_stress_insert() {

    for (int i = 0; i < 100; i++) {
        std::vector<int> values;
        for (int j = 0; j < 900; j++) {
            int value = rand() % 20000 + 1;
            values.push_back(value);
        }

        avlTree tree;
        for (int value : values) {
            tree.add(value);
        }

        //assert(tree.is_valid_avl(tree));
        if (!tree.is_valid_avl(tree)) {
            cout << "Not Valid Tree";
        }
    }

}


// Test cases for removal
std::vector<std::pair<std::vector<int>, int>> removal_cases{

        {{1, 2, 3}, 1}, // No rotation
        {{1, 2, 3}, 2}, // No rotation
        {{1, 2, 3}, 3}, // No rotation

        {{50, 40, 60, 30, 70, 20, 80, 45}, 0}, // Delete min value
        {{50, 40, 60, 30, 70, 20, 80, 45}, 45}, // No rotation
        {{50, 40, 60, 30, 70, 20, 80, 45}, 40}, // No rotation
        {{50, 40, 60, 30, 70, 20, 80, 45}, 30}, // No rotation

        {{50, 40, 60, 30, 70, 20, 80, 45}, 20}, // RR rotation
        {{50, 40, 60, 30, 70, 20, 80, 15}, 40}, // LL rotation

        {{50, 40, 60, 30, 70, 20, 80, 35}, 20}, // RL rotation
        {{50, 40, 60, 30, 70, 20, 80, 25}, 40}, // LR rotation

};

void test_remove() {

    for (auto test: removal_cases) {
        avlTree tree;
        for (int n : test.first) {
            tree.add(n);
        }

        int del = test.second;
        tree.remove(del);

        //assert(tree.is_valid_avl(tree));
        if (!tree.is_valid_avl(tree)) {
            cout << "Not Valid Tree";
        }
    }

}

void test_remove2() {
    avlTree tree;
    for (int n = -9; n <= 15; n+=2) {
        tree.add(n);
    }

    for(int n = -9; n <= 9; n+=2) {
        tree.remove(n);
        if (!tree.is_valid_avl(tree)) {
            cout << "Not Valid Tree";
        }
    }
}

void test_remove3() {
    avlTree tree;
    for (int n = 0; n <= 33; n += 3) {
        tree.add(n);
    }

    for (int n = 0; n <= 9; n += 2) {
        tree.remove(n);
        if (!tree.is_valid_avl(tree)) {
            std::cout << "Not Valid Tree";
        }
    }
}

void test_stress_remove() {
    srand(time(nullptr));

    for (int i = 0; i < 100; i++) {
        std::vector<int> values;
        while (values.size() < 200) {
            int val = rand() % 20000 + 1;
            //cout << val << ", ";
            values.push_back(val);
        }
        avlTree tree;

        for (size_t j = 0; j < values.size(); j += 1) {
            tree.add(values[j]);
            assert(tree.is_valid_avl(tree));
        }
        //cout << "Hello World";
        for (size_t j = 0; j < values.size(); j += 2) {
            tree.remove(values[j]);
            if (!tree.is_valid_avl(tree)) {
                //std::cout << j << endl;
                tree.is_valid_avl(tree);
                std::cerr << "PROBLEM WITH REMOVE OPERATION" << std::endl;
            }
        }
    }
}

void failing_test() {
    std::vector<std::vector<int>> removal_cases{
            {3420, 7672, 15344, 11728, 389, 13594, 456, 5929, 183, 16938},
            {4571, 5225, 9745, 18797, 10605, 12132, 4331, 12575, 6301, 5505},
            {2873, 7671, 12817, 19442, 2606, 16531, 19468, 2485, 15177, 2097}
    };
    for (auto test: removal_cases) {
        avlTree tree;
        for (size_t j = 0; j < test.size(); j += 2) {
            tree.add(test[j]);
        }

        for (size_t j = 0; j < test.size(); j += 2) {
            //cout << "Removing: " << test[j] << endl;
            tree.remove(test[j]);
            if (!tree.is_valid_avl(tree)) {
                //std::cout << j << endl;
                tree.is_valid_avl(tree);
                std::cerr << "PROBLEM WITH REMOVE OPERATION" << std::endl;
            }
        }

        //assert(tree.is_valid_avl(tree));
        if (!tree.is_valid_avl(tree)) {
            cout << "Not Valid Tree";
        }
    }
}

int main() {

    /*test_basic_structure();
    test_complex_cases();
    test_stress_insert();
    test_remove();
    test_remove2();
    test_remove3();*/
    test_stress_remove();
    failing_test();

    //std::cout << "All tests passed!" << std::endl;

    return 0;
}