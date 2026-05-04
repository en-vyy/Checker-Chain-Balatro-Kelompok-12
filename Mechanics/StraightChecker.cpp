#include <iostream>
#include <vector>
#include <algorithm>
#include "StraightChecker.h"

HandRank StraightChecker::check(const Hand& hand) {
    bool isStraight = true;
    
    if (hand.cards.size() == 5) {
        std::vector<int> ranks;
        for (const auto& card : hand.cards) ranks.push_back(card.rank); // Ekstrak angkanya
        std::sort(ranks.begin(), ranks.end()); // Urutkan dari kecil ke besar

        // Cek apakah berurutan
        for (size_t i = 1; i < ranks.size(); i++) {
            if (ranks[i] != ranks[i-1] + 1) {
                isStraight = false;
                break;
            }
        }
    } else {
        isStraight = false;
    }

    if (isStraight) {
        std::cout << "Detected STRAIGHT\n";
        return HandRank::STRAIGHT;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}