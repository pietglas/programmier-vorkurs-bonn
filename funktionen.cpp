// Script in which we collect the important functions that we'll need more often

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "Funktionen.h"
using namespace std;

// Use Euclid's algorithm to find the greatest common divisor of two integers
int gcd(int a, int b)
{
    // For the algorithm to work, we need to take the absolute value
    if (a < 0)
        a *= -1;
    if (b < 0)
        b *= -1;
    // do the algorithm
    while (a!=0 && b!=0)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }

    if (a == 0)
        return b;
    else
        return a;
}

// Calculate gcd of possibly more than two numbers.
int gcd_expanded(vector<int> numbers)
{
    // The case of two numbers uses the Euclidean algorithm, defined above.
    if (numbers.size() == 2)
    {
        return gcd(numbers[0], numbers[1]);
    }
    // In the case of more than 2 numbers, proceed by recursion, using
    // gcd(a, b, c) = gcd(gcd(a, b), c)
    else
    {
        // Locate the last element of the vector
        int last_postition = numbers.size() - 1;
        int last_elt = numbers[last_postition];
        // Remove the last element and proceed by recursion
        numbers.erase(numbers.begin() + last_postition);
        return gcd(gcd_expanded(numbers), last_elt);
    }
}


// Calculate the square root of a positive real number, using the Babel Approximation method
double square_root(double a, double error){
    double guess, lastguess, difference;
    guess = a;
    do {
        lastguess = guess;
        guess = (lastguess + a/lastguess)/2;
        // the algorithm that we implement is monotonic, so we could also go for the 'else-case'.
        if (guess - lastguess > 0) {
            difference = guess - lastguess;
        }
        else {
            difference = lastguess - guess;
        }
    } while (difference > error);

    return guess;
}

// The following function returns 1 if an integer is prime, 0 if it isn't. It is able to check integers
// upto 2147483647 = 2^31 - 1, the eight Mersenne prime.
int isprime(long n) {
    // First, check the first few numbers
    if (n==1 || n==4 || n==6)
        return 0;
    else if (n==2 || n==3 || n==5)
        return 1;
    else {
        // check whether n is divisible by 2 or 3
        if (n%2 == 0 || n%3 == 0)
            return 0;
        // Check for higher prime divisors
        else {
            // Calculate the square root of n using our own function
            double sqrt_n = square_root(n, 0.005);
            long k = 1;
            while ((6*k - 1) < sqrt_n || (6*k + 1) < sqrt_n) {
                if (n % (6*k - 1) == 0 || n % (6*k + 1) == 0) {
                    return 0;
                    break;
                }
                else
                    k += 1;

            }
            return 1;
        }
    }
}

// The following function takes as input a positive integer n, and returns a vector
// containing all prime numbers up to and including n. We choose a vector because they are more dynamic
// than arrays: arrays cannot be declared without size.
// Note: the reason this is possible, is that vectors are allocated more memory than they actually
// need. Thus, in case we don't need to add elements, it is always better to work with arrays.
vector<int> primevector(long n) {
    vector<int> sequence;
    int m = 2;
    int ctr = 1;
    while (m <= n) {
        if (isprime(m)==1) {
            sequence.push_back(m);
        }
        if (m==2)
            m += 1;
        else if (m==3)
            m += 2;
        // We only need to check all number of the form 6k +- 1 with k a positive integer,
        // smaller or equal than n.
        else if (m==(6*ctr - 1))
            m += 2;
        else {
            m += 4;
            ctr += 1;
        }
    }

    return sequence;
}

// Function to calculate n factorial, i.e. n! for nonnegative integers n.
int factorial(int n) {
    int result;
    if (n == 0)
        result = 1;
    else {
        result = 1;
        for (int i=1; i <= n; i++) {
            result *= i;
        }
    }
    return result;
}

// Fuction that calculate the binomial coefficients
int binomial(int n, int k) {
    int result;
    // treat the case k > n
    if (k > n)
        result = 0;
    else {
        int nfact = factorial(n);
        int kfact = factorial(k);
        int nkfact = factorial(n - k);
        result = nfact / (kfact * nkfact);
    }
    return result;
}

// Function that that returns the n-th Bell number B_n
int Bell(int n) {
    // Declare a vector which will contain the B_0,.., B_{n-1}. For n > 0, the B_i occur more often.
    // Making a list ensures that we only have to calculate each Bell number once.
    vector<int> bellvector;
    int bellnr;
    // The case n = 0
    bellnr = 1;
    bellvector.push_back(bellnr);
    // Calculate higher Bell numbers.
    for (int i=1; i <= n; i++) {
        bellnr = 0;
        for (int j = 0; j <= i - 1; j++) {
            bellnr += binomial(i - 1, j) * bellvector[j];
        }
        bellvector.push_back(bellnr);
    }
    return bellvector[n];
}

