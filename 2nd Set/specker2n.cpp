#include <iostream>  
#include <stdexcept>
#include <limits>
#include <cmath>  
using namespace std;

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
