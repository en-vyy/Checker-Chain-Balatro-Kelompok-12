#include <iostream>
#include <map>
#include "FlushHouseChecker.h"

HandRank FlushHouseChecker::check(const Hand& hand) {
    bool isFlush = true;
    bool hasThree = false;
    bool hasTwo = false;
    std::map<int, int> rankCount;

    if (hand.cards.size() > 0) {
        char firstSuit = hand.cards[0].suit;
        for (const auto& card : hand.cards) {
            if (card.suit != firstSuit) isFlush = false; // Cek Flush
            rankCount[card.rank]++;                      // Cek jumlah Rank
        }
    }

    // Cek apakah membentuk pola Full House (3 dan 2)
    for (const auto& pair : rankCount) {
        if (pair.second == 3) hasThree = true;
        if (pair.second == 2) hasTwo = true;
    }

    // Harus memenuhi keduanya
    if (isFlush && hasThree && hasTwo) {
        std::cout << "Detected FLUSH HOUSE\n";
        return HandRank::FLUSH_HOUSE;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}