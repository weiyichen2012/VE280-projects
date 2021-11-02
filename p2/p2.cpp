//This file's comments follow the regulation of doxygen, https://www.doxygen.nl/
/**
 * @file p2.cpp
 * @author Yichen Wei (ethepherein@sjtu.edu.cn)
 * @brief VE280 project2
 * @date 2021-10-19
 * 
 */
#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

/**
 * @brief Recursively find the size of list, if list is empty return 0, else return 1 + the list except for the first element.
 * 
 * @param list The list that needs to be sized.
 * @return int The size of the list.
 */
int size(list_t list){
    if (list_isEmpty(list))
        return 0;
    else
        return 1 + size(list_rest(list));
}

/**
 * @brief Recursively find the sum of all the elements in the list, if list is empty then return 0, else return 
 * (the first element) + (the sum of the list except the first element).
 * 
 * @param list The list that needs to be summed.
 * @return int The sum of all elements in the list.
 */
int sum(list_t list){
    if (list_isEmpty(list))
        return 0;
    else
        return list_first(list) + sum(list_rest(list));
}

/**
 * @brief Recursively find the product of all the elements in the list, if list is empty then return 1, else return
 * (the first element) * (the product of the list except the first element).
 * 
 * @param list The list that needs to be producted.
 * @return int The product of all elements in the list.
 */
int product(list_t list){
    if (list_isEmpty(list))
        return 1;
    else
        return list_first(list) * product(list_rest(list));
}


/**
 * @brief Apply given fn to the list. Returns "base" if "list" is empty. Returns fn(list_first(list), accumulate(list_rest(list), fn, base) otherwise.
 * 
 * @param list The list that needs to be accumulated.
 * @param fn The operation.
 * @param base Return if list is empty.
 * @return int The result after accumulation.
 */
int accumulate(list_t list, int (*fn)(int, int), int base){
    if (list_isEmpty(list))
        return base;
    else
        return fn(list_first(list), accumulate(list_rest(list), fn, base));
}

/**
 * @brief Reverse a list recursively. Get the first element of leftList and use list_make to push it to reversedList.
 * Remove the first element in leftList and call recursively until the leftList is empty.
 * 
 * @param reversedList The current reversed list. 
 * @param leftList The original list that left to be reversed.
 * @return list_t The finished reversed list.
 */
static list_t reverseHelper(list_t reversedList, list_t leftList){
    if (list_isEmpty(leftList))
        return reversedList;
    else
        return reverseHelper(list_make(list_first(leftList), reversedList), list_rest(leftList));
}

/**
 * @brief Call reverseHelper to get the reversed of list.
 * 
 * @param list The list that needs to be reversed.
 * @return list_t The reversed list.
 */
list_t reverse(list_t list){
    return reverseHelper(list_make(), list);
}
/*
// EFFECTS: Returns the reverse of "list".
//
// For example: the reverse of ( 3 2 1 ) is ( 1 2 3 )
*/

/**
 * @brief Append two list recursively. Each step will put the last element of first into the head of the second,
 * then get rid of the last element of the first.
 * 
 * @param first The list in the front.
 * @param second The list behind.
 * @return list_t The resulted list.
 */
list_t append(list_t first, list_t second){
    if (list_isEmpty(first))
        return second;
    else
        return append(reverse(list_rest(reverse(first))), list_make(list_first(reverse(first)), second));
}

/**
 * @brief Get rid of all the elements that aren't odd rucursively. Each step check whether the first elemnt is odd or not.
 * If odd, then keep it. If not odd, then get rid of it.
 * 
 * @param list 
 * @return list_t 
 */
list_t filter_odd(list_t list){
    if (list_isEmpty(list))
        return list;
    else
        if (list_first(list) % 2 == 1)
            return list_make(list_first(list), filter_odd(list_rest(list)));
        else
            return filter_odd(list_rest(list));
}

/**
 * @brief Get rid of all the elements that aren't even rucursively. Each step check whether the first elemnt is even or not.
 * If even, then keep it. If not even, then get rid of it.
 * 
 * @param list 
 * @return list_t 
 */
list_t filter_even(list_t list){
    if (list_isEmpty(list))
        return list;
    else
        if (list_first(list) % 2 == 0)
            return list_make(list_first(list), filter_even(list_rest(list)));
        else
            return filter_even(list_rest(list));
}

/**
 * @brief Get rid of all the elements that fn isn't true. Each step check whether the first elemnt fn is true or not.
 * If true, then keep it. If false, then get rid of it.
 * 
 * @param list 
 * @return list_t 
 */
list_t filter(list_t list, bool (*fn)(int)){
    if (list_isEmpty(list))
        return list;
    else if (fn(list_first(list)))
        return list_make(list_first(list), filter(list_rest(list), fn));
    else
        return filter(list_rest(list), fn);
}

/**
 * @brief Recusively get rid of the first n elements in first, then append the rest to the second. Then add the individual
 * to the second recursively in the end.
 * @param first The front list.
 * @param second The behind list.
 * @param n The position n where insert begin.
 * @return list_t The result list.
 */
