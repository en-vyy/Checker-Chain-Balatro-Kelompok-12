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
#include "../Mechanics/StraightFlushChecker.h"
#include "../Mechanics/RoyalFlushChecker.h"
#include "../Mechanics/FiveOfAKindChecker.h"
#include "../Mechanics/FlushHouseChecker.h"
#include "../Mechanics/FlushFiveChecker.h"

class ScoringRule {
public:
    ScoringRule(); // Constructor untuk merangkai linked list nanti
    int scoreHand(const Hand& hand);

private:

    FlushFiveChecker flushFiveChecker;
    FlushHouseChecker flushHouseChecker;
    FiveOfAKindChecker fiveOfAKindChecker;
    RoyalFlushChecker royalFlushChecker;
    StraightFlushChecker straightFlushChecker;
    FourOfAKindChecker fourofakindChecker;
    FullHouseChecker fullhouseChecker;
    FlushChecker flushchecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;
    
    // Fungsi internal untuk mengubah HandRank menjadi skor
    int convertRankToScore(HandRank rank); 
};