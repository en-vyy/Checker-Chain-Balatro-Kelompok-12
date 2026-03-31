#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule() {
    // Di sinilah nanti Anda merangkai gerbongnya menggunakan setNext()
    // Contoh jika kelasnya sudah ada:
    // fullHouseChecker.setNext(&flushChecker);
    // flushChecker.setNext(&pairChecker);
}

int ScoringRule::scoreHand(const Hand& hand) {
    std::cout << "Calculating hand score...\n";
    
    // Nanti Anda akan memanggil check() dari checker urutan pertama (root)
    // Contoh: HandRank rank = fullHouseChecker.check(hand);
    
    // Untuk sementara, kita buat dummy rank agar tidak error:
    HandRank rank = HandRank::HIGH_CARD; 
    
    int score = convertRankToScore(rank);
    std::cout << "Final score = " << score << "\n";
    
    return score;
}

int ScoringRule::convertRankToScore(HandRank rank) {
    // Anda yang menentukan aturan konversi poin dasarnya di sini [cite: 466, 467]
    switch (rank) {
        case HandRank::FULL_HOUSE: return 25;
        case HandRank::FLUSH: return 20;
        case HandRank::PAIR: return 10;
        case HandRank::HIGH_CARD: default: return 5;
    }
}