list_t insert_list(list_t first, list_t second, unsigned int n){
    if (n == 0)
        return append(second, first);
    else
        return list_make(list_first(first), insert_list(list_rest(first), second, n - 1));
}

/**
 * @brief Recursively chop down the last n elements in the list. In each step, get rid of the last element and let n - 1.
 * 
 * @param list The given list.
 * @param n The number of chop down.
 * @return list_t Result.
 */
list_t chop(list_t list, unsigned int n){
    if (n == 0)
        return list;
    else
        return chop(reverse(list_rest(reverse(list))), n - 1);
}

/**
 * @brief Recursively sum up of the tree. If tree is empty, sum = 0. else sum = elt + sum(left_tree) + sum(right_tree)
 * 
 * @param tree The given tree to be summed.
 * @return int The sum.
 */
int tree_sum(tree_t tree){
    if (tree_isEmpty(tree))
        return 0;
    else
        return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

/**
 * @brief Recursively search the tree. If the tree is empty, obviously false. Else result = (tree_search(left tree)) or (tree_search(right tree))
 * 
 * @param tree The given tree to be searched.
 * @param key The key to be searched.
 * @return true The key is found in the tree.
 * @return false The key isn't found in the tree.
 */
bool tree_search(tree_t tree, int key){
    if (tree_isEmpty(tree))
        return false;
    else if (tree_elt(tree) == key)
        return true;
    else
        return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
}

/**
 * @brief Recursively run through the tree. If the tree is empty, obvously depth = 0. Else depth = 1 + max(depth of left tree, depth of right tree).
 * 
 * @param tree The given tree to be depth.
 * @return int The depth.
 */
int depth(tree_t tree){
    if (tree_isEmpty(tree))
        return 0;
    else
        return max(depth(tree_left(tree)), depth(tree_right(tree))) + 1;
}

/**
 * @brief Recusively find the minimum of the elements. If tree is empty, returns a INT32_MAX so that it won't affect the result.
 * Else return the min(current element, tree_min(left tree), tree_min(right tree)).
 * 
 * @param tree The given tree to be minimumed.
 * @return int The min value.
 */
int tree_min(tree_t tree){
    if (tree_isEmpty(tree))
        return INT32_MAX;
    else
        return min(tree_elt(tree), min(tree_min(tree_left(tree)), tree_min(tree_right(tree))));
}

/**
 * @brief Recursively traversal the tree. If the tree is empty return a null list. Else return traversal(left tree) + current element + traversal(right tree).
 * 
 * @param tree The given tree to be traversaled.
 * @return list_t The result list.
 */
list_t traversal(tree_t tree){
    if (tree_isEmpty(tree))
        return list_make();
    else
        return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

/**
 * @brief Recursively determine whether there's pathSum = sum. If the tree is empty, obvously no root-to-leaf.
 * Else if current element = sum and it's leaf return false. Else return (left tree hasPathSum) or (right tree hasPathSum)
 * 
 * @param tree The given tree to be hasPathSumed.
 * @param sum The given sum.
 * @return true These's pathSum.
 * @return false There isn't pathSum.
 */
bool tree_hasPathSum(tree_t tree, int sum){
    if (tree_isEmpty(tree))
        return false;
    else if (tree_elt(tree) == sum && tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
        return true;
    else
        return (tree_hasPathSum(tree_left(tree), sum - tree_elt(tree)) || tree_hasPathSum(tree_right(tree), sum - tree_elt(tree)));
}

/**
 * @brief Implement "cover" exactly by the definition. The code I believe is obvious.
 * 
 * @param A Tree A
 * @param B Tree B
 * @return true Is covered.
 * @return false Isn't covered.
 */
bool covered_by(tree_t A, tree_t B){
    if (tree_isEmpty(A))
        return true;
    else if (tree_isEmpty(B))
        return false;
    else
        return (tree_elt(A) == tree_elt(B) && covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B)));
}
    
/**
 * @brief Implement "contained" exactly by the definition.
 * 
 * @param A Tree A
 * @param B Tree B
 * @return true Is contained.
 * @return false Isn't contained.
 */
bool contained_by(tree_t A, tree_t B){
    if (tree_isEmpty(B))
        return false;
    else
        return (covered_by(A, B) || contained_by(A, tree_left(B)) || contained_by(A, tree_right(B)));
}    


/**
 * @brief Insert a element to the tree so that the tree is still sorted. If tree is empty, this means we find where we should put the element.
 * Else if element < tree_elt(tree), this means the element will be inserted to the left tree, else means the element will be inserted to the right tree.
 * 
 * @param elt The given element to be inserted.
 * @param tree The given tree.
 * @return tree_t The new sorted tree.
 */
tree_t insert_tree(int elt, tree_t tree){
    if (tree_isEmpty(tree))
        return tree_make(elt, tree_make(), tree_make());
    else if (elt < tree_elt(tree))
        return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
    else
        return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
}