#pragma once
#include "../System/PokerHandChecker.h"

class FullHouseChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};