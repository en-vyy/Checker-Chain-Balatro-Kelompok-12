#include <iostream>
#include <map>
#include "PairChecker.h"

HandRank PairChecker::check(const Hand& hand) {
    std::map<int, int> rankCount;
    for (const auto& card : hand.cards) {
        rankCount[card.rank]++;
    }

    bool isPair = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 2) { // Cari angka yang jumlahnya 2
            isPair = true;
            break;
        }
    }

    if (isPair) {
        std::cout << "Detected PAIR\n";
        return HandRank::PAIR;  
    }
    
    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}