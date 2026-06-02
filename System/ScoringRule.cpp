#include <iostream>
#include "ScoringRule.h"

ScoringRule::ScoringRule() {
    flushFiveChecker.setNext(&flushHouseChecker);
    flushHouseChecker.setNext(&fiveOfAKindChecker);
    fiveOfAKindChecker.setNext(&royalFlushChecker);
    royalFlushChecker.setNext(&straightFlushChecker);
    straightFlushChecker.setNext(&fourofakindChecker);  
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
    // Mulai evaluasi dari ujung rantai (root) yang paling baru dan tertinggi
    HandRank rank = flushFiveChecker.check(hand);
    
    int score = convertRankToScore(rank);
    return score;
}

int ScoringRule::convertRankToScore(HandRank rank) {
    switch (rank) {
        case HandRank::HIGH_CARD: return 5;
        case HandRank::PAIR: return 10;
        case HandRank::TWO_PAIR: return 15;
        case HandRank::THREE_OF_A_KIND: return 20;
        case HandRank::STRAIGHT: return 25;
        case HandRank::FLUSH: return 30;
        case HandRank::FULL_HOUSE: return 35;
        case HandRank::FOUR_OF_A_KIND: return 40;
        case HandRank::STRAIGHT_FLUSH: return 60;
        case HandRank::ROYAL_FLUSH: return 80;
        case HandRank::FIVE_OF_A_KIND: return 100;
        case HandRank::FLUSH_HOUSE: return 120;
        case HandRank::FLUSH_FIVE: return 150;
        default: return 0;
    }
}

// ==========================================
// TAMBAHAN BARU UNTUK SISTEM JOKER
// ==========================================
std::string ScoringRule::getRankName(const Hand& hand) {
    // Jalankan pengecekan untuk mengambil enum Rank
    HandRank rank = flushFiveChecker.check(hand);
    
    switch (rank) {
        case HandRank::HIGH_CARD: return "High Card";
        case HandRank::PAIR: return "Pair";
        case HandRank::TWO_PAIR: return "Two Pair";
        case HandRank::THREE_OF_A_KIND: return "Three of a Kind";
        case HandRank::STRAIGHT: return "Straight";
        case HandRank::FLUSH: return "Flush";
        case HandRank::FULL_HOUSE: return "Full House";
        case HandRank::FOUR_OF_A_KIND: return "Four of a Kind";
        case HandRank::STRAIGHT_FLUSH: return "Straight Flush";
        case HandRank::ROYAL_FLUSH: return "Royal Flush";
        case HandRank::FIVE_OF_A_KIND: return "Five of a Kind";
        case HandRank::FLUSH_HOUSE: return "Flush House";
        case HandRank::FLUSH_FIVE: return "Flush Five";
        default: return "Unknown";
    }
}