#include <iostream>
#include <vector>
#include <algorithm>
#include "StraightFlushChecker.h"

HandRank StraightFlushChecker::check(const Hand& hand) {
    bool isStraight = true;
    bool isFlush = true;

    if (hand.cards.size() == 5) {
        // 1. Cek Flush
        char firstSuit = hand.cards[0].suit;
        for (const auto& card : hand.cards) {
            if (card.suit != firstSuit) isFlush = false;
        }

        // 2. Cek Straight
        std::vector<int> ranks;
        for (const auto& card : hand.cards) ranks.push_back(card.rank);
        std::sort(ranks.begin(), ranks.end());

        for (size_t i = 1; i < ranks.size(); i++) {
            if (ranks[i] != ranks[i-1] + 1) {
                isStraight = false;
                break;
            }
        }
    } else {
        isStraight = false;
        isFlush = false;
    }

    if (isStraight && isFlush) {
        std::cout << "Detected STRAIGHT FLUSH\n";
        return HandRank::STRAIGHT_FLUSH;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}