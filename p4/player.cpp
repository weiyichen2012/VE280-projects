#include "player.h"

int spot2Count(Spot spot){
    if (spot == ACE)
        return 1;
    if ((int)spot >= (int)TEN)
        return 10;
    else
        return ((int)spot + 2 - (int)TWO);
}

class simplePlayer : public Player{
public:

    int bet(unsigned int bankroll, unsigned int minimum); 

    bool draw(Card dealer, const Hand &player);

    void expose(Card c);

    void shuffled();

    simplePlayer();

    ~simplePlayer();
};

class countingPlayer : public Player{
    int count;
 public:
    int bet(unsigned int bankroll, unsigned int minimum); 

    bool draw(Card dealer, const Hand &player);

    void expose(Card c);

    void shuffled();
    
    countingPlayer();

    ~countingPlayer();
};

bool playerDraw(Card dealer, const Hand &player){
    int count = player.handValue().count, dealerCount = spot2Count(dealer.spot);
    if (player.handValue().soft){
        if (count <= 17)
            return true;
        if (count == 18){
            if (dealerCount == 2 || dealerCount == 7 || dealerCount == 8)
                return false;
            else
                return true;
        }
        else
            return false;
    }
    else{
        if (count <= 11)
            return true;
        else if (count == 12){
            if (4 <= dealerCount && dealerCount <= 6)
                return false;
            else
                return true;
        }
        else if (13 <= count && count <= 16){
            if (2 <= dealerCount && dealerCount <= 6)
                return false;
            else
                return true;
        }
        else
            return false;
    }
}

int simplePlayer::bet(unsigned int bankroll, unsigned int minimum){
    return minimum;
}

bool simplePlayer::draw(Card dealer, const Hand &player){
    return playerDraw(dealer, player);
}

void simplePlayer::expose(Card c){}

void simplePlayer::shuffled(){}

simplePlayer::simplePlayer(){}

simplePlayer::~simplePlayer(){}

int countingPlayer::bet(unsigned int bankroll, unsigned int minimum){
    if (bankroll < 2 * minimum)
        return minimum;
    if (count >= 2)
        return 2 * minimum;
    else
        return minimum;
}

bool countingPlayer::draw(Card dealer, const Hand &player){
    return playerDraw(dealer, player);
}

void countingPlayer::expose(Card c){
    if ((int)c.spot >= (int)TEN)
        count--;
    else if ((int)c.spot <= (int)SIX)
        count++;
}

void countingPlayer::shuffled(){
    count = 0;
}
    
countingPlayer::countingPlayer(){
    count = 0;
}

countingPlayer::~countingPlayer(){}

static simplePlayer simple;
static countingPlayer counting;

Player* get_Simple(){
    return &simple;
}

Player* get_Counting(){
    return &counting;
}