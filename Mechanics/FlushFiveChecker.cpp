#include <iostream>
#include "FlushFiveChecker.h"

HandRank FlushFiveChecker::check(const Hand& hand) {
    if (hand.value == 10) {
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}