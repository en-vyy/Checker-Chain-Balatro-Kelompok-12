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

HandRank ScoringRule::evaluateHand(const Hand& hand) {
    return flushFiveChecker.check(hand); 
}

int ScoringRule::getBaseChips(HandRank rank) {
    switch (rank) {
        case HandRank::HIGH_CARD: return 5;
        case HandRank::PAIR: return 10;
        case HandRank::TWO_PAIR: return 20;
        case HandRank::THREE_OF_A_KIND: return 30;
        case HandRank::STRAIGHT: return 30;
        case HandRank::FLUSH: return 35;
        case HandRank::FULL_HOUSE: return 40;
        case HandRank::FOUR_OF_A_KIND: return 60;
        case HandRank::ROYAL_FLUSH: return 80;
        case HandRank::STRAIGHT_FLUSH: return 100;
        case HandRank::FIVE_OF_A_KIND: return 120;
        case HandRank::FLUSH_HOUSE: return 140;
        case HandRank::FLUSH_FIVE: return 150;
        default: return 0;
    }
}

int ScoringRule::getBaseMultiplier(HandRank rank) {
    switch (rank) {
        case HandRank::HIGH_CARD: return 1;
        case HandRank::PAIR: return 2;
        case HandRank::TWO_PAIR: return 2;
        case HandRank::THREE_OF_A_KIND: return 3;
        case HandRank::STRAIGHT: return 3;
        case HandRank::FLUSH: return 4;
        case HandRank::FULL_HOUSE: return 4;
        case HandRank::FOUR_OF_A_KIND: return 7;
        case HandRank::ROYAL_FLUSH: return 8;
        case HandRank::STRAIGHT_FLUSH: return 8;
        case HandRank::FIVE_OF_A_KIND: return 12;
        case HandRank::FLUSH_HOUSE: return 14;
        case HandRank::FLUSH_FIVE: return 14;
        default: return 1;
    }
}

std::string ScoringRule::getRankNameStr(HandRank rank) {
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

// Fungsi untuk menghitung nilai satuan masing-masing kartu yang dimainkan
int ScoringRule::getCardChips(int rank) {
    if (rank >= 2 && rank <= 10) {
        return rank; // Kartu 2-10 sesuai angkanya
    } else if (rank >= 11 && rank <= 13) {
        return 10;   // J, Q, K bernilai 10
    } else if (rank == 14) {
        return 11;   // As bernilai 11
    }
    return 0;
}

int ScoringRule::scoreHand(const Hand& hand) {
    HandRank rank = evaluateHand(hand);
    return getBaseChips(rank) * getBaseMultiplier(rank);
}

std::string ScoringRule::getRankName(const Hand& hand) {
    return getRankNameStr(evaluateHand(hand));
}