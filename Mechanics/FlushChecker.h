#pragma once
#include "../System/PokerHandChecker.h"

class FlushChecker : public PokerHandChecker{
public:
    HandRank check(const Hand& hand) override;
};