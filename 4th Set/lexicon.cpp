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
                node *parent;

                node(const string &s, const int &f){
                    word = s;
                    frequenccy = f;
                    left = nullptr;
                    right = nullptr;
                    parent = nullptr;
                };
        };

        node* search(const string &s, node* t);
        void print(ostream &out, node *t) const;
        void delete_node(node *t);

    node *root;
};

lexicon::lexicon(){
    root = nullptr;
}

lexicon::~lexicon(){
    if(root != nullptr){
        delete root;
    }
}

int operator < (string s1, string s2){
    return s1.compare(s2) < 0;
}

int operator > (string s1, string s2){
    return s1.compare(s2) > 0;
}

int operator == (string s1, string s2){
    return s1.compare(s2) == 0;
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
                    curr->left->parent = curr;
                    return;
                }
                else{
                    curr = curr->left;
                }
            }
            else{
                if(curr->right == nullptr){
                    curr->right = new node(s, 1);
                    curr->right->parent = curr;
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

//search return the parent of the searched
lexicon::node* lexicon::search(const string &s,node* t){
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

void lexicon::delete_node(node* t){
    if(t == nullptr){
        return;
    }
    else if (t == root){
        if(t->left == nullptr && t->right == nullptr){
            delete t;
            root = nullptr;
        }
        else if(t->left == nullptr){
            root = t->right;
            t->right->parent = nullptr;
            delete t;
        }
        else if(t->right == nullptr){
            root = t->left;
            t->left->parent = nullptr;
            delete t;
        }
        else{
            node *curr = t;
            while(curr->left != nullptr){
                curr = curr->left;
            }
            t->word = curr->word;
            t->frequenccy = curr->frequenccy;
            delete_node(curr);
        } 
    }
    else if(t->left == nullptr && t->right == nullptr){
        if(t->parent->left == t){
            t->parent->left = nullptr;
        }
        else{
            t->parent->right = nullptr;
        }
        delete t;
    }
    else if(t->left == nullptr){
        if(t->parent->left == t){
            t->parent->left = t->right;
            t->right->parent = t->parent;
        }
        else{
            t->parent->right = t->right;
            t->right->parent = t->parent;
        }
        delete t;
    }
    else if(t->right == nullptr){
        if(t->parent->left == t){
            t->parent->left = t->left;
            t->left->parent = t->parent;
        }
        else{
            t->parent->right = t->left;
            t->left->parent = t->parent;
        }
        delete t;
    }
    else{
        node *curr = t->left;
        while(curr->left != nullptr){
            curr = curr->left;
        }
        t->word = curr->word;
        t->frequenccy = curr->frequenccy;
        delete_node(curr);
    }
}

void lexicon::replace(const string &s1, const string &s2){
    node *firstWord = search(s1, root);
    if(firstWord != nullptr){
        node *secondWord = search(s2, root);
        if(secondWord != nullptr){
            secondWord->frequenccy += firstWord->frequenccy;
            delete_node(firstWord);
        }
        else{
            insert(s2);
            search(s2, root)->frequenccy = firstWord->frequenccy;
            delete_node(firstWord);
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

/*
int main(){

    lexicon l;
    
    string temp = "";
    for (int i = 0; i < 7; i++){
        temp += "a";
        l.insert(temp);
    }
    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "b";
        l.insert(temp);
    }
    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "c";
        l.insert(temp);
    }
    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "d";
        l.insert(temp);
    }

    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "a";
        l.replace(temp, "dummy");
    }
    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "b";
        l.replace(temp, "dummy");
    }
    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "c";
        l.replace(temp, "dummy");
    }
    temp = "";
    for (int i = 0; i < 7; i++){
        temp += "d";
        l.replace(temp, "dummy");
    }

    cout << l;

    return 0;
}
*/
