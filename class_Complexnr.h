#include<iostream>
#include<string>

class Complexnr {
    double realpart, complexpart;
public:
    // Constructors
    Complexnr() {};

    Complexnr(double x): realpart(x), complexpart(0) {};

    Complexnr(double x, double y): realpart(x), complexpart(y) {};

    // get methods
    double get_realpart() const {return realpart;}

    double get_complexpart() const {return complexpart;}

    // set methods
    void set_realpart(double x) {realpart = x;}

    void set_complexpart(double y) {complexpart = y;}

    // print method
    void print() const
    {
        cout << realpart << " + " << complexpart << "i" << endl;
    }

    // Function that returns the conjugate.
    Complexnr conjugate()
    {
        if (complexpart == 0) return *this;

        else
        {
            double cplxpart = (-1)*complexpart;
            Complexnr conj(realpart, cplxpart);
            return conj;
        }
    }

    // Overload addition
    Complexnr operator + (const Complexnr & z) const
    {
        double realpt, comppt;
        realpt = realpart + z.get_realpart();
        comppt = complexpart + z.get_complexpart();
        Complexnr sum(realpt, comppt);

        return sum;
    }

    // Overload subtraction
    Complexnr operator - (const Complexnr & z) const
    {
        double realpt, comppt;
        realpt = realpart - z.get_realpart();
        comppt = complexpart - z.get_complexpart();
        Complexnr difference(realpt, comppt);

        return difference;
    }

    // Overload multiplication
    Complexnr operator * (const Complexnr & z) const
    {
        double realpt, comppt;
        realpt = (realpart * z.get_realpart()) - (complexpart * z.get_complexpart());
        comppt = (realpart * z.get_complexpart()) + (complexpart * z.get_realpart());
        Complexnr product(realpt, comppt);

        return product;
    }

    // Overload division
    Complexnr operator / (const Complexnr & z) const
    {
        // Throw exception when the user tries to divide by zero
        try
        {
            if (z.get_realpart() == 0 && z.get_complexpart() == 0)
            {
                throw std::runtime_error("You cannot divide by zero");
            }
            double realpt, comppt;
            Complexnr quotient;
            // calculate real and complex part
            realpt = z.get_realpart() /
                    (natural_power(z.get_realpart(), 2) + natural_power(z.get_complexpart(), 2));
            comppt = z.get_complexpart() /
                    (natural_power(z.get_realpart(), 2) + natural_power(z.get_complexpart(), 2));

            // Define return value
            Complexnr divisor(realpt, comppt);
            quotient = (*this) * divisor;

            return quotient;
        } catch (std::runtime_error err) {
            // Let the user enter a nonzero complex number
            cout << "You are trying to divide by zero" << endl;
            exit(1);
        }
    }

    // Overload +=
    Complexnr& operator+= (const Complexnr & z)
    {
        *this = *this + z;
        return *this;
    }
};

// Overload << for complex numbers
void operator<<(ostream & os, const Complexnr & z)
{
    z.print();
}



