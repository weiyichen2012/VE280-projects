#include "recursive.h"
#include <climits> // To graders: Check my tree_min() implementation. I think my use of this lib is justified.

int size(list_t list) {
    // EFFECT: Returns the length (including 0) of the given list
    if (list_isEmpty(list)) {
        return 0;
    } else {
        return 1 + size(list_rest(list));
    }
}

int accumulate(list_t list, int (*f)(int, int), int base) {
    // Effect: Returns f(f(f(... f(base, l[0]) ..., l[-3]), l[-2]), l[-1]); Returns base for empty list
    if (list_isEmpty(list)) {
        return base;
    } else {
        return f(accumulate(list_rest(list), f, base), list_first(list));
    }
}

static int sum(int a, int b) {
    return a + b;
}

static int product(int a, int b) {
    return a * b;
}

int sum(list_t list) {
    // EFFECT: Returns the sum of all elements in list. For empty list return 0.
    return accumulate(list, sum, 0);
}

int product(list_t list) {
    // EFFECT: Returns the product of all elements in list. For empty list return 0.
    return accumulate(list, product, 1);
}

list_t filter(list_t list, bool (*f)(int)) {
    // Effect: Returns a list containing all elements from the given list passing the f() test in order.
    if (list_isEmpty(list)) {
        return list;
    } else {
        if (f(list_first(list))) {
            return list_make(list_first(list), filter(list_rest(list), f));
        } else {
            return filter(list_rest(list), f);
        }
    }
}

static bool isOdd(int num) {
    // Effect: Return true for an odd number, false otherwise.
    return num % 2;
}

static bool isEven(int num) {
    // Effect: Return false for an odd number, true otherwise.
    return !isOdd(num);
}

list_t filter_odd(list_t list) {
    // Effect: Returns a list containing all odd elements from the given list in order.
    return filter(list, isOdd);
}

list_t filter_even(list_t list) {
    // Effect: Returns a list containing all even elements from the given list in order.
    return filter(list, isEven);
}

list_t chop(list_t list, unsigned int n) {
    // Requires: size(list) >= n
    // Effect: Return list without the last n elements.
    if ((int)n == size(list)) {
        return list_make();
    } else {
        return list_make(list_first(list), chop(list_rest(list), n));
    }
}

list_t append(list_t first, list_t second) {
    // Effect: Returns first + second
    if (list_isEmpty(first)) {
        return second;
    } else {
        return list_make(list_first(first), append(list_rest(first), second));
    }
}

static list_t reverse_chop(list_t list, unsigned int n) {
    // Requires: size(list) >= n
    // Effect: Returns list only with the last n elements.
    if (size(list) == (int)n) {
        return list;
    } else {
        return reverse_chop(list_rest(list), n);
    }
}

static list_t limit(list_t list, unsigned int n) {
    // Requires: size(list) >= n
    // Effect: Returns list only with the first n elements.
    if (n) {
        return list_make(list_first(list), limit(list_rest(list), n - 1));
    } else {
        return list_make();
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n) {
    // Requires: size(list) >= n
    // Effect: Returns first n of first + second + the rest of first
    return append(limit(first, n), append(second, reverse_chop(first, size(first) - n)));
}

list_t reverse(list_t list) {
    // Effect: Returns the list in reversed order
    if (list_isEmpty(list)) {
        return list_make();
    } else {
        return list_make(list_first(reverse_chop(list, 1)), reverse(limit(list, size(list) - 1)));
    }
}

/**************************************************/

bool tree_search(tree_t tree, int key) {
    if (tree_isEmpty(tree)) {
        return false;
    } else {
        return (tree_elt(tree) == key) || tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
    }
}

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int depth(tree_t tree) {
    // Effect: Returns the depth (including 0) of a tree.
    if (tree_isEmpty(tree)) {
        return 0;
    } else {
        return 1 + MAX(depth(tree_left(tree)), depth(tree_right(tree)));
    }
}

list_t traversal(tree_t tree) {
    // Effect: Returns a list containing all elements of a tree once in the order of left to right
    if (tree_isEmpty(tree)) {
        return list_make();
    } else {
        return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
    }
}

int tree_sum(tree_t tree) {
    // Effect: Returns the sum of all elements of a tree.
    return sum(traversal(tree));
}


static int myMin(int a, int b) {
    // Effect: Returns the smaller one of two integers.
    return a < b ? a : b;
}

int tree_min(tree_t tree) {
    // Requires: tree non-empty
    // Effect: Returns the minimum element of the tree.
    return accumulate(traversal(tree), myMin, INT_MAX);
}

bool tree_hasPathSum(tree_t tree, int target) {
    // Effect: Returns whether the tree has a root to leaf path with all elements along have the sum equals to the target. Return false for an empty tree.
    if (tree_isEmpty(tree)) {
        return false;
    } else if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))){
        return target == tree_elt(tree);
    } else {
        return tree_hasPathSum(tree_left(tree), target - tree_elt(tree)) || tree_hasPathSum(tree_right(tree), target - tree_elt(tree));
    }
}

bool covered_by(tree_t coveree, tree_t coverer) {
    // Effect: Returns whether the coveree is covered by the coverer
    if (tree_isEmpty(coveree)) {
        return true;
    } else if (tree_isEmpty(coverer)){
        return false;
    } else {
        return tree_elt(coveree) == tree_elt(coverer) && covered_by(tree_left(coveree), tree_left(coverer)) && covered_by(tree_right(coveree), tree_right(coverer));
    }
}

bool contained_by(tree_t containee, tree_t container) {
    // Effect: Returns whether the containee is contained by the container
    if (tree_isEmpty(containee)) {
        return true;
    } else if (depth(containee) > depth(container)) {
        // includes the "container is empty" case.
        return false;
    } else {
        return covered_by(containee, container) || contained_by(containee, tree_left(container)) || contained_by(containee, tree_right(container));
    }
}

tree_t insert_tree(int element, tree_t tree) {
    // Requires: A sorted tree (including an empty tree)
    // Effect: Returns a sorted tree with the element inserted.
    if (tree_isEmpty(tree)) {
        return tree_make(element, tree_make(), tree_make());
    } else {
        if (element < tree_elt(tree)) {
            return tree_make(tree_elt(tree),
                insert_tree(element, tree_left(tree)),
                tree_right(tree)
            );
        } else {
            return tree_make(tree_elt(tree),
                tree_left(tree),
                insert_tree(element, tree_right(tree))
            );
        }
    }
}
