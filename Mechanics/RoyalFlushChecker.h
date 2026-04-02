#pragma once
#include "../System/PokerHandChecker.h"

class RoyalFlushChecker : public PokerHandChecker {
public:
    HandRank check(const Hand& hand) override;
};