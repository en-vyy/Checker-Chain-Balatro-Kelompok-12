#pragma once

#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"

class GameManager {
public:
    void runSession(); // Fungsi utama yang menjalankan core loop

private:
    // Deklarasi objek-objek sistem yang akan dipanggil secara berurutan
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
};