#include <iostream>

using namespace std;

template <typename T>
class stack {
    public:
        stack (int size) {
            _stack = new(nothrow) T[size];
            if (!_stack){
                perror("Out of memory");
                exit(1);
            }
            _size = size;
        }

        stack (const stack &s) {
            _size = s._size;
            current = s.current;
            _stack = new(nothrow) T[_size];
            if (!_stack){
                perror("Out of memory");
                exit(1);
            }
            for (int i = 0; i < current; ++i){
                _stack[i] = s._stack[i];
            }
        }

        ~stack () {
            delete[] _stack;
        }

        const stack & operator = (const stack &s) {
            delete[] _stack;
            _size = s._size;
            current = s.current;
            _stack = new(nothrow) T[_size];
            if (!_stack){
                perror("Out of memory");
                exit(1);
            }
            for (int i = 0; i < current; ++i){
                _stack[i] = s._stack[i];
            }
            return *this;
        }

        bool empty () { return (current == 0); }

        void push (const T &x) {
            _stack[current] = x;
            ++current;
        }

        T pop () {
            return _stack[--current];
        }

        int size () { return current; }

        friend ostream & operator << (ostream &out, const stack &s) {
            if (s.current == 0) {
                out << "[]";
            }
            else if (s.current == 1){
                out << "[" << s._stack[0] << "]";
            }
            else {
                out << "[";
                for (int i = 0; i < s.current - 1; ++i){
                    out << s._stack[i] << ", ";
                }
                out << s._stack[s.current-1] << "]";
            }
            return out;
        }

    private:
        int _size;
        T* _stack;
        int current = 0;
        
};