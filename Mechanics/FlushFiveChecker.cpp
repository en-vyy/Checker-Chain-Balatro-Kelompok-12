#include <iostream>
#include <map>
#include "FlushFiveChecker.h"

HandRank FlushFiveChecker::check(const Hand& hand) {
    bool isFlush = true;
    bool isFive = false;
    std::map<int, int> rankCount;

    if (hand.cards.size() > 0) {
        char firstSuit = hand.cards[0].suit;
        for (const auto& card : hand.cards) {
            if (card.suit != firstSuit) isFlush = false; 
            rankCount[card.rank]++;                      
        }
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