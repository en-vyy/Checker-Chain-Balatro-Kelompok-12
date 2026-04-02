#include <iostream>
#include "FourOfAKindChecker.h"

HandRank FourOfAKindChecker::check(const Hand& hand) {
    // 1. Cek apakah value-nya cocok (misal 4 untuk Four of a Kind)
    if (hand.value == 4) { 
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }

    // 2. Jika tidak cocok, OPER ke checker selanjutnya!
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    
    return HandRank::HIGH_CARD;
}