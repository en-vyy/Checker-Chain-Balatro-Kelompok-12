#include <iostream>
#include "HandPlayer.h"

ChosenHand HandPlayer::playHand(const Hand& generatedHand) {
    std::cout << "Player is selecting cards...\n";
    ChosenHand chosen;
    
    // Untuk sementara, mari kita buat seolah-olah player memilih semua kartu (5 buah) 
    // yang diberikan oleh HandGenerator.
    for (const auto& card : generatedHand.cards) {
        chosen.addChosenCard(card);
    }
    
    chosen.showChosenCards();
    return chosen; // Mengirimkan kartu yang sudah dipilih ke sistem penilai
}