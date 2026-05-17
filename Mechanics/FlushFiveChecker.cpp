#include <iostream>
#include <map>
#include "FlushFiveChecker.h"

// Flush Five butuh tepat 5 kartu (5 rank sama, semua suit sama)
HandRank FlushFiveChecker::check(const Hand& hand) {
    if (hand.cards.size() != 5) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    bool isFlush = true;
    bool isFive = false;
    std::map<int, int> rankCount;

    char firstSuit = hand.cards[0].suit;
    for (const auto& card : hand.cards) {
        if (card.suit != firstSuit) isFlush = false;
        rankCount[card.rank]++;
    }

    for (const auto& pair : rankCount) {
        if (pair.second == 5) isFive = true;
    }

    if (isFlush && isFive) {
        std::cout << "Detected FLUSH FIVE\n";
        return HandRank::FLUSH_FIVE;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}