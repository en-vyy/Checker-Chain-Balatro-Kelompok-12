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
    // (Isi fungsi convertRankToScore Anda biarkan saja seperti sebelumnya)
    return 5; // contoh dummy
}