//This file's comments follow the regulation of doxygen, https://www.doxygen.nl/
/**
 * @file p1.cpp
 * @author Yichen Wei (ethepherein@sjtu.edu.cn)
 * @brief VE280 project1
 * @date 2021-10-05
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
 * @brief Given the information of whether the test if pass, will print (Pass / Fail).
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
    int maxTriangleNum = 2 * ceil(sqrt(integer));
    return binarySearchTriangle(1, maxTriangleNum, integer);
}

/**
 * @brief Determine whether a integer is a power number.
 * First find a factor of this integer, then check if this integer is only multiplied by this factor.
 * @param integer 
 * @return true The integer is a power number.
 * @return false The integer isn't a power number.
 */
bool ifPower(int integer){
    for (int i = 2; i <= ceil(sqrt(integer)); ++i){
        if (integer / i == 1)
            continue;
        if (integer % i == 0){
            int temp = integer;
            while (temp != 1){
                if (temp % i != 0)
                    break;
                temp = temp / i;
            }
            if (temp == 1)
                return true;
        }
    }
    return false;
}

/**
 * @brief sum[i] stores the square sum from 1 to i.
 * 
 */
unsigned long long sum[4000];

/**
 * @brief Using binary search method, given the left boundary: m, determine whether there exists a n that fits sum of squares.
 * @param m The left boundary of sum of squares.
 * @param left The current left boundary of n in binary search.
 * @param right The current right boundary of n in binary search.
 * @param integer The target integer.
 * @return true The integer is a sum of consecutive sqaures number.
 * @return false The integer isn't a sum of consecutive squares number with given m.
 */
bool binarySearchSquares(int m, int left, int right, int integer){
    if (left > right)
        return false;
    int mid = (left + right) / 2;
    if (sum[mid] - sum[m] == (unsigned long long)integer)
        return true;
    else if (sum[mid] - sum[m] > (unsigned long long)integer)
        return binarySearchSquares(m, left, mid - 1, integer);
    else
        return binarySearchSquares(m, mid + 1, right, integer);
}

/**
 * @brief Call binarySearchSqaures() with suitable initial value to check all the m, if it's a sum of consecutive square number.
 * @param integer The given interger.
 * @return true The integer is a sum of consecutive sqaures number.
 * @return false The integer isn't a sum of consecutive sqaures number.
 */
bool ifSumSquares(int integer){
    for (int i = 1; i < 4000; ++i)
        sum[i] = sum[i - 1] + i * i;
    int upperBound = ceil(sqrt(integer));
    for (int i = 1; i <= upperBound; ++i)
        if (binarySearchSquares(i - 1, i, upperBound, integer))
            return true;
    return false;
}

/**
 * @brief Determine whether a number is a abduntant number.
 * First find all the small divisors (smaller than sqrt(integer)), then add the small divisors and their corresponding big divisors. Compare the sum to the integer.
 * @param integer 
 * @return true The integer is a abdundant number.
 * @return false The integer isn't a abdundant number.
 */
bool ifAbdundant(int integer){
    int sum = 0;
    for (int i = 1; i <= floor(sqrt(integer)); ++i)
        if (integer % i == 0){
            sum += i;
            if (i != 1 && integer / i != i)
                sum += integer / i;
        }
    if (sum > integer)
        return true;
    else
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
            output(ifPower(integer));
            break;
        
        case 3:
            output(ifSumSquares(integer));
            break;

        case 4:
            output(ifAbdundant(integer));
            break;
    }
    return 0;
}