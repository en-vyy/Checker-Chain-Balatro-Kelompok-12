#include <iostream>
#include "HighCardChecker.h"

HandRank HighCardChecker::check(const Hand& hand) {
    // Karena ini pemberhentian terakhir, langsung return High Card
    std::cout << "Detected HIGH CARD\n";
    return HandRank::HIGH_CARD; 
}