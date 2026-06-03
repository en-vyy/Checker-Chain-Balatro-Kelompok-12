#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "HighCardChecker.h"
#include "PairChecker.h"
#include "TwoPairChecker.h"
#include "ThreeOfAKindChecker.h"
#include "StraightChecker.h"
#include "FlushChecker.h"
#include "FullHouseChecker.h"
#include "FourOfAKindChecker.h"
#include "StraightFlushChecker.h"
#include "RoyalFlushChecker.h"
#include "FiveOfAKindChecker.h"
#include "FlushHouseChecker.h"
#include "FlushFiveChecker.h"

class ScoringRule {
public:
    ScoringRule();
    
    // Fungsi untuk sistem Base Chips x Base Mult
    HandRank evaluateHand(const Hand& hand);
    int getBaseChips(HandRank rank);
    int getBaseMultiplier(HandRank rank);
    std::string getRankNameStr(HandRank rank);

    // Fungsi untuk menghitung nilai chip dari masing-masing kartu
    int getCardChips(int rank);

    // Fungsi kompatibilitas
    int scoreHand(const Hand& hand); 
    std::string getRankName(const Hand& hand);
    
private:
    HighCardChecker highCardChecker;
    PairChecker pairChecker;
    TwoPairChecker twoPairChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    StraightChecker straightChecker;
    FlushChecker flushchecker;
    FullHouseChecker fullhouseChecker;
    FourOfAKindChecker fourofakindChecker;
    StraightFlushChecker straightFlushChecker;
    RoyalFlushChecker royalFlushChecker;
    FiveOfAKindChecker fiveOfAKindChecker;
    FlushHouseChecker flushHouseChecker;
    FlushFiveChecker flushFiveChecker;
};