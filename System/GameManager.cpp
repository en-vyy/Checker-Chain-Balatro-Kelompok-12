#include <iostream>
#include "GameManager.h"

void GameManager::runSession() {
    std::cout << "=== Run Started ===\n";
    
    // 1. Generate Hand [cite: 715]
    Hand hand = handGenerator.generateHand(); // Pastikan HandGenerator sudah diubah untuk me-return Hand [cite: 691, 713, 715]
    
    // 2. Play Hand (Pemain memilih kartu) [cite: 717]
    handPlayer.playHand();
    
    // 3. Score Hand (Kirim data kartu ke sistem penilaian)
    int score = scoringRule.scoreHand(hand);
    
    // 4. Check Win Condition & 5. Earn Money
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);
    
    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}