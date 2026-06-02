#pragma once
#include <string>
#include <vector>
#include "Card.h" 

struct ScorePayload {
    std::string handRankName;      
    int baseScore;                 
    int multiplier;                
    std::vector<Card> playedCards; // Uncomment kalau nanti butuh efek cek kembang kartu

    ScorePayload() : baseScore(0), multiplier(1) {}
};