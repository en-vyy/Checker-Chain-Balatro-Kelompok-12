#include <iostream>
#include <vector>
#include <algorithm> // Untuk std::shuffle
#include <random>    // Untuk std::default_random_engine
#include <chrono>    // Untuk mendapatkan waktu saat ini sebagai seed acak
#include "HandGenerator.h"

Hand HandGenerator::generateHand() {
    std::cout << "Generating random hand...\n";
    Hand hand;

    // 1. Membuat Dek Virtual berisi 52 Kartu
    std::vector<Card> deck;
    char suits[] = {'S', 'H', 'C', 'D'}; // Spades (Sekop), Hearts (Hati), Clubs (Keriting), Diamonds (Wajik)
    
    for (int suitIdx = 0; suitIdx < 4; ++suitIdx) {
        for (int rank = 2; rank <= 14; ++rank) { // Rank 2 sampai 14 (As)
            deck.push_back({rank, suits[suitIdx]});
        }
    }

    // 2. Mengocok Dek Kartu (Shuffle)
    // Kita mengambil waktu dari sistem komputer saat ini agar hasil kocokan selalu berbeda setiap kali program dijalankan
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    
    std::shuffle(deck.begin(), deck.end(), engine);

    // 3. Mengambil 5 Kartu Teratas dari Dek yang sudah dikocok
    for (int i = 0; i < 5; ++i) {
        hand.cards.push_back(deck[i]);
    }

    return hand;
}