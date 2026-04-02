#include <iostream>
#include "FiveOfAKindChecker.h"

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    if (hand.value == 9) {
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}