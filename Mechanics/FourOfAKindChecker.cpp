#include <iostream>
#include <map>
#include "FourOfAKindChecker.h"

// Four of a Kind butuh minimal 4 kartu; tepat 4 rank sama (bukan Five of a Kind)
HandRank FourOfAKindChecker::check(const Hand& hand) {
    if (hand.cards.size() < 4) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) rankCount[card.rank]++;

    bool isFour = false;
    bool isFive = false;

    for (const auto& entry : rankCount) {
        if (entry.second == 4) isFour = true;
        if (entry.second == 5) isFive = true;
    }

    if (isFour && !isFive) {
        std::cout << "Detected FOUR OF A KIND\n";
        return HandRank::FOUR_OF_A_KIND;
    }

    if (nextChecker != nullptr) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}