#include <iostream>
#include <map>
#include "FlushHouseChecker.h"

// Flush House butuh tepat 5 kartu (3+2, semua suit sama)
HandRank FlushHouseChecker::check(const Hand& hand) {
    if (hand.cards.size() != 5) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    bool isFlush = true;
    bool hasThree = false;
    bool hasTwo = false;
    std::map<int, int> rankCount;

    char firstSuit = hand.cards[0].suit;
    for (const auto& card : hand.cards) {
        if (card.suit != firstSuit) isFlush = false;
        rankCount[card.rank]++;
    }

    for (const auto& pair : rankCount) {
        if (pair.second == 3) hasThree = true;
        if (pair.second == 2) hasTwo = true;
    }

    if (isFlush && hasThree && hasTwo) {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}