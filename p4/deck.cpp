#include "deck.h"
// #include <iostream>

Deck::Deck(){
    this->reset();
}

void Deck::reset(){
    this->next = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 13; ++j){
            deck[i * 13 + j].suit = (Suit)i;
            deck[i * 13 + j].spot = (Spot)j;
    }
}

void Deck::shuffle(int n){
    this->next = 0;
    Card newDeck[DeckSize];
    if (n <= 26){
        for (int i = 0; i < n; ++i){
            newDeck[2 * i] = this->deck[n + i];
            newDeck[2 * i + 1] = this->deck[i];
        }
        for (int i = 2 * n; i < DeckSize; ++i)
            newDeck[i] = this->deck[i];
    }
    else{
        for (int i = 0; i < DeckSize - n; ++i){
            newDeck[2 * i] = this->deck[n + i];
            newDeck[2 * i + 1] = this->deck[i];
        }
        for (int i = DeckSize - n; i < n; ++i)
            newDeck[DeckSize + i - n] = this->deck[i];
    }

    for (int i = 0; i < DeckSize; ++i)
        this->deck[i] = newDeck[i];
}

Card Deck::deal(){
    return this->deck[this->next++];
}

int Deck::cardsLeft(){
    return DeckSize - this->next;
}

// void printCard(Card card){
//     std::cout << SuitNames[card.suit] << " " << SpotNames[card.spot];
// }


// void printDeck(Deck deck){
//     for (int i = 0; i < DeckSize; ++i){
//         std::cout << i << ": ";
//         printCard(deck.deck[i]);
//         std::cout << std::endl;
//     }
// }

// int main(){
//     Deck a;
//     a.shuffle(51);
//     printDeck(a);
// }