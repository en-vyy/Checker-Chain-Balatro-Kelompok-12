#include <iostream>
#include <vector>
#include <algorithm>
#include "RoyalFlushChecker.h"

HandRank RoyalFlushChecker::check(const Hand& hand) {
    bool isStraight = true;
    bool isFlush = true;
    bool isRoyal = false;

    if (hand.cards.size() == 5) {
        char firstSuit = hand.cards[0].suit;
        std::vector<int> ranks;
        
        for (const auto& card : hand.cards) {
            if (card.suit != firstSuit) isFlush = false;
            ranks.push_back(card.rank);
        }

        std::sort(ranks.begin(), ranks.end());

        for (size_t i = 1; i < ranks.size(); i++) {
            if (ranks[i] != ranks[i-1] + 1) {
                isStraight = false;
                break;
            }
        }

        // Syarat spesifik Royal: kartu terkecil = 10, terbesar = 14
        if (ranks[0] == 10 && ranks[4] == 14) {
            isRoyal = true;
        }
    } else {
        isStraight = false;
        isFlush = false;
    }

    if (isStraight && isFlush && isRoyal) {
        std::cout << "Detected ROYAL FLUSH\n";
        return HandRank::ROYAL_FLUSH;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}