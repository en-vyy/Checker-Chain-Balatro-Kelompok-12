#include <iostream>
#include <map>
#include "PairChecker.h"

// Pair butuh minimal 2 kartu; tepat SATU pair, tanpa three-of-a-kind (bukan Full House)
HandRank PairChecker::check(const Hand& hand) {
    if (hand.cards.size() < 2) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) rankCount[card.rank]++;

    int pairCount = 0;
    bool hasThree = false;

    for (const auto& entry : rankCount) {
        if (entry.second == 2) pairCount++;
        if (entry.second == 3) hasThree = true;
    }

    if (pairCount == 1 && !hasThree) {
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;
    }

    if (nextChecker != nullptr) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}