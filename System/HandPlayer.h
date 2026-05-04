#pragma once
#include "Hand.h"
#include "ChosenHand.h" // Tambahkan baris ini

class HandPlayer {
public:
    ChosenHand playHand(const Hand& generatedHand); 
};