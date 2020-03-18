#ifndef FUNKTIONEN_H
#define FUNKTIONEN_H
#include<vector>
#include<string>
using namespace std;

// Use Euclid's algorithm to find the greatest common divisor of two integers
int gcd(int a, int b);

// Calculate gcd of possibly more than two numbers.
int gcd_expanded(vector<int> numbers);

// Calculate the square root of a positive real number, using the Babel Approximation method
double square_root(double a, double error);

// The following function returns 1 if an integer is prime, 0 if it isn't. It is able to check integers
// upto 2147483647 = 2^31 - 1, the eight Mersenne prime.
int isprime(long n);

// The following function takes as input a positive integer n, and returns a vector
// containing all prime numbers up to and including n. We choose a vector because they are more dynamic
// than arrays: arrays cannot be declared without size.
// Note: the reason this is possible, is that vectors are allocated more memory than they actually
// need. Thus, in case we don't need to add elements, it is always better to work with arrays.
vector<int> primevector(long n);

// Function to calculate n factorial, i.e. n! for nonnegative integers n.
int factorial(int n);

// Fuction that calculate the binomial coefficients
int binomial(int n, int k);

// Function that that returns the n-th Bell number B_n
int Bell(int n);

// Double-and-Add-Method, recursive.
double natural_power(double x, int n);

// Double-and-Add, without recursion. Only slightly slower than the one with recursion.
double power_alt(double x, int n);

// Function that returns an approximation of e^x, where x is real, using a Taylor expansion
// e^x = infsum(x^k / k!)
double expo(double x, double error);

// Function that returns an approximation of ln(x), where x is a positive real number.
double ln(double x, double error);

// Function that returns x^y, where x is real and nonnegative, y real.
double real_power(double x, double y, double error);

// Calculate the n-th fibonacci number recursively. Computational cost is (golden_ratio)^{n - 1}.
unsigned fibonacci_naiv(unsigned n);

// Calculate the n-th fibonacci number, by computing all fibonacci numbers preceding it and saving them
// in a vector. Computational cost is 2n.
unsigned fibonacci(unsigned n);

// Function that returns the smallest number in a vector. Since vectors are large, we avoid making a
// copy when we pass the argument by reference. Since the function won't change the vector, we pass
// by constant reference.
unsigned * minimum(const vector<unsigned> &numbers);

// Function that returns the minimum value above a threshold in a vector.
unsigned * relative_minimum(const vector<unsigned> &numbers, unsigned threshold);

// Function takes a vector with nonnegative integers, and returns a vector of the same size,
// containing the same values but sorted in ascending order.
// Performance issues: takes about 60 seconds to sort a vector of size 1e5, whereas std::sort()
// Only takes 3 seconds.
vector<unsigned> sort_vector(const vector<unsigned> &numbers);

// Function that prints the elements of a vector from first to last element.
void printvec(const vector<int> &numbers);

// Function that reads numbers from a text file and stores them into a vector
vector<int> nrs_from_txt(string path);

#endif // FUNKTIONEN_H


