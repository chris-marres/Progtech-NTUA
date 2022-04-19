#include <iostream>  
#include <stdexcept>
#include <limits>
#include <cmath>  
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

//-------------------------------------------------------------//
//-------------------------Specker2n---------------------------//
//-------------------------------------------------------------//


class Player {
    public:
        Player(const string &n);
        virtual ~Player();


        virtual const string & getType() const = 0;
        virtual Move play(const State &s) = 0;

        friend ostream & operator << (ostream &out, const Player &player);

    protected:
        string name;
};

Player::Player(const string &n) {
    name = n;
}
Player::~Player() {}

ostream & operator << (ostream &out, const Player &player) {
    return out << player.getType() << " player " << player.name;
}

class GreedyPlayer : public Player {
    public:
        GreedyPlayer(const string &n);
        ~GreedyPlayer() override;

        const string & getType() const override;
        Move play(const State &s) override;

    protected:
        string type;
};

GreedyPlayer::GreedyPlayer(const string &n) : Player(n), type("Greedy") {}
GreedyPlayer::~GreedyPlayer() {}

const string & GreedyPlayer::getType() const {
    return type;
}

Move GreedyPlayer::play(const State &s) {
    int source = 0;
    int sourceCoins = 0;
    int maxCoins = 0;
    for (int i = 0; i < s.getHeaps(); ++i) {
        if (s.getCoins(i) > maxCoins) {
            maxCoins = s.getCoins(i);
            source = i;
            sourceCoins = maxCoins;
        }
    }
    return Move(source, sourceCoins, 0, 0);
}

class SpartanPlayer : public Player {
    public:
        SpartanPlayer(const string &n);
        ~SpartanPlayer() override;

        const string & getType() const override;
        Move play(const State &s) override;

    protected:
        string type;
};

SpartanPlayer::SpartanPlayer(const string &n) : Player(n), type("Spartan") {}
SpartanPlayer::~SpartanPlayer() {}

const string & SpartanPlayer::getType() const {
    return type;
}

Move SpartanPlayer::play(const State &s) {
    int source = 0;
    int maxCoins = 0;
    int sourceCoins = 0;
    for (int i = 0; i < s.getHeaps(); ++i) {
        if (s.getCoins(i) > maxCoins) {
            maxCoins = s.getCoins(i);
            source = i;
            sourceCoins = 1;
        }
    }
    return Move(source, sourceCoins, 0, 0);
}

class SneakyPlayer : public Player {
    public:
        SneakyPlayer(const string &n);
        ~SneakyPlayer() override;

        const string & getType() const override;
        Move play(const State &s) override;

    protected:
        string type;
};

SneakyPlayer::SneakyPlayer(const string &n) : Player(n), type("Sneaky") {}
SneakyPlayer::~SneakyPlayer() {}

const string & SneakyPlayer::getType() const {
    return type;
}

Move SneakyPlayer::play(const State &s) {
    int source = 0;
    int minCoins = numeric_limits<int>::max();
    for (int i = 0; i < s.getHeaps(); ++i) {
        if ((s.getCoins(i) < minCoins) && (s.getCoins(i) != 0)) {
            minCoins = s.getCoins(i);
            source = i;
        }
    }
    return Move(source, minCoins, 0, 0);
}


class RighteousPlayer : public Player {
    public:
        RighteousPlayer(const string &n);
        ~RighteousPlayer() override;

        const string & getType() const override;
        Move play(const State &s) override;

    protected:
        string type;
};

RighteousPlayer::RighteousPlayer(const string &n) : Player(n), type("Righteous") {}
RighteousPlayer::~RighteousPlayer() {}

const string & RighteousPlayer::getType() const {
    return type;
}

Move RighteousPlayer::play(const State &s) {
    int source = 0;
    int sourceCoins = 0;
    int target = 0;
    int targetCoins = 0;
    int maxCoins = 0;
    int minCoins = numeric_limits<int>::max();
    for (int i = 0; i < s.getHeaps(); ++i) {
        if (s.getCoins(i) > maxCoins) {
            maxCoins = s.getCoins(i);
            source = i;
            sourceCoins = ceil(float(maxCoins) / 2.0); // gets casted back to int
        }
    }
    for (int i = 0; i < s.getHeaps(); ++i) {
        if (s.getCoins(i) < minCoins) {
            minCoins = s.getCoins(i);
            target = i;
            targetCoins = sourceCoins - 1;
        }
    }
    return Move(source, sourceCoins, target, targetCoins);
}


//-------------------------------------------------------------//
//-------------------------Specker3n---------------------------//
//-------------------------------------------------------------//


class Game {
    public:
        Game(int heaps, int players);
        ~Game();

        void addHeap(int coins) throw(logic_error);
        void addPlayer(Player *player) throw(logic_error);
        void play(ostream &out) throw(logic_error);


        int getPlayers() const;
        const Player *getPlayer(int p) const throw(logic_error);

    private:
        State *state;
        Player **_players;
        int *_coins;
        int heapCount = 0;
        int playerCount = 0;
        int maxHeaps;
        int maxPlayers;
};

Game::Game(int heaps, int players) {
    maxHeaps = heaps;
    maxPlayers = players;
    _coins = new int[heaps];
    _players = new Player*[players];
}

Game::~Game() {
    delete [] _players;
}

void Game::addHeap(int coins) throw(logic_error) {
    if (coins < 0) {
        throw logic_error("Coins cannot be negative");
    }
    if (heapCount == maxHeaps) {
        throw logic_error("Already at max number of heaps. Cannot add more.");
    }
    _coins[heapCount++] = coins;
}

void Game::addPlayer(Player *player) throw(logic_error) {
    if (playerCount == maxPlayers) {
        throw logic_error("Already at max number of players. Cannot add more.");
    }
    _players[playerCount++] = player;
}

int Game::getPlayers() const {
    return maxPlayers;
}

const Player *Game::getPlayer(int p) const throw(logic_error) {
    if (p < 0 || p >= maxPlayers) {
        throw logic_error("Player index out of bounds");
    }
    return _players[p];
}

void Game::play(ostream &out) throw(logic_error) {
    if (heapCount == 0) {
        throw logic_error("No heaps added yet");
    }
    if (playerCount == 0) {
        throw logic_error("No players added yet");
    }
    if (heapCount != maxHeaps) {
        throw logic_error("Heap count does not match state. You need to add more heaps.");
    }
    if (playerCount != maxPlayers) {
        throw logic_error("Player count does not match state. You need to add more players.");
    }
 
    state = new State(heapCount, _coins, playerCount);
    delete [] _coins;

    while (!state->winning()){
        out << "State: " << *state << endl;
        Player *currentPlayer = _players[state->getPlaying()];
        Move nextMove = currentPlayer->play(*state);
        out << *currentPlayer << " " << nextMove << endl;
        state->next(nextMove);
    }
    out << "State: " << *state << endl;
    if (state->getPlaying() != 0) {
        out << *_players[state->getPlaying()-1] << " wins" << endl;
    }
    else {
        out << *_players[state->getPlayers()-1] << " wins" << endl;
    }
}

int main() {

    Game specker(3, 4);
    specker.addHeap(10);
    specker.addHeap(20);
    specker.addHeap(17);
    specker.addPlayer(new SneakyPlayer("Tom"));
    specker.addPlayer(new SpartanPlayer("Mary"));
    specker.addPlayer(new GreedyPlayer("Alan"));
    specker.addPlayer(new RighteousPlayer("Robin"));
    specker.play(cout);

    return 0;
}