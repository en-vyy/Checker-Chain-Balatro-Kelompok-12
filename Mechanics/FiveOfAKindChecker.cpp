#include <iostream>
#include <map>
#include "FiveOfAKindChecker.h"

HandRank FiveOfAKindChecker::check(const Hand& hand) {
    std::map<int, int> rankCount;
    
    // Menghitung jumlah masing-masing rank (angka)
    for (const auto& card : hand.cards) {
        rankCount[card.rank]++;
    }

    bool isFive = false;
    for (const auto& pair : rankCount) {
        if (pair.second == 5) {
            isFive = true;
            break;
        }
    }

    if (isFive) {
        std::cout << "Detected FIVE OF A KIND\n";
        return HandRank::FIVE_OF_A_KIND;
    }

    if (nextChecker != nullptr) {
        return nextChecker->check(hand);
    }
    return HandRank::HIGH_CARD;
}