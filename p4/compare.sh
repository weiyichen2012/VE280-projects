g++ -Wall player.cpp hand.cpp card.cpp blackjack.cpp rand.cpp deck.cpp -o blackjack
g++ -Wall player1.cpp hand1.cpp card.cpp blackjack1.cpp rand.cpp deck1.cpp -o blackjack1
./blackjack 10000 10000 simple > out1
./blackjack1 10000 10000 simple > out2
diff out1 out2