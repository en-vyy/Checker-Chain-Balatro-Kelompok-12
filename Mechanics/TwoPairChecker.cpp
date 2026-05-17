#include <iostream>
#include <map>
#include "TwoPairChecker.h"

// Two Pair butuh minimal 4 kartu; tepat DUA pair berbeda rank, tanpa three-of-a-kind
HandRank TwoPairChecker::check(const Hand& hand) {
    if (hand.cards.size() < 4) {
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

    if (pairCount == 2 && !hasThree) {
        std::cout << "Detected TWO PAIR\n";
        return HandRank::TWO_PAIR;
    }

    if (nextChecker != nullptr) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}