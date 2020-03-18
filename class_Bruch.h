#include <iostream>

class Bruch {
public:
    // Constructor. Throws an exception when the user tries to set the denominator equal to zero.
    Bruch() {};

    Bruch(int zaehler,
          int nenner)
    {
        try
        {
            _zaehler = zaehler;
            if (nenner == 0)
            {
                throw std::invalid_argument("The denominator cannot equal 0");
            }
            _nenner = nenner;
        // make sure that the program continues, by letting the user input a nonzero integer for
        // the denominator
        } catch(std::invalid_argument err) {
            cout << "Enter a nonzero value for the denominator" << endl;
            cin >> nenner;
            _nenner = nenner;
        }
    }

    // Method that prints the zaehler and nenner.
    void print()
    {
        std::cout << _zaehler << " / " << _nenner << std::endl;
    }

    // Multiply with another Bruch. The 'const' declarations mean that neither the input nor the
    // original Bruch are modified, instead a new Bruch is returned.
    Bruch multiplizieren (const Bruch & bruch) const
    {
        return Bruch(_zaehler * bruch.get_zaehler(),
                     _nenner * bruch.get_nenner());
    }

    // Add to another Bruch.
    Bruch addieren (const Bruch & bruch) const
    {
        int zaehler = _nenner * bruch.get_zaehler() + _zaehler * bruch.get_nenner();
        int nenner = _nenner * bruch.get_nenner();
        return Bruch(zaehler, nenner);
    }

    // Simplify by dividing out the greatest common divisor
    void simplifizieren()
    {
        // if both the nominator and numerator are negative, multiply by -1
        if (_zaehler < 0 && _nenner < 0)
        {
            _zaehler *= -1;
            _nenner *= -1;
        }
        // Find gcd
        int g_c_d = gcd(_zaehler, _nenner);
        // reset _zaehler and _nenner by dividing out the gcd
        _zaehler = _zaehler / g_c_d;
        _nenner = _nenner / g_c_d;

        // print the result
        print();
    }

     // set() and get() methods.
    int get_zaehler() const
    {
        return _zaehler;
    }

    int get_nenner() const
    {
        return _nenner;
    }

    void set_zaehler(int zaehler)
    {
        _zaehler = zaehler;
    }

    void set_nenner(int nenner)
    {
       _nenner = nenner;
    }

private:
   int _zaehler;
   int _nenner;
};
