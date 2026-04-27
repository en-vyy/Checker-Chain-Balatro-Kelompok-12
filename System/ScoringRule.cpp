#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule() {
    // Rangkai gerbong dari hierarki tertinggi ke terendah
    fourofakindChecker.setNext(&fullhouseChecker);
    fullhouseChecker.setNext(&flushchecker);
    flushchecker.setNext(&straightChecker);
    straightChecker.setNext(&threeOfAKindChecker);
    threeOfAKindChecker.setNext(&twoPairChecker);
    twoPairChecker.setNext(&pairChecker);
    pairChecker.setNext(&highCardChecker);
}

int ScoringRule::scoreHand(const Hand& hand) {
    std::cout << "Calculating hand score...\n";
    
    // Mulai evaluasi dari ujung rantai (root) yang baru
    HandRank rank = fourofakindChecker.check(hand);
    
    int score = convertRankToScore(rank);
    std::cout << "Final score = " << score << "\n";
    return score;
}

int ScoringRule::convertRankToScore(HandRank rank) {
    switch (rank) {
        case HandRank::HIGH_CARD:
            return 5;
        case HandRank::PAIR:
            return 10;
        case HandRank::TWO_PAIR:
            return 15;
        case HandRank::THREE_OF_A_KIND:
            return 20;
        case HandRank::STRAIGHT:
            return 25;
        case HandRank::FLUSH:
            return 30;
        case HandRank::FULL_HOUSE:
            return 35;
        case HandRank::FOUR_OF_A_KIND:
            return 40;
            
        // Kombinasi tambahan yang ada di Enum (bisa disesuaikan nilainya)
        case HandRank::STRAIGHT_FLUSH:
            return 60;
        case HandRank::ROYAL_FLUSH:
            return 80;
        case HandRank::FIVE_OF_A_KIND:
            return 100;
        case HandRank::FLUSH_HOUSE:
            return 120;
        case HandRank::FLUSH_FIVE:
            return 150;
            
        default:
            return 0; // Nilai default jika entah kenapa gagal terdeteksi
    }
}