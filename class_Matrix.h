#include <iostream>
#include <vector>

template<class T>
using row = std::vector<T>;

template<class T>
class Matrix
{
public:
    // Constructors.
    Matrix() {};

    // Creates n x n unit matrix
    Matrix(unsigned n): _num_rows(n), _num_columns(n), _entries(n)
    {
        T zero(0);
        T one(1);
        for (unsigned i = 0; i < _num_rows; i++)
        {
            for (unsigned j = 0; j < _num_columns; j++)
            {
                if (i == j)
                {
                    (_entries[i]).push_back(one);
                }
                else
                {
                    (_entries[i]).push_back(zero);
                }
            }
        }
    }

    // Creates m x n zero matrix
    Matrix(unsigned m, unsigned n):
       _num_rows(m),
       _num_columns(n),
       _entries(m)
    {
       T zero(0);
       for(unsigned i = 0; i < _num_rows; i++)
       {
          for(unsigned j = 0; j < _num_columns; j++)
          {
             (_entries[i]).push_back(zero);
          }
       }
    }

    Matrix(unsigned m, unsigned n, vector<double> values):
       _num_rows(m),
       _num_columns(n),
       _entries(m)
    {
       for(unsigned i = 0; i < _num_rows; i++)
       {
          for(unsigned j = 0; j < _num_columns; j++)
          {
             (_entries[i]).push_back(values[i*_num_columns + j]);
          }
       }
    }

    // get methods
    T get_entry(unsigned i, unsigned j) const {
       // Check whether the index 'exist' for this matrix
       try
       {
           if (i >= _num_rows || j >= _num_columns)
           {
               throw std::invalid_argument("index out of range");
           }
       } catch (std::invalid_argument err) {
             cout << "The following index is out of range: ";

             if (i >= _num_rows)
             {
                 cout << i << endl;
                 cout << "Enter a new value: ";
                 cin >> i;
             }

             if (j >= _num_columns)
             {
                 cout << j << endl;
                 cout << "Enter a new value: ";
                 cin >> j;
             }
       }
       return _entries[i][j];
    }

    unsigned get_num_rows() const {
       return _num_rows;
    }

    unsigned get_num_columns() const {
       return _num_columns;
    }

    // set method
    T set_entry(unsigned i, unsigned j, T value) {
       return _entries[i][j] = value;
    }

    // Print the entries
    void print() {
       std::cout << _num_rows << " Rows and " << _num_columns << " Columns:" << std::endl;
       for(unsigned i = 0; i < _num_rows; i++)
       {
          for(unsigned j = 0; j < _num_columns; j++)
          {
             std::cout << _entries[i][j];
          }
          std::cout << std::endl;
       }
    }

    // Define matrix addition
    Matrix<T> operator+ (const Matrix<T> & other) const
    {
        try
        {
            if (_num_columns != other._num_columns || _num_rows != other._num_rows)
                throw std::invalid_argument("dimensions don't match");

            Matrix<T> sum(_num_rows, _num_columns);
            for (unsigned i = 0; i < _num_rows; i++)
            {
                for (unsigned j = 0; j < _num_columns; j++)
                {
                    T entrysum = get_entry(i, j) + other.get_entry(i, j);
                    sum.set_entry(i, j, entrysum);
                }
            }
            return sum;
        } catch(std::invalid_argument err) {
            cout << "The dimensions of these matrices don't match";
            exit(1);
        }
    }

    // Define matrix multiplication
    Matrix<T> operator* (const Matrix<T> & other) const {
       try
       {
          if (_num_columns != other._num_rows)
             throw std::invalid_argument("dimensions don't match");

          Matrix<T> result(_num_rows, other._num_columns);
          for(unsigned i = 0; i < _num_rows; i++) {
          for(unsigned j = 0; j < other._num_columns; j++)
          {
             T entry(0);
             for(unsigned k = 0; k < _num_rows; k++) {
                entry += _entries[i][k] * other._entries[k][j];
             }
             result.set_entry(i, j, entry);
          }
       }
       return result;
       } catch(std::invalid_argument err) {
             cout << "The dimension don't of these matrices don't match";
             exit(1);
       }
    }

    // Define the transpose of a matrix
    Matrix<T> transpose() const
    {
        Matrix<T> transpose(_num_columns, _num_rows);
        for (int i = 0; i < _num_columns; i++)
        {
            for (int j = 0; j < _num_rows; j++)
            {
                transpose.set_entry(i, j, _entries[j][i]);
            }
        }

        return transpose;
    }

    // Define the conjugate of a matrix, in the complex case
    Matrix<Complexnr> conjugate()
    {
        Matrix<Complexnr> conjugate(_num_rows, _num_columns);
        for (int i = 0; i < _num_rows; i++)
        {
            for (int j = 0; j < _num_columns; j++)
            {
                Complexnr conj;
                conj = _entries[i][j].conjugate();
                conjugate.set_entry(i, j, conj);
            }
        }

        return conjugate;
    }


private:
    unsigned  _num_rows;
    unsigned  _num_columns;
    std::vector<row<T>> _entries;
};


