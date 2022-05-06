#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

class ChessBoardArray {

    protected:
        class Row {
            public:
                Row(ChessBoardArray &a, int i);
                int & operator [] (int i) const;

            private:
                ChessBoardArray *array;
                int index;
        };

        class ConstRow {
            public:
                ConstRow(const ChessBoardArray &a, int i);
                int operator [] (int i) const;

            private:
                const ChessBoardArray *array;
                int index;
        };

    public:
        ChessBoardArray(unsigned size = 0, unsigned base = 0);
        ChessBoardArray(const ChessBoardArray &a);
        ~ChessBoardArray();

        ChessBoardArray & operator = (const ChessBoardArray &a);

        int & select(int i, int j);
        int select(int i, int j) const;

        const Row operator [] (int i);
        const ConstRow operator [] (int i) const;


        friend ostream & operator << (ostream &out, const ChessBoardArray &a);

    private:
        int size;
        int base;
        int *data;

        unsigned int loc(int i, int j) const throw(out_of_range);
};


ChessBoardArray::Row::Row(ChessBoardArray &a, int i) {
    array = &a;
    index = i;
}

int & ChessBoardArray::Row::operator [] (int i) const {
    return array->select(index, i);
}

ChessBoardArray::ConstRow::ConstRow(const ChessBoardArray &a, int i) {
    array = &a;
    index = i;
}

int ChessBoardArray::ConstRow::operator [] (int i) const {
    return array->select(index, i);
}

ChessBoardArray::ChessBoardArray(unsigned size, unsigned base) {
    this->size = size;
    this->base = base;
    data = new int[size * size / 2 + size % 2];

    for (int i = 0; i < size * size / 2 + size % 2; i++) {
        data[i] = 0;
    }
}

ChessBoardArray::ChessBoardArray(const ChessBoardArray &a) {
    size = a.size;
    base = a.base;
    data = new int[(size * size) / 2 + size % 2];

    for (int i = 0; i < (size * size) / 2 + size % 2; i++) {
        data[i] = a.data[i];
    }
}

ChessBoardArray::~ChessBoardArray() {
    delete[] data;
}

ChessBoardArray & ChessBoardArray::operator = (const ChessBoardArray &a) {
    if (this == &a) {
        return *this;
    }

    delete[] data;

    size = a.size;
    base = a.base;
    data = new int[(size * size) / 2 + size % 2];

    for (int i = 0; i < (size * size) / 2 + size % 2; i++) {
        data[i] = a.data[i];
    }

    return *this;
}

int & ChessBoardArray::select(int i, int j) {
    return data[loc(i, j)];
}

int ChessBoardArray::select(int i, int j) const {
    return data[loc(i, j)];
}

const ChessBoardArray::Row ChessBoardArray::operator [] (int i) {
    return Row(*this, i);
}

const ChessBoardArray::ConstRow ChessBoardArray::operator [] (int i) const {
    return ConstRow(*this, i);
}

unsigned int ChessBoardArray::loc(int i, int j) const throw(out_of_range) {
    int di = i - base;
    int dj = j - base;

    if (di < 0 || di >= size || dj < 0 || dj >= size) {
        throw out_of_range("Index out of range");
    }
    if ((di + dj) % 2 == 1) {
        throw out_of_range("black square");
    }

    if (size % 2 == 0) return di * (size / 2) + dj / 2;
    
    return di * (size / 2) + di / 2 + di % 2 + dj / 2;

}

ostream & operator << (ostream &out, const ChessBoardArray &a) {
    for (int i = 0; i < a.size; i++) {
        for (int j = 0; j < a.size; j++) {
            if ((i + j) % 2 == 1) {
                out << setw(4) << "0";
            }
            else{
                out << setw(4) << a.select(i + a.base, j + a.base);
            }
        }
        out << endl;
    }
    return out;
}

/*
int main () {
    int size = 4;
    int base = 1;
    ChessBoardArray a(size, base);
    
    a[3][1] = 42;
    a[4][4] = 17;

    try { a[2][1] = 7; } catch (out_of_range &e) { cout << e.what() << endl; }
    try { cout << a[1][2] << endl; } catch (out_of_range &e) { cout << e.what() << endl; }

    cout << a << endl;

    return 0;
}
*/
