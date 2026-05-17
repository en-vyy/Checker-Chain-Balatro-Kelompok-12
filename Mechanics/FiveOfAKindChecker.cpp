#include <iostream>
#include <map>
#include "FiveOfAKindChecker.h"

// Five of a Kind butuh tepat 5 kartu dengan rank yang semua sama
HandRank FiveOfAKindChecker::check(const Hand& hand) {
    if (hand.cards.size() != 5) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) rankCount[card.rank]++;

    bool isFive = false;
    for (const auto& entry : rankCount) {
        if (entry.second == 5) { isFive = true; break; }
    }

    if (isFive) {
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }

    if (nextChecker != nullptr) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}