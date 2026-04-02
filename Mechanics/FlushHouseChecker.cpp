#include <iostream>
#include "FlushHouseChecker.h"

HandRank FlushHouseChecker::check(const Hand& hand) {
    if (hand.value == 11) {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}