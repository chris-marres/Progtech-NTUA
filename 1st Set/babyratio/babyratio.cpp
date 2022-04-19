#include <iostream>
#ifndef CONTEST
#include "babyratio.hpp"
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

rational rational::add (rational r){

    rational a(nom * r.den, den * r.den);
    rational b(r.nom * den, r.den * den);

    return rational(a.nom + b.nom, a.den);
}

rational rational::sub (rational r){

    rational a(nom * r.den, den * r.den);
    rational b(r.nom * den, r.den * den);

    return rational(a.nom - b.nom, a.den);
}

rational rational::mul (rational r){
    return rational(nom * r.nom, den * r.den);
}

rational rational::div (rational r){
    return rational(nom * r.den, den * r.nom);
}

void rational::print (){
    int temp = gcd(abs(nom), den);
    cout << nom/temp << "/" << den/temp;
}

int rational::gcd (int a, int b){
    while (a > 0 && b > 0){
        if (a > b) a %= b;
        else b %= a;
    }
    return a + b;
}
