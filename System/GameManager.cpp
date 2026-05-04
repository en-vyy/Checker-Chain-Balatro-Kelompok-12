#include <iostream>
#include "GameManager.h"
#include "ChosenHand.h"

void GameManager::runSession() {
    std::cout << "=== Run Started ===\n";
    
    // Generator memberikan Hand utuh
    Hand hand = handGenerator.generateHand(); 
    
    // Player memilih kartu dan menghasilkan ChosenHand
    ChosenHand chosenHand = handPlayer.playHand(hand); 
    
    // Sistem menilai ChosenHand
    int score = scoringRule.scoreHand(chosenHand); 
    
    // Mengecek win/lose dan menghitung reward sesuai instruksi PDF
    bool win = blindRule.checkBlind(score); 
    int reward = rewardRule.earnMoney(win, score); 
    
    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}