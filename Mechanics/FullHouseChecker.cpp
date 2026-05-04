#include <iostream>
#include <map>
#include "FullHouseChecker.h"

HandRank FullHouseChecker::check(const Hand& hand) {
    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) {
        rankCount[card.rank]++;
    }

    bool hasThree = false;
    bool hasTwo = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 3) hasThree = true;
        if (pair.second == 2) hasTwo = true;
    }

    if (hasThree && hasTwo) {
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }
        
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}