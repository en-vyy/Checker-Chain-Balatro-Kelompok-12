#pragma once
#include "../System/PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};