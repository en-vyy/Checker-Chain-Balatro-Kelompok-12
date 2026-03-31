#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
// Nanti teman Anda akan melakukan #include kelas spesifik buatannya di sini (misal: "FlushChecker.h")

class ScoringRule {
public:
    ScoringRule(); // Constructor untuk merangkai linked list nanti
    int scoreHand(const Hand& hand); // Fungsi ini sekarang wajib menerima data Hand [cite: 442, 443]

private:
    // Deklarasikan checker sebagai member variable nanti setelah teman Anda selesai membuatnya
    // FlushChecker flushChecker;
    // PairChecker pairChecker;
    
    // Fungsi internal untuk mengubah HandRank menjadi skor [cite: 466]
    int convertRankToScore(HandRank rank); 
};