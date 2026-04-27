#pragma once
#include "../System/PokerHandChecker.h"

class FlushFiveChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};