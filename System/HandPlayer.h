#pragma once
#include "Hand.h"
#include "ChosenHand.h"
#include <string>

class HandPlayer {
public:
    // Menerima referensi (Hand&) agar kartu di tangan bisa dikurangi setelah di-play
    ChosenHand playHand(Hand& currentHand); 
    
    // Fungsi baru untuk discard
    void discardCards(Hand& currentHand); 

private:
    std::string formatRank(int rank);
};