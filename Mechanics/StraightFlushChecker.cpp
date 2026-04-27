#include <iostream>
#include "StraightFlushChecker.h"

HandRank StraightFlushChecker::check(const Hand& hand) {
    if (hand.value == 13) {
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}