#include<iostream>
#include<vector>

using namespace std;

// Class template for polynomials of 1 variable and arbitrary degree. We can specialize to allow
// for different types of coefficients.
template <class T>
class Polynom {
private:
    // The following members are automatically set to be only privately accessible
    int deg;
    vector<T> coeffs;
public:
    // Constructors
    Polynom() {};

    Polynom(int degree, vector<T> coefficients)
    {
        deg = degree;
        coeffs = coefficients;
    }

    // get methods. Must be set to 'const', otherwise the compiler interprets them as possibly
    // changing the members of the class they belong to; That would cause a conflict with other
    // member functions which are set 'const', i.e. which won't modify the class members.
    int get_deg() const {return deg;}

    T get_ith_coeff(int i) const {return coeffs[i];}

    // set methods
    void set_deg(int degree) {deg = degree;}

    void set_ith_coeff(int i, T coeff_i) {coeffs[i] = coeff_i;}

    // Print the polynomial
    void print()
    {
        cout << get_ith_coeff(0) << " + ";
        //cout << coeffs[0] << " + ";
        for (int i=1; i < deg; i++)
        {
            cout << get_ith_coeff(i) << "x^" << i << " + ";
            //cout << coeffs[i] << "x^" << i << " + ";
        }
        cout << get_ith_coeff(deg) << "x^" << deg << endl;
        //cout << coeffs[deg] << "x^" << deg << endl;
    }

    // Add another polynomial to this one. Function cannot be set 'const' is it might have to
    // change the coefficient vector.
    Polynom<T> addition(Polynom<T> & pol)
    {
        int degree;
        vector<T> coefficients;
        // Calculate degree, Add 0's to the coefficient vector of the polynomial with the lowest degree.
        if (deg <= pol.get_deg())
        {
            // Set degree
            degree = pol.get_deg();
            // Add 0's
            for (int i = (deg + 1); i <= pol.get_deg(); i++)
            {
                coeffs.push_back(0);
            }
        }
        else
        {
            // Set degree
            degree = deg;
            // Add 0's
            for (int i = pol.get_deg()+1; i <= deg; i++)
            {
                pol.set_ith_coeff(i, 0);
            }
        }
        coefficients.reserve(3);

        // Calculate coefficients
        for (int i = 0; i <= degree; i++)
        {
            T coeff = coeffs[i] + pol.get_ith_coeff(i);
            coefficients.push_back(coeff);
        }
        Polynom<T> pol2(degree, coefficients);
        return pol2;
    }

    // Multiply this polynomial with another one.
    Polynom<T> multiplication(Polynom<T> & pol)
    {
        int degree;
        vector<T> coefficients;

        // calculate degree
        degree = deg + pol.get_deg();

        // Add 0's
        for (int i = (deg + 1); i <= degree; i++)
        {
            coeffs.push_back(0);
        }

        for (int i = pol.get_deg()+1; i <= degree; i++)
        {
            pol.set_ith_coeff(i, 0);
        }

        // Calculate coefficients
        for (int i = 0; i <= degree; i++)
        {
            T coeff_sum = 0;
            for (int j = 0; j <= i; j++)
            {
                coeff_sum += coeffs[j] * pol.get_ith_coeff(i - j);
            }
            coefficients.push_back(coeff_sum);
        }

        return Polynom(degree, coefficients);
    }

};
