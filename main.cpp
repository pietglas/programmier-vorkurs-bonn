#include<iostream>
#include<fstream>
#include<vector>
#include<string>

#include "funktionen.h"
#include "class_Bruch.h"
#include "class_Polynom.h"
#include "class_Complexnr.h"
#include "class_Matrix.h"

#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;


int main() {
    Matrix<Complexnr> mtx1(2, 2);
    Matrix<Complexnr> mtx2(2);
    Complexnr z(1, 1);
    mtx1.set_entry(0, 0, z);
    mtx1.set_entry(0, 1, 1);
    //mtx1.print();
    //mtx2.print();
    Matrix<Complexnr> mtx3;
    mtx3 = mtx1 * mtx2;
    mtx3.print();
    Matrix<Complexnr> mtx4;
    mtx4 = mtx3.transpose().conjugate();
    mtx4.print();

    return 0;
}
