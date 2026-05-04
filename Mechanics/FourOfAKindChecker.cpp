#include <iostream>
#include <map>
#include "FourOfAKindChecker.h"

HandRank FourOfAKindChecker::check(const Hand& hand) {
    std::map<int, int> rankCount;
    
    for (const auto& card : hand.cards) {
        rankCount[card.rank]++;
    }

    bool isFour = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 4) {
            isFour = true;
            break;
        }
    }

    if (isFour) {
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}