#include <iostream>
#include "TwoPairChecker.h"

HandRank TwoPairChecker::check(const Hand& hand) {
    // Gunakan 22 untuk Two Pair
    if (hand.value == 8) {
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }

    // Jika tidak cocok, lempar ke checker selanjutnya
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}