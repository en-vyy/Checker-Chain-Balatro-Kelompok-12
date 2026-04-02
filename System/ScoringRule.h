// Di dalam ScoringRule.h yang ada di folder System:
#pragma once
#include "Hand.h"
#include "PokerHandChecker.h"
#include "../Mechanics/HighCardChecker.h"
#include "../Mechanics/PairChecker.h"
#include "../Mechanics/TwoPairChecker.h"
#include "../Mechanics/ThreeOfAKindChecker.h"
#include "../Mechanics/StraightChecker.h"
#include "../Mechanics/FullHouseChecker.h"
#include "../Mechanics/FourOfAKindChecker.h"
#include "../Mechanics/FlushChecker.h"

class ScoringRule {
public:
    ScoringRule(); // Constructor untuk merangkai linked list nanti
    int scoreHand(const Hand& hand);

private:
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;
    FullHouseChecker fullhouseChecker;
    FourOfAKindChecker fourofakindChecker;
    FlushChecker flushchecker;
    // Fungsi internal untuk mengubah HandRank menjadi skor [cite: 466]
    int convertRankToScore(HandRank rank); 
};