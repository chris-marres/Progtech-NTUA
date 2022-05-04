#include <iostream>
#include <cmath>
using namespace std;
class Polynomial {
    protected:
        class Term {
            public:
                int exponent;
                int coefficient;
                Term *next;
                Term(int exp, int coeff, Term *n);
                friend class Polynomial;
        };

    public:
        Polynomial();
        Polynomial(const Polynomial &p);
        ~Polynomial();

        Polynomial & operator = (const Polynomial &p);

        void addTerm(int expon, int coeff);
        double evaluate(double x);

        friend Polynomial operator+ (const Polynomial &p, const Polynomial &q);
        friend Polynomial operator* (const Polynomial &p, const Polynomial &q);

        friend ostream & operator << (ostream &out, const Polynomial &p);     


    private:
        Term *head;
};

Polynomial::Term::Term(int exp, int coeff, Term *n) {
    exponent = exp;
    coefficient = coeff;
    next = n;
}

Polynomial::Polynomial() {
    head = NULL;
}

Polynomial::Polynomial(const Polynomial &p) {
    head = NULL;
    Term *p1 = p.head;
    while (p1 != NULL) {
        addTerm(p1->exponent, p1->coefficient);
        p1 = p1->next;
    }
}

Polynomial::~Polynomial() {
    Term *p_ptr = head;
    while (p_ptr != NULL) {
        Term *temp = p_ptr;
        p_ptr = p_ptr->next;
        delete temp;
    }
}

Polynomial & Polynomial::operator = (const Polynomial &p) {
    head = NULL;
    Term *p1 = p.head;
    while (p1 != NULL) {
        addTerm(p1->exponent, p1->coefficient);
        p1 = p1->next;
    }
    return *this;
}

void Polynomial::addTerm(int expon, int coeff) {
    Term *p_ptr = head;
    Term *prev = NULL;
    if (coeff == 0) {
        return;
    }
    while (p_ptr != NULL && p_ptr->exponent > expon) {
        prev = p_ptr;
        p_ptr = p_ptr->next;
    }
    if (p_ptr == NULL || p_ptr->exponent != expon) {
        Term *temp = new Term(expon, coeff, p_ptr);
        if (prev == NULL) {
            head = temp;
        }
        else{
            prev->next = temp;
        }
    }
    else{
        p_ptr->coefficient += coeff;
        if (p_ptr->coefficient == 0) {
            if (prev == NULL) {
                head = p_ptr->next;
            }
            else{
                prev->next = p_ptr->next;
            }
            delete p_ptr;
        }
    }
}

double Polynomial::evaluate(double x) {
    Term *p_ptr = head;
    double sum = 0;
    while (p_ptr != NULL) {
        sum += p_ptr->coefficient * pow(x, p_ptr->exponent);    
        p_ptr = p_ptr->next;
    }
    return sum;
}

Polynomial operator+ (const Polynomial &p, const Polynomial &q) {
    Polynomial sum;
    Polynomial::Term *p_ptr = p.head;
    Polynomial::Term *q_ptr = q.head;
    while (p_ptr != NULL && q_ptr != NULL) {
        if (p_ptr->exponent > q_ptr->exponent) {
            sum.addTerm(p_ptr->exponent, p_ptr->coefficient);
            p_ptr = p_ptr->next;
        }
        else if (p_ptr->exponent < q_ptr->exponent) {
            sum.addTerm(q_ptr->exponent, q_ptr->coefficient);
            q_ptr = q_ptr->next;
        }
        else {
            sum.addTerm(p_ptr->exponent, p_ptr->coefficient + q_ptr->coefficient);
            p_ptr = p_ptr->next;
            q_ptr = q_ptr->next;
        }
    }
    while (p_ptr != NULL) {
        sum.addTerm(p_ptr->exponent, p_ptr->coefficient);
        p_ptr = p_ptr->next;
    }
    while (q_ptr != NULL) {
        sum.addTerm(q_ptr->exponent, q_ptr->coefficient);
        q_ptr = q_ptr->next;
    }
    return sum;
}

Polynomial operator* (const Polynomial &p, const Polynomial &q) {
    Polynomial product;
    Polynomial::Term *p_ptr = p.head;
    while (p_ptr != NULL) {
        Polynomial::Term *q_ptr = q.head;
        while (q_ptr != NULL) {
            product.addTerm(p_ptr->exponent + q_ptr->exponent, p_ptr->coefficient * q_ptr->coefficient);
            q_ptr = q_ptr->next;
        }
        p_ptr = p_ptr->next;
    }
    return product;
}

ostream & operator << (ostream &out, const Polynomial &p) {
    Polynomial::Term *p_ptr = p.head;

    if (p_ptr == NULL) {
        out << "0";
    }
    else {
        if (p_ptr->coefficient < 0) {
            out << "- ";
        }
        if ((p_ptr->coefficient != 1 && p_ptr->coefficient != -1) || p_ptr->exponent == 0) {
            out << abs(p_ptr->coefficient);
        }
        if (p_ptr->exponent != 0) {
            out << "x";
        }
        if (p_ptr->exponent != 1 && p_ptr->exponent != 0) {
            out << "^" << p_ptr->exponent;
        }
        p_ptr = p_ptr->next;
        while (p_ptr != NULL) {
            if (p_ptr->coefficient < 0) {
                out << " - ";
            }
            else {
                out << " + ";
            }
            if ((p_ptr->coefficient != 1 && p_ptr->coefficient != -1) || p_ptr->exponent == 0) {
                out << abs(p_ptr->coefficient);
            }
            if (p_ptr->exponent != 0) {
                out << "x";
            }
            if (p_ptr->exponent != 1 && p_ptr->exponent != 0) {
                out << "^" << p_ptr->exponent;
            }
            p_ptr = p_ptr->next;
        }
    }
    return out;
}

/*
int main (){
    Polynomial a, b;

    a.addTerm(2, 1);
    a.addTerm(1, 1);
    b.addTerm(2, -1);
    b.addTerm(1, -1);

    cout << a << endl;
    cout << b << endl;

    cout << a + b << endl;


    return 0;
}
*/
