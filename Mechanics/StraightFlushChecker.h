#pragma once
#include "../System/PokerHandChecker.h"

class StraightFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};