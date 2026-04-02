#include <iostream>
#include "StraightChecker.h"

HandRank StraightChecker::check(const Hand& hand) {
    // Cek apakah value-nya 5 untuk Straight
    if (hand.value == 5) {
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }

    // Jika tidak cocok, lempar ke checker selanjutnya
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}