#include "hand.h"
#include <iostream>
using namespace std;

Hand::Hand(){
    this->discardAll();
}
    
void Hand::discardAll(){
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c){
    if (c.spot == ACE){
        if (this->curValue.count + 11 <= 21){
            this->curValue.count += 11;
            this->curValue.soft = true;
        }
        else
            this->curValue.count += 1;
    }
    else{
        if (c.spot >= TEN)
            this->curValue.count += 10;
        else
            this->curValue.count += (c.spot + (2 - TWO));
    }
    if (this->curValue.count > 21 && this->curValue.soft){
        this->curValue.soft = false;
        this->curValue.count -= 10;
    }
}

HandValue Hand::handValue() const{
    return curValue;
}

// int main(){
//     Card a,b;
//     a.suit = b.suit = HEARTS;
//     a.spot = ACE;
//     b.spot = QUEEN;
//     Hand h;
//     h.addCard(a);
//     cout << h.handValue().count << " " << h.handValue().soft << endl;
//     h.addCard(b);
//     cout << h.handValue().count << " " << h.handValue().soft << endl;
// }