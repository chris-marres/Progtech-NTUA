#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
#endif

using namespace std;

int abs(int a) {return (a >= 0) ? a : -a;}
bool isNegative (int nom, int den) {return ((nom < 0 && den > 0) || (nom > 0 && den < 0)) ? true : false;}

rational::rational (int n, int d){
    if (isNegative(n, d)){
        nom = -abs(n);
        den = abs(d);
    }
    else{
        nom = abs(n);
        den = abs(d);
    }
}

rational operator + (const rational &x, const rational &y){
    rational a(x.nom * y.den, x.den * y.den);
    rational b(y.nom * x.den, y.den * x.den);

    return rational(a.nom + b.nom, a.den);
}

rational operator - (const rational &x, const rational &y){
    rational a(x.nom * y.den, x.den * y.den);
    rational b(y.nom * x.den, y.den * x.den);

    return rational(a.nom - b.nom, a.den);
}

rational operator * (const rational &x, const rational &y){
    return rational(x.nom * y.nom, x.den * y.den);
}

rational operator / (const rational &x, const rational &y){
    return rational(x.nom * y.den, x.den * y.nom);
}

int rational::gcd (int a, int b){
    while (a > 0 && b > 0){
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}

ostream & operator << (std::ostream &out, const rational &x){
    int temp = rational::gcd(abs(x.nom), x.den);
    return out << x.nom/temp << "/" << x.den/temp; 
}