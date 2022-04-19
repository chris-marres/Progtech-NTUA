#include <iostream>  
#include <stdexcept>  
using namespace std;  
  
class Move {  
    public:  
        // Take sc coins from heap sh and put tc coins to heap th.  
        Move(int sh, int sc, int th, int tc);  
  
        int getSource() const;  
        int getSourceCoins() const;  
        int getTarget() const;  
        int getTargetCoins() const;  
  
        friend ostream & operator << (ostream &out, const Move &move);  
  
    private:  
        int source;  
        int sourceCoins;  
        int target;  
        int targetCoins;  
};  
  
Move::Move(int sh, int sc, int th, int tc) {  
    source = sh;  
    sourceCoins = sc;  
    target = th;  
    targetCoins = tc;  
}  
  
int Move::getSource() const {  
    return source;  
}  
  
int Move::getSourceCoins() const {  
    return sourceCoins;  
}  
  
int Move::getTarget() const {  
    return target;  
}  
  
int Move::getTargetCoins() const {  
    return targetCoins;  
}  
  
ostream & operator << (ostream &out, const Move &move) {  
    if (move.getTargetCoins() == 0){  
        out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts nothing";  
    }  
    else{  
        out << "takes " << move.getSourceCoins() << " coins from heap " << move.getSource() << " and puts " << move.getTargetCoins() << " coins to heap " << move.getTarget();  
    }  
    return out;  
}  
  
class State {  
    public:  
        // State with h heaps, where the i-th heap starts with c[i] coins.  
        // A total of n players are in the game, numbered from 0 to n-1,  
        // and player 0 is the first to play.  
        State(int h, const int c[], int n);  
        ~State();  
  
        void next(const Move &move) throw(logic_error);  
        bool winning() const;  
  
        int getHeaps() const;  
        int getCoins(int h) const throw(logic_error);  
  
        int getPlayers() const;  
        int getPlaying() const;  
  
        friend ostream & operator << (ostream &out, const State &state);  
  
    private:  
        int heaps;  
        int *coins;  
        int players;  
        int playing;  
};  
  
State::State(int h, const int c[], int n) {  
    heaps = h;  
    coins = new int[heaps];  
    players = n;  
    for (int i = 0; i < heaps; i++) {  
        coins[i] = c[i];  
    }  
    playing = 0;  
}  
  
State::~State() {  
    delete[] coins;  
}  
  
void State::next(const Move &move) throw(logic_error){  
    if (move.getSource() < 0 || move.getSource() >= heaps) {  
        throw logic_error("Invalid source heap. Out of range.");  
    }  
    if (move.getSourceCoins() < 0 || move.getSourceCoins() > coins[move.getSource()]) {  
        throw logic_error("Invalid source coins. Can't take more coins than available, or negative.");  
    }  
    if (move.getTarget() < 0 || move.getTarget() >= heaps) {  
        throw logic_error("Invalid target heap. Out of range.");  
    }  
    if (move.getTargetCoins() < 0 || move.getTargetCoins() >= move.getSourceCoins()) {
        if (move.getSourceCoins() != 0) {
            throw logic_error("Invalid target coins. Can't put more coins than taken or equal, or negative.");  
        }   
    }  
    coins[move.getSource()] -= move.getSourceCoins();  
    coins[move.getTarget()] += move.getTargetCoins();  
    if (playing < players - 1) {  
        playing++;  
    }  
    else {  
        playing = 0;  
    }  
}  
  
bool State::winning() const {  
    for (int i = 0; i < heaps; i++) {  
        if (coins[i] != 0) {  
            return false;  
        }  
    }  
    return true;  
}  
  
int State::getHeaps() const {  
    return heaps;  
}  
  
int State::getCoins(int h) const throw(logic_error){  
    if (h < 0 || h >= heaps) {  
        throw logic_error("Invalid heap. Out of range.");  
    }  
    return coins[h];  
}  
  
int State::getPlayers() const {  
    return players;  
}  
  
int State::getPlaying() const {  
    return playing;  
}  
  
ostream & operator << (ostream &out, const State &state) {  
    for (int i = 0; i < state.getHeaps()-1; i++) {  
        out << state.getCoins(i) << ", ";  
    }  
    return out << state.coins[state.getHeaps()-1] << " with " << state.getPlaying() << "/" << state.getPlayers() << " playing next";  
}
