//This file's comments follow the regulation of doxygen, https://www.doxygen.nl/
/**
 * @file p1.cpp
 * @author Yichen Wei (ethepherein@sjtu.edu.cn)
 * @brief VE280 project1
 * @version 0.1
 * @date 2021-09-28
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
/**
 * @brief Handles the given input. Ask to input again if input is invalid.
 * @param integer The integer that needs to be [0, 1e7]
 * @param number The number that needs to be {1, 2, 3, 4}
 */
void input(int &integer, int &number){
    while (integer < 1 || integer > (int)1e7 || number < 1 || number > 4){
        cout << "Please enter the integer and the test choice: ";
        cin >> integer >> number;
    }
}
/**
 * @brief Given the information of whether the test if pass, will prrint (Pass / Fail).
 * @param ifPass The ifPass indicates whether the test is past.
 */
void output(bool ifPass){
    cout << (ifPass ? "Pass" : "Fail") << endl;
}

/**
 * @brief Using binary search method, determine whether a integer is a triangle number.
 * @param left The left boundary in binary search.
 * @param right The right boundary in binary search.
 * @param integer The target integer number.
 * @return true: The integer is a triangle number.
 * @return false: The integer isn't a triangle number.
 */
bool binarySearchTriangle(int left, int right, int integer){
    if (left > right)
        return false;
    int mid = (left + right) / 2;
    if (mid * (mid + 1) / 2 == integer)
        return true;
    else if (mid * (mid + 1) / 2 > integer)
        return binarySearchTriangle(left, mid - 1, integer);
    else
        return binarySearchTriangle(mid + 1, right, integer);
}

/**
 * @brief Call binarySearchTriangle() with suitable initial value to help determine whether a integer is a triangle number.
 * By calculating, we find that the upper bound should be around 2*sqrt(integer).
 * @see binarySearchTriangle()
 * @param integer The target integer number.
 * @return true: The integer is a triangle number.
 * @return false: The integer isn't a triangle number.
 */
bool ifTriangle(int integer){
    return binarySearchTriangle(1, 2 * ceil(sqrt(integer)), integer);
}

/**
 * @brief Determine whether a integer is a power number.
 * First find the minimum prime factor of this integer, then see if this integer is only multiplied by this minimum prime factor.
 * @param integer 
 * @return true 
 * @return false 
 */
bool ifPowerNumber(int integer){
    for (int i = 2; i <= ceil(sqrt(integer)); ++i)
        if (integer % i == 0){
            while (integer != 1){
                if (integer % i != 1)
                    return false;
                integer = integer / i;
            }
            return true;
        }
    return false;
}
/**
 * @brief The main function.
 * @return int 
 */
int main(){
    int integer = 0, number = 0;
    input(integer, number);
    switch (number){
        case 1:
            output(ifTriangle(integer));
            break;

        case 2:
            output(ifPowerNumber(integer));
            break;
    }
    return 0;
}