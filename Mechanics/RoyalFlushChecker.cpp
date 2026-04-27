#include <iostream>
#include "RoyalFlushChecker.h"

HandRank RoyalFlushChecker::check(const Hand& hand) {
    if (hand.value == 12) {
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}