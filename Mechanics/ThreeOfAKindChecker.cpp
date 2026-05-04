#include <iostream>
#include <map>
#include "ThreeOfAKindChecker.h"

HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) {
        rankCount[card.rank]++;
    }

    bool hasThree = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 3) {
            hasThree = true;
            break;
        }
    }

    if (hasThree) {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}