// Double-and-Add-Method, recursive.
double natural_power(double x, int n) {
    if (n==0)
        return 1;
    else if (n==1)
        return x;
    else if (n==2)
        return x*x;
    else if ((n % 2) == 1)
        return x * natural_power(x*x, (n-1) / 2);
    else
        return natural_power(x*x, n / 2);
}

// Double-and-Add, without recursion. Only slightly slower than the one with recursion.
double power_alt(double x, int n) {
    // set variables
    int k = 1;
    double y = x;
    double result = 1;
    // the result will be calculated via the 2-adic expansion of n. We count down until n=0.
    // Example: x^7 = x^1 * x^2 * x^4, 7 = 1 + 6 = 1 + 2*3 = 1 + 2 + 2*2
    while (n > 0) {
        // divide n by 2 until either n = 2 or n is odd, say k times, giving the factor
        // x^(2^k). If n = 2, take square and break the loop. if n is odd, multiply result with
        // the factor and subtract 1 from n (see example).
        if ((n % 2) == 0 && n != 2) {
            n /= 2;
            y *= y;
            k *= 2;
        }
        else if (n == 2) {
            y *= y;
            result *= y;
            break;
        }
        else {
            result *= y;
            n -= 1;
        }
    }

    return result;
}

// Function that returns an approximation of e^x, where x is real, using a Taylor expansion
// e^x = infsum(x^k / k!)
double expo(double x, double error) {
    // Declare summands and sum
    double summand, sum;
    int k;
    sum = 0;

    // Calculate the infinite sum by a finite approximation
    for (k = 0; ;k++) {
        summand = natural_power(x, k) / factorial(k);
        // break of the summation when the summands become smaller than the error
        if (summand < error)
            break;
        sum += summand;
    }
    return sum;
}

// Function that returns an approximation of ln(x), where x is a positive real number.
double ln(double x, double error) {
    double summand, sum;
    int k;
    sum = 0;

    // Check for valid input
    if (x <= 0) {
        cout << "Invalid input: the logarithm is not defined for negative x." << endl;
        return 0;
    }
    double X = (x - 1) / (x + 1);
    // Calculate an approximation of the infinite sum
    for (k = 0; ;k++) {
        summand = natural_power(X, 2*k + 1) * 2 / (2*k + 1);
        if (summand < error)
            break;
        sum += summand;
    }
    return sum;
}

// Function that returns x^y, where x is real and nonnegative, y real.
double real_power(double x, double y, double error) {
    double power = y * ln(x, error);
    double result = expo(power, error);

    return result;
}

// Calculate the n-th fibonacci number recursively. Computational cost is (golden_ratio)^{n - 1}.
unsigned fibonacci_naiv(unsigned n) {
    if (n < 2)
        return 1;
    else
        return fibonacci_naiv(n - 1) + fibonacci_naiv(n - 2);
}

// Calculate the n-th fibonacci number, by computing all fibonacci numbers preceding it and saving them
// in a vector. Computational cost is 2n.
unsigned fibonacci(unsigned n) {
    vector<int> fib_vector;
    // Add the first two elements of the fibonacci sequence to the vector
    for (int i = 0; i <= 1; i++)
        fib_vector.push_back(1);
    // Add the remaining elements
    for (int j = 2; j <= n; j++) {
        int f_j;
        f_j = fib_vector[j - 1] + fib_vector[j - 2];
        fib_vector.push_back(f_j);
    }
    return fib_vector[n];

}

// Function that returns the smallest number in a vector. Since vectors are large, we avoid making a
// copy when we pass the argument by reference. Since the function won't change the vector, we pass
// by constant reference.
unsigned * minimum(const vector<unsigned> &numbers) {
    unsigned temp_min, minvalue;
    temp_min = *numbers.begin();
    int k = 0;
    int position = 0;
    // compare the first value with the next values. Change it if a smaller value is found.
    // For practice, use iterators.
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (temp_min > *it) {
            temp_min = *it;
            position = k;
        }
        // If 0 is found, we don't need to continue further
        if (temp_min == 0)
            break;
        k += 1;
    }
    minvalue = temp_min;
    // Declare a pointer
    unsigned * arr;
    // Use of malloc makes sure the memory is freed on the heap instead of the stack.
    // Memory needs to be emptied later to prevent leaks, using free(arr).
    arr = (unsigned*) malloc(2);
    // Check whether the memory allocation was successful
    if (!arr) {
        cout << "Memory allocation failed" << endl;
        exit(1);
    }
    // The array will be the minimum value and its position in the vector
    arr[0] = minvalue;
    arr[1] = position;
    return arr;
}

// Function that returns the minimum value above a threshold in a vector.
unsigned * relative_minimum(const vector<unsigned> &numbers, unsigned threshold) {
    unsigned temp_min = 0;
    unsigned minvalue;
    // Integers to keep track of positions
    unsigned temp_pos, pos;
    // Search for a number larger than the threshold
    for (int k=0; k < numbers.size(); k++) {
        if (numbers[k] > threshold) {
            temp_min = numbers[k];
            temp_pos = k;
            //cout << "We found " << temp_min << " at position " << temp_pos << endl;
            break;
        }
    }
    // If there is no number larger than the threshold, print this message and return 0
    if (temp_min == 0) {
        cout << "There is no value larger than the threshold in this vector." << endl;
        return 0;
    }
    // Declare the pointer
    unsigned * arr;
    // Use of malloc makes sure the memory is freed on the heap instead of the stack.
    // Memory needs to be emptied later to prevent leaks, using free(arr).
    arr = (unsigned*) malloc(2);
    // Check whether the memory allocation was successful
    if (!arr) {
        cout << "Memory allocation failed" << endl;
        exit(1);
    }
    // If the value found is 1 larger than the threshold, we are done.
    else if (temp_min == (threshold + 1)) {
        minvalue = temp_min;
        pos = temp_pos;
        arr[0] = minvalue;
        arr[1] = pos;

        return arr;
    }
    // compare the first value with the next values. Change it if a smaller value is found.
    else {
        for (int i = temp_pos; i < numbers.size(); i++) {
            if (temp_min > numbers[i] && numbers[i] > threshold) {
                temp_min = numbers[i];
                temp_pos = i;
                //cout << temp_pos << endl;
            }
        }
        minvalue = temp_min;
        pos = temp_pos;
        // The array will be the minimum value and its position in the vector
        arr[0] = minvalue;
        arr[1] = pos;

        return arr;
    }
}

// Function takes a vector with nonnegative integers, and returns a vector of the same size,
// containing the same values but sorted in ascending order.
// Performance issues: takes about 60 seconds to sort a vector of size 1e5, whereas std::sort()
// Only takes 3 seconds.
vector<unsigned> sort_vector(const vector<unsigned> &numbers) {
    vector<unsigned> numbers_sorted;
    unsigned m = numbers.size();
    unsigned minvalue, stlminvalue, position;
    unsigned ctr;
    while (m > 0) {
        ctr = 0;
        if (m == numbers.size())
            {
            // Declare pointer for the minimum value
            unsigned * ptr;
            ptr = minimum(numbers);
            // Check whether the pointer assignment was successful
            if (ptr == nullptr) {
                cout << "A nullpointer was assigned" << endl;
                exit(1);
            }
            minvalue = ptr[0];
            position = ptr[1];
            // Count how often the minimum value is contained in the vector, and add the minimum
            // value that much times to the sorted vector.
            for (unsigned i = position; i < numbers.size(); i++)
            {
                if (minvalue == numbers[i])
                {
                    numbers_sorted.push_back(minvalue);
                    ctr += 1;
                    //cout << ctr << endl;
                }
            }
            m -= ctr;
            // Empty the memory allocated earlier
            free(ptr);
        }
        else
        {
            minvalue = numbers_sorted[numbers.size() - m - 1];
            // Declare a pointer for the function relative_minimum().
            unsigned * ptr;
            ptr = relative_minimum(numbers, minvalue);
            // Check whether the pointer assignment was successful
            if (ptr == nullptr) {
                cout << "A nullpointer was assigned" << endl;
                exit(1);
            }
            stlminvalue = ptr[0];
            position = ptr[1];
            // Count how often the nth to last minimum value is contained in the vector, and add the
            // minimum value that much times to the sorted vector.
            for (unsigned i = position; i < numbers.size(); i++)
            {
                if (stlminvalue == numbers[i])
                {
                    numbers_sorted.push_back(stlminvalue);
                    ctr += 1;
                    //cout << ctr << endl;
                }
            }
            m -= ctr;
            // Empty the memory allocated earlier
            free(ptr);
        }
    }
    return numbers_sorted;
}

// Function that prints the elements of a vector from first to last element.
void printvec(const vector<int> &numbers) {
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << ", ";
    }
}

// Function that reads numbers from a text file and stores them into a vector
vector<int> nrs_from_txt(string path)
{
    vector<int> numbers;

    // declare ifstream object to read from text file
    ifstream file;
    file.open(path);

    // Check that the file was opened
    if (!file)
    {
        cout << "Unable to open file" << path;
        exit(1);
    }
    else
    {
        int number;
        // Collect numbers from file and add them to the vector, one by one
        while (file >> number)
        {
            numbers.push_back(number);
        }
    }

    return numbers;
}
