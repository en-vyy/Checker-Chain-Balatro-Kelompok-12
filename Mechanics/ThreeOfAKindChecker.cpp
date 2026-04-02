#include <iostream>
#include "ThreeOfAKindChecker.h"

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    // Cek apakah value-nya 3 untuk Three of a Kind
    if (hand.value == 3) {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }

    // Jika tidak cocok, lempar ke checker selanjutnya
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}