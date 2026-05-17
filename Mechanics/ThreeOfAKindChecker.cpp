#include <iostream>
#include <map>
#include "ThreeOfAKindChecker.h"

// Three of a Kind butuh minimal 3 kartu; tepat 3 rank sama, tanpa pair lain (bukan Full House)
HandRank ThreeOfAKindChecker::check(const Hand& hand) {
    if (hand.cards.size() < 3) {
        if (nextChecker != nullptr) return nextChecker->check(hand);
        return HandRank::HIGH_CARD;
    }

    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) rankCount[card.rank]++;

    bool hasThree = false;
    bool hasPair  = false;

    for (const auto& entry : rankCount) {
        if (entry.second == 3) hasThree = true;
        if (entry.second == 2) hasPair  = true;
    }

    if (hasThree && !hasPair) {
        std::cout << "Detected THREE OF A KIND\n";
        return HandRank::THREE_OF_A_KIND;
    }

    if (nextChecker != nullptr) return nextChecker->check(hand);
    return HandRank::HIGH_CARD;
}