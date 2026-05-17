#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "FlushChecker.h"

// Cek: semua suit sama, TAPI bukan Straight Flush / Royal Flush / Flush House / Flush Five
HandRank FlushChecker::check(const Hand& hand) {
    // Flush butuh tepat 5 kartu — kurang dari itu langsung lanjut ke checker berikutnya
    if (hand.cards.size() != 5) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    // --- Cek Flush ---
    bool isFlush = true;
    char firstSuit = hand.cards[0].suit;
    for (const auto& card : hand.cards) {
        if (card.suit != firstSuit) { isFlush = false; break; }
    }

    if (!isFlush) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    // --- Sudah Flush; pastikan bukan varian flush yang lebih tinggi ---

    // Cek Straight (berurutan) → Straight Flush / Royal Flush
    bool isStraight = false;
    if (hand.cards.size() == 5) {
        std::vector<int> ranks;
        for (const auto& card : hand.cards) ranks.push_back(card.rank);
        std::sort(ranks.begin(), ranks.end());

        isStraight = true;
        for (size_t i = 1; i < ranks.size(); i++) {
            if (ranks[i] != ranks[i-1] + 1) { isStraight = false; break; }
        }
    }
    if (isStraight) {
        // Ini Straight Flush atau Royal Flush — biarkan checker mereka yang tangani
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    // Cek pola rank → Flush House (3+2) atau Flush Five (5 sama)
    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) rankCount[card.rank]++;

    bool hasThree = false, hasPair = false, hasFive = false;
    for (const auto& entry : rankCount) {
        if (entry.second == 5) hasFive  = true;
        if (entry.second == 3) hasThree = true;
        if (entry.second == 2) hasPair  = true;
    }

    if (hasFive || (hasThree && hasPair)) {
        // Ini Flush Five atau Flush House — biarkan checker mereka yang tangani
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    // Murni Flush
    std::cout << "Detected FLUSH\n";
    return HandRank::FLUSH;
}