#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath> 
#include <vector> 
using namespace std;

/**
 * Generates a random number of length n.
 *
 * @param n the length of the number to generate
 *
 * @return the randomly generated number as a string
 *
 * @throws None
 */
string generate_random_number(int n) {
    string number;
    for (int i = 0; i < n; ++i) {
        int digit = 1 + rand() % 9; // Generate a random digit from 1 to 9
        number.push_back(digit + '0');
    }
    return number;
}


/**
 * Adds two strings representing numbers and returns the sum as a string.
 *
 * @param num1 the first string representing a number
 * @param num2 the second string representing a number
 *
 * @return the sum of the two numbers as a string
 *
 * @throws None
 */
string string_addition(const string& num1, const string& num2) {
    string result;
    long long carry = 0;
    long long i = num1.size() - 1;
    long long j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry != 0) {
        long long x = (i >= 0) ? num1[i] - '0' : 0;
        long long y = (j >= 0) ? num2[j] - '0' : 0;
        long long sum = x + y + carry;
        carry = sum / 10;
        sum %= 10;
        result.push_back(sum + '0');
        if (i >= 0) --i;
        if (j >= 0) --j;
    }

    reverse(result.begin(), result.end());
    return result;
}

/**
 * Adds zeros before a given string to make its length a multiple of 6.
 *
 * @param input_string the string to be modified
 *
 * @return the modified string with zeros added before it
 *
 * @throws None
 */
string add_zeros_before_string(string input_string) {
    int n = input_string.size();
    double div = n / 6.0;
    int i = 0;
    while (pow(3, i) < div) {
        i+=1;
    }
    int num_of_zeros = (6 * (pow(3, i))) - n;
    string result_string = string( num_of_zeros, '0').append(input_string);
    return result_string;
}


/**
 * Subtracts two strings representing non-negative integers and returns the result as a string.
 *
 * @param num1 the first non-negative integer as a string
 * @param num2 the second non-negative integer as a string
 *
 * @return the difference between num1 and num2 as a string
 *
 * @throws None
 */
string strings_substraction(const string& num1, const string& num2) {
    string result;
    int borrow = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
        int x = (i >= 0) ? num1[i] - '0' : 0;
        int y = (j >= 0) ? num2[j] - '0' : 0;
        int diff = x - y - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
        if (i >= 0) --i;
        if (j >= 0) --j;
    }

    reverse(result.begin(), result.end());
    // Remove leading zeros
    result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
    return result;
}

/**
 * Pads a given string with zeros to a specified length.
 *
 * @param num the string to be padded
 * @param zeros the number of zeros to be added
 *
 * @return the padded string
 *
 * @throws None
 */
string pad_zeros(const string& num, int zeros) {
    string paddedNum = num;
    for (int i = 0; i < zeros; ++i) {
        paddedNum.push_back('0');
    }
    return paddedNum;
}


/**
 * Removes leading zeros from a given string.
 *
 * @param num the string from which to remove leading zeros
 *
 * @return the modified string with leading zeros removed
 *
 * @throws None
 */
string remove_leading_zeros(const string& num) {
    string result = num;
    result.erase(0, min(result.find_first_not_of('0'), result.size() - 1));
    return result;
}


/**
 * Divides and conquers the multiplication of two small integers.
 *
 * @param A the first string representing the integer
 * @param B the second string representing the integer
 *
 * @return the result of the multiplication as a string
 *
 * @throws None
 */
string divide_and_conquer_multiplication_for_two_small_integers(const string& A, const string& B) {
    int n = max(A.size(), B.size());

    // Base case: if the input strings are small, perform regular multiplication
    if (n <= 3) {
        return to_string(stoll(A) * stoll(B));
    }

    int mid = n / 2;

    // Divide the input strings into two parts
    string x = A.substr(0, A.size() - mid);
    string y = A.substr(A.size() - mid);

    string a = B.substr(0, B.size() - mid);
    string b = B.substr(B.size() - mid);

    // Recursive calls for subproblems
    string p1 = divide_and_conquer_multiplication_for_two_small_integers(x, a);
    string p2 = divide_and_conquer_multiplication_for_two_small_integers(y, b);
    string p3 = divide_and_conquer_multiplication_for_two_small_integers(string_addition(x, y), string_addition(a, b));
    string p4 = strings_substraction(strings_substraction(p3, p1), p2);


    //padding zeros for abc and xyz
    string abc = pad_zeros(p1, 2 * mid);
    string xyz = pad_zeros(p4, mid);

    // Combine the results
    string result = string_addition(string_addition(pad_zeros(p1, 2 * mid), pad_zeros(p4, mid)), p2);
    return remove_leading_zeros(result);
}


/**
 * Divides the input strings into three parts and performs multiplication using divide and conquer algorithm.
 *
 * @param A the first input string
 * @param B the second input string
 *
 * @return the result of multiplication as a string
 *
 * @throws None
 */
string divide_and_conquer_multiplication_for_three_small_integers(const string& A, const string& B) {

    int n = max(A.size(), B.size());
    int mid = n / 3;

    // Base case: if the input strings are small, perform regular multiplication
    if (n <= 3) {
        return to_string(stoll(A) * stoll(B));
    }

    // Divide the input strings into three parts
    string x = A.substr(0, mid);
    string y = A.substr(mid, mid);
    string z = A.substr(2 * mid);

    string a = B.substr(0, mid);
    string b = B.substr(mid, mid);
    string c = B.substr(2 * mid);


    // Recursive calls for subproblems

    string p1 = divide_and_conquer_multiplication_for_three_small_integers(x, a);
    string p11 = pad_zeros(p1, 4 * mid);

    string p2_mid = divide_and_conquer_multiplication_for_three_small_integers(y, a);
    string p2_min = divide_and_conquer_multiplication_for_three_small_integers(x, b);
    string p2 = string_addition(p2_mid, p2_min);

    //padding zeros for p2
    string p22 = pad_zeros(p2, 3 * mid);

    string p6 = divide_and_conquer_multiplication_for_three_small_integers(x, c);
    string p7 = divide_and_conquer_multiplication_for_three_small_integers(y, b);
    string p8 = divide_and_conquer_multiplication_for_three_small_integers(z,a);
    
    //padding zeros for p66 , p77 and p88
    string p66 = pad_zeros(p6, 2 * mid);
    string p77 = pad_zeros(p7, 2 * mid);
    string p88 = pad_zeros(p8, 2 * mid);

    string p3_mid = divide_and_conquer_multiplication_for_three_small_integers(y, c);
    string p3_min = divide_and_conquer_multiplication_for_three_small_integers(z, b);

    //padding zeros for p33_mid and p33_min
    string p33_mid = pad_zeros(p3_mid, 1 * mid);
    string p33_min = pad_zeros(p3_min, 1 * mid);


    string p44 = divide_and_conquer_multiplication_for_three_small_integers(z, c);

    std::string result = string_addition(string_addition(string_addition(string_addition(p11, p22), p33_mid), p44), string_addition(p33_min, string_addition(p66, string_addition(p77, p88))));

    return remove_leading_zeros(result);

}


/**
 * Checks the similarity between three strings.
 *
 * @param resultOriginal the original string to compare against
 * @param resultModified the first modified string to compare
 * @param resultModifiedtwo the second modified string to compare
 *
 * @return void
 *
 * @throws None
 */
void check_similarity( const string& resultModified, const string& resultModifiedtwo) {
    if (resultModified == resultModifiedtwo) {
        cout << "They are the same!" << endl;
    } else {
        cout << "They are different!" << endl;
    }
}

/**
 * Main function that takes command line arguments and performs large integer multiplication using different algorithms.
 *
 * @param argc the number of command line arguments
 * @param argv an array of strings containing the command line arguments
 *
 * @return an integer indicating the success or failure of the program
 *
 * @throws None
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: ./main <n>" << endl;
        return 1;
    }

    string inputArg(argv[1]);

    if (inputArg == "0") {
        cout << "n must be a multiple of 6." << endl;
        return 1;
    }

    int n = stoi(inputArg);
    if (n % 6 != 0) {
        cout << "n must be a multiple of 6." << endl;
        return 1;
    }

    srand(time(0));
    string A = generate_random_number(n);
    string B = generate_random_number(n);

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;

    // Compute A * B using modified divide and conquer algorithm
    string resultModified = divide_and_conquer_multiplication_for_two_small_integers(A, B);
    cout << "A*B (The large integer multiplication from the division of two smaller integers is) = " << resultModified << endl;
    A = add_zeros_before_string(A);
    B = add_zeros_before_string(B);
    string resultModifiedtwo = divide_and_conquer_multiplication_for_three_small_integers(A, B);
    cout << "A*B (The large integer multiplication from the division of three smaller integers is) = " << resultModifiedtwo << endl;
    check_similarity( resultModified, resultModifiedtwo);

    return 0;
}

