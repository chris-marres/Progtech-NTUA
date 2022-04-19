#include <iostream>
#include <stdexcept>
using namespace std;

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
