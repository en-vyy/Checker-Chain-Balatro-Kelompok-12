#include <iostream>
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating cards for player...\n";
    Hand hand;
    hand.value = 3; // Nilai dummy simulasi
    return hand;
}