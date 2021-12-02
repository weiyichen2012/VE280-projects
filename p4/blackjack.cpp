#include <iostream>
#include "card.h"
#include "deck.h"
#include "rand.h"
#include "player.h"

using namespace std;

#define MINIMUM_BET 5

void shuffleDeck(Deck* deck, Player* player){
    cout << "Shuffling the deck\n";
    player->shuffled();
    for (int i = 0; i < 7; ++i){
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck->shuffle(cut);
    }
}

void printCard(string subject, const Card* card){
    cout << subject << SpotNames[card->spot] << " of " << SuitNames[card->suit] << endl;
}

int main(int argc, char* argv[]){
    int bankroll = atoi(argv[1]), hands = atoi(argv[2]);
    Deck* deck = new Deck();
    Player* player;
    if (argv[3][0] == 's')
        player = get_Simple();
    else
        player = get_Counting();
    Hand playerHand, dealerHand;
    shuffleDeck(deck, player);

    int thisHand = 0;
    while (thisHand < hands && bankroll >= MINIMUM_BET){
        thisHand++;
        cout << "Hand " << thisHand << " bankroll " << bankroll << endl;
        playerHand.discardAll();
        dealerHand.discardAll();

        if (deck->cardsLeft() < 20)
            shuffleDeck(deck, player);
        
        int wager = player->bet(bankroll, MINIMUM_BET);
        cout << "Player bets " << wager << endl;

        Card playerCard1 = deck->deal(), dealerCard1 = deck->deal(), playerCard2 = deck->deal(), dealerCard2 = deck->deal();
        printCard("Player dealt ", &playerCard1);
        player->expose(playerCard1);
        playerHand.addCard(playerCard1);

        printCard("Dealer dealt ", &dealerCard1);
        player->expose(dealerCard1);

        printCard("Player dealt ", &playerCard2);
        player->expose(playerCard2);
        playerHand.addCard(playerCard2);

        if (playerHand.handValue().count == 21){
            cout << "Player dealt natural 21\n";
            bankroll += (3 * wager) / 2;
        }
        else{
            while (player->draw(dealerCard1, playerHand)){
                Card tmpCard = deck->deal();
                printCard("Player dealt ", &tmpCard);
                player->expose(tmpCard);
                playerHand.addCard(tmpCard);
                if (playerHand.handValue().count > 21)
                    break;
            }
            cout << "Player's total is " << playerHand.handValue().count << endl;
            if (playerHand.handValue().count > 21){
                bankroll -= wager;
                cout << "Player busts\n";
                continue;
            }

            dealerHand.addCard(dealerCard1);
            dealerHand.addCard(dealerCard2);
            player->expose(dealerCard2);
            printCard("Dealer's hole card is ", &dealerCard2);
            while (dealerHand.handValue().count < 17){
                Card tmpCard = deck->deal();
                printCard("Dealer dealt ", &tmpCard);
                player->expose(tmpCard);
                dealerHand.addCard(tmpCard);
                if (dealerHand.handValue().count > 21)
                    break;
            }
            cout << "Dealer's total is " << dealerHand.handValue().count << endl;
            if (dealerHand.handValue().count > 21){
                bankroll += wager;
                cout << "Dealer busts\n";
                continue;
            }
            if (playerHand.handValue().count < dealerHand.handValue().count){
                cout << "Dealer wins\n";
                bankroll -= wager;
            }
            else if (playerHand.handValue().count == dealerHand.handValue().count)
                cout << "Push\n";
            else{
                cout << "Player wins\n";
                bankroll += wager;
            }
        }
    }
    cout << "Player has " << bankroll << " after " << thisHand << " hands\n";
    delete(deck);
    return 0;
}
