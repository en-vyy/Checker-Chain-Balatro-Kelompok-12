#pragma once
#include "Hand.h" // Otomatis membawa ChosenHand juga

class HandPlayer {
public:
    // Ubah tipe return-nya menjadi ChosenHand
    ChosenHand playHand(const Hand& generatedHand); 
};