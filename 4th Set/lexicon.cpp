#include <iostream>
using namespace std;


class lexicon {
    public:
        lexicon();
        ~lexicon();

        void insert(const string &s);
        int lookup(const string &s) const;
        int depth(const string &s) const;
        void replace(const string &s1, const string &s2);

        friend ostream & operator << (ostream &out, const lexicon &l);

    private:
        class node{
            public:
                string word;
                int frequenccy;
                node *left;
                node *right;

                node(const string &s, const int &f){
                    word = s;
                    frequenccy = f;
                    left = nullptr;
                    right = nullptr;
                };
        };

        node* search(const string &s, node *t);
        void print(ostream &out, node *t) const;

    node *root;
};

lexicon::lexicon(){
    root = nullptr;
}

// Need to implement recursive destructor of BST
lexicon::~lexicon(){
    if(root != nullptr){
        delete root;
    }
}

void lexicon::insert(const string &s){
    if(root == nullptr){
        root = new node(s, 1);
    }
    else{
        node *curr = root;
        while(curr != nullptr){
            if(s == curr->word){
                curr->frequenccy++;
                return;
            }
            else if(s < curr->word){
                if(curr->left == nullptr){
                    curr->left = new node(s, 1);
                    return;
                }
                else{
                    curr = curr->left;
                }
            }
            else{
                if(curr->right == nullptr){
                    curr->right = new node(s, 1);
                    return;
                }
                else{
                    curr = curr->right;
                }
            }
        }
    }
}

int lexicon::lookup(const string &s) const{
    if(root == nullptr){
        return 0;
    }
    else{
        node *curr = root;
        while(curr != nullptr){
            if(s == curr->word){
                return curr->frequenccy;
            }
            else if(s < curr->word){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        return 0;
    }
}

int lexicon::depth(const string &s) const{
    if(root == nullptr){
        return -1;
    }
    else{
        node *curr = root;
        int depth = 0;
        while(curr != nullptr){
            if(s == curr->word){
                return depth;
            }
            else if(s < curr->word){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
            depth++;
        }
        return -1;
    }
}

lexicon::node* lexicon::search(const string &s, node *t){
    if(t == nullptr){
        return nullptr;
    }
    else if(s == t->word){
        return t;
    }
    else if(s < t->word){
        return search(s, t->left);
    }
    else{
        return search(s, t->right);
    }
}


void lexicon::replace(const string &s1, const string &s2){
    node *firstWord = search(s1, root);
    if(firstWord != nullptr){
        node *secondWord = search(s2, root);
        if(secondWord != nullptr){
            secondWord->frequenccy += firstWord->frequenccy;
            if (firstWord->left != nullptr && firstWord->right != nullptr){
                firstWord = firstWord->left;
            }
            else if(firstWord->left != nullptr){
                firstWord = firstWord->left;
            }
            else if(firstWord->right != nullptr){
                firstWord = firstWord->right;
            }
            else{
                firstWord = nullptr;
            }
        }
        else{
            insert(s2);
            search(s2, root)->frequenccy += firstWord->frequenccy;
            if (firstWord->left != nullptr && firstWord->right != nullptr){
                firstWord = firstWord->left;
            }
            else if(firstWord->left != nullptr){
                firstWord = firstWord->left;
            }
            else if(firstWord->right != nullptr){
                firstWord = firstWord->right;
            }
            else{
                firstWord = nullptr;
            }
        }
    }
}

void lexicon::print(ostream &out, node *t) const{
    if(t != nullptr){
        print(out, t->left);
        out << t->word << " " << t->frequenccy << endl;
        print(out, t->right);
    }
}

ostream & operator << (ostream &out, const lexicon &l){
    l.print(out, l.root);
    return out;
}

int main(){

    lexicon l;
    l.insert("the");
    l.insert("boy");
    l.insert("and");
    l.insert("the");
    l.insert("wolf");

    cout << "The word 'the' is found " << l.lookup("the") << " time(s)" << endl;
    cout << "The word 'and' is found at depth " << l.depth("and") << endl;
    cout << l;
    l.replace("boy", "wolf");
    cout << "After replacement:\n";
    cout << l;
    cout << "Now the word 'and' is found at depth " << l.depth("and") << endl;

    return 0;
}