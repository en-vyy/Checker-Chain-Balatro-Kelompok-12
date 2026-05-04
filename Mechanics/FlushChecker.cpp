#include <iostream>
#include "FlushChecker.h"

HandRank FlushChecker::check(const Hand& hand) {
    bool isFlush = true;
    
    if (hand.cards.size() > 0) {
        char firstSuit = hand.cards[0].suit;
        for (const auto& card : hand.cards) {
            if (card.suit != firstSuit) {
                isFlush = false;
                break;
            }
        }
    } else {
        isFlush = false;
    }

    if (isFlush) {
        std::cout << "Detected FLUSH\n";
        return HandRank::FLUSH;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}