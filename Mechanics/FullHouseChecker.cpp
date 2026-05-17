#include <iostream>
#include <map>
#include "FullHouseChecker.h"

// Full House butuh tepat 5 kartu (pola 3+2)
HandRank FullHouseChecker::check(const Hand& hand) {
    if (hand.cards.size() != 5) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) rankCount[card.rank]++;

    bool hasThree = false;
    bool hasTwo   = false;

    for (const auto& entry : rankCount) {
        if (entry.second == 3) hasThree = true;
        if (entry.second == 2) hasTwo   = true;
    }

    if (hasThree && hasTwo) {
        std::cout << "Detected FULL HOUSE\n";
        return HandRank::FULL_HOUSE;
    }

    if (nextChecker != nullptr) